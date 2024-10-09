#ifndef NETWORK_H
#define NETWORK_H

#include <netinet/in.h>
#include <net/if.h>
#include <stdbool.h>

/**
 * @brief Structure representing a network interface for OSPF.
 */
typedef struct
{
    char ifname[IFNAMSIZ];  // Interface name
    int ifindex;            // Interface index
    struct in_addr ip_addr; // Interface IP address
    struct in_addr netmask; // Interface netmask
    int socket_fd;          // Raw socket file descriptor
} ospf_interface_t;

/**
 * @brief Initialize a raw socket for OSPF on a specific interface.
 *
 * @param iface Pointer to the OSPF interface structure.
 * @return True on success, false on failure.
 */
bool ospf_socket_init(ospf_interface_t *iface);

/**
 * @brief Join OSPF multicast groups on the interface.
 *
 * @param iface Pointer to the OSPF interface structure.
 * @return True on success, false on failure.
 */
bool ospf_join_multicast(ospf_interface_t *iface);

/**
 * @brief Leave OSPF multicast groups on the interface.
 *
 * @param iface Pointer to the OSPF interface structure.
 * @return True on success, false on failure.
 */
bool ospf_leave_multicast(ospf_interface_t *iface);

/**
 * @brief Send an OSPF packet through the interface.
 *
 * @param iface Pointer to the OSPF interface structure.
 * @param dest_addr Destination IP address.
 * @param packet Pointer to the packet data.
 * @param packet_len Length of the packet data.
 * @return Number of bytes sent on success, -1 on failure.
 */
int ospf_send_packet(ospf_interface_t *iface, struct in_addr dest_addr, const void *packet, size_t packet_len);

/**
 * @brief Receive an OSPF packet from the interface.
 *
 * @param iface Pointer to the OSPF interface structure.
 * @param buffer Buffer to store the received packet.
 * @param buffer_len Length of the buffer.
 * @return Number of bytes received on success, -1 on failure.
 */
int ospf_receive_packet(ospf_interface_t *iface, void *buffer, size_t buffer_len);

/**
 * @brief Close the OSPF interface and clean up resources.
 *
 * @param iface Pointer to the OSPF interface structure.
 */
void ospf_interface_close(ospf_interface_t *iface);

#endif // NETWORK_H
