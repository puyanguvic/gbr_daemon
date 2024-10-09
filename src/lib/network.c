#include "network.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netpacket/packet.h>
#include <netinet/ip.h>
#include <net/ethernet.h>

/**
 * @brief Initialize a raw socket for OSPF on a specific interface.
 */
bool ospf_socket_init(ospf_interface_t *iface)
{
    if (!iface)
    {
        fprintf(stderr, "ospf_socket_init: Invalid interface pointer.\n");
        return false;
    }

    // Create a raw socket for IP protocol 89 (OSPF)
    int sockfd = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_IP));
    if (sockfd < 0)
    {
        perror("ospf_socket_init: socket");
        return false;
    }

    // Get the interface index
    iface->ifindex = if_nametoindex(iface->ifname);
    if (iface->ifindex == 0)
    {
        perror("ospf_socket_init: if_nametoindex");
        close(sockfd);
        return false;
    }

    // Bind the socket to the interface
    struct sockaddr_ll addr = {0};
    addr.sll_family = AF_PACKET;
    addr.sll_protocol = htons(ETH_P_IP);
    addr.sll_ifindex = iface->ifindex;

    if (bind(sockfd, (struct sockaddr *)&addr, sizeof(addr)) < 0)
    {
        perror("ospf_socket_init: bind");
        close(sockfd);
        return false;
    }

    // Set socket options to include IP header
    int optval = 1;
    if (setsockopt(sockfd, IPPROTO_IP, IP_HDRINCL, &optval, sizeof(optval)) < 0)
    {
        perror("ospf_socket_init: setsockopt IP_HDRINCL");
        close(sockfd);
        return false;
    }

    iface->socket_fd = sockfd;
    return true;
}

/**
 * @brief Join OSPF multicast groups on the interface.
 */
bool ospf_join_multicast(ospf_interface_t *iface)
{
    if (!iface)
    {
        fprintf(stderr, "ospf_join_multicast: Invalid interface pointer.\n");
        return false;
    }

    // Join multicast group 224.0.0.5 (AllSPFRouters)
    struct ip_mreqn mreq = {0};
    mreq.imr_multiaddr.s_addr = inet_addr("224.0.0.5");
    mreq.imr_address = iface->ip_addr;
    mreq.imr_ifindex = iface->ifindex;

    if (setsockopt(iface->socket_fd, IPPROTO_IP, IP_ADD_MEMBERSHIP, &mreq, sizeof(mreq)) < 0)
    {
        perror("ospf_join_multicast: IP_ADD_MEMBERSHIP AllSPFRouters");
        return false;
    }

    // Join multicast group 224.0.0.6 (AllDRouters)
    mreq.imr_multiaddr.s_addr = inet_addr("224.0.0.6");

    if (setsockopt(iface->socket_fd, IPPROTO_IP, IP_ADD_MEMBERSHIP, &mreq, sizeof(mreq)) < 0)
    {
        perror("ospf_join_multicast: IP_ADD_MEMBERSHIP AllDRouters");
        return false;
    }

    return true;
}

/**
 * @brief Leave OSPF multicast groups on the interface.
 */
bool ospf_leave_multicast(ospf_interface_t *iface)
{
    if (!iface)
    {
        fprintf(stderr, "ospf_leave_multicast: Invalid interface pointer.\n");
        return false;
    }

    // Leave multicast group 224.0.0.5 (AllSPFRouters)
    struct ip_mreqn mreq = {0};
    mreq.imr_multiaddr.s_addr = inet_addr("224.0.0.5");
    mreq.imr_address = iface->ip_addr;
    mreq.imr_ifindex = iface->ifindex;

    if (setsockopt(iface->socket_fd, IPPROTO_IP, IP_DROP_MEMBERSHIP, &mreq, sizeof(mreq)) < 0)
    {
        perror("ospf_leave_multicast: IP_DROP_MEMBERSHIP AllSPFRouters");
        return false;
    }

    // Leave multicast group 224.0.0.6 (AllDRouters)
    mreq.imr_multiaddr.s_addr = inet_addr("224.0.0.6");

    if (setsockopt(iface->socket_fd, IPPROTO_IP, IP_DROP_MEMBERSHIP, &mreq, sizeof(mreq)) < 0)
    {
        perror("ospf_leave_multicast: IP_DROP_MEMBERSHIP AllDRouters");
        return false;
    }

    return true;
}

/**
 * @brief Send an OSPF packet through the interface.
 */
int ospf_send_packet(ospf_interface_t *iface, struct in_addr dest_addr, const void *packet, size_t packet_len)
{
    if (!iface || !packet || packet_len == 0)
    {
        fprintf(stderr, "ospf_send_packet: Invalid arguments.\n");
        return -1;
    }

    // Build the IP header
    struct iphdr ip_header = {0};
    ip_header.version = 4;
    ip_header.ihl = 5;
    ip_header.tot_len = htons(sizeof(struct iphdr) + packet_len);
    ip_header.ttl = 1;       // OSPF uses TTL of 1
    ip_header.protocol = 89; // OSPF protocol number
    ip_header.saddr = iface->ip_addr.s_addr;
    ip_header.daddr = dest_addr.s_addr;
    ip_header.check = 0; // Kernel will compute the checksum

    // Build the complete packet
    unsigned char buffer[1500]; // Adjust size as needed
    memcpy(buffer, &ip_header, sizeof(struct iphdr));
    memcpy(buffer + sizeof(struct iphdr), packet, packet_len);

    // Destination address
    struct sockaddr_ll addr = {0};
    addr.sll_family = AF_PACKET;
    addr.sll_ifindex = iface->ifindex;
    addr.sll_halen = ETH_ALEN;

    // Send the packet
    ssize_t bytes_sent = sendto(iface->socket_fd, buffer, sizeof(struct iphdr) + packet_len, 0,
                                (struct sockaddr *)&addr, sizeof(addr));

    if (bytes_sent < 0)
    {
        perror("ospf_send_packet: sendto");
        return -1;
    }

    return bytes_sent;
}

/**
 * @brief Receive an OSPF packet from the interface.
 */
int ospf_receive_packet(ospf_interface_t *iface, void *buffer, size_t buffer_len)
{
    if (!iface || !buffer || buffer_len == 0)
    {
        fprintf(stderr, "ospf_receive_packet: Invalid arguments.\n");
        return -1;
    }

    ssize_t bytes_received = recvfrom(iface->socket_fd, buffer, buffer_len, 0, NULL, NULL);

    if (bytes_received < 0)
    {
        if (errno != EINTR && errno != EAGAIN)
        {
            perror("ospf_receive_packet: recvfrom");
        }
        return -1;
    }

    return bytes_received;
}

/**
 * @brief Close the OSPF interface and clean up resources.
 */
void ospf_interface_close(ospf_interface_t *iface)
{
    if (iface && iface->socket_fd >= 0)
    {
        close(iface->socket_fd);
        iface->socket_fd = -1;
    }
}
