#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <netinet/ip.h>
#include "network.h"

int main(void)
{
    printf("Running network operations tests...\n");

    ospf_interface_t iface;
    memset(&iface, 0, sizeof(ospf_interface_t));
    strncpy(iface.ifname, "lo", IFNAMSIZ);

    // Initialize interface IP address
    if (inet_pton(AF_INET, "127.0.0.1", &iface.ip_addr) != 1)
    {
        fprintf(stderr, "Failed to set interface IP address.\n");
        return 1;
    }

    // Initialize the raw socket
    if (!ospf_socket_init(&iface))
    {
        fprintf(stderr, "Failed to initialize OSPF socket.\n");
        return 1;
    }

    // Join multicast groups
    if (!ospf_join_multicast(&iface))
    {
        fprintf(stderr, "Failed to join multicast groups.\n");
        ospf_interface_close(&iface);
        return 1;
    }

    // Prepare a test OSPF packet (dummy data)
    const char *ospf_packet = "OSPF Test Packet";
    size_t packet_len = strlen(ospf_packet) + 1; // Include null terminator

    // Set destination address to 224.0.0.5 (AllSPFRouters)
    struct in_addr dest_addr;
    inet_pton(AF_INET, "224.0.0.5", &dest_addr);

    // Send the packet
    int bytes_sent = ospf_send_packet(&iface, dest_addr, ospf_packet, packet_len);
    if (bytes_sent < 0)
    {
        fprintf(stderr, "Failed to send OSPF packet.\n");
        ospf_leave_multicast(&iface);
        ospf_interface_close(&iface);
        return 1;
    }
    printf("Sent OSPF packet (%d bytes).\n", bytes_sent);

    // Receive the packet (non-blocking for testing purposes)
    unsigned char buffer[1500];
    int bytes_received = ospf_receive_packet(&iface, buffer, sizeof(buffer));
    if (bytes_received > 0)
    {
        // Skip the IP header
        struct iphdr *ip_header = (struct iphdr *)buffer;
        void *ospf_data = buffer + ip_header->ihl * 4;
        int ospf_data_len = bytes_received - ip_header->ihl * 4;

        printf("Received OSPF packet (%d bytes): %.*s\n", bytes_received, ospf_data_len, (char *)ospf_data);
    }
    else
    {
        printf("No OSPF packet received.\n");
    }

    // Leave multicast groups
    if (!ospf_leave_multicast(&iface))
    {
        fprintf(stderr, "Failed to leave multicast groups.\n");
    }

    // Close the interface
    ospf_interface_close(&iface);

    printf("All network operations tests completed.\n");
    return 0;
}
