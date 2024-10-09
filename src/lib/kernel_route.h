#ifndef KERNEL_ROUTE_H
#define KERNEL_ROUTE_H

#include <netinet/in.h>
#include <stdbool.h>

/**
 * @brief Structure representing a kernel routing table entry.
 */
typedef struct
{
    struct in_addr destination; // Destination IP address (network byte order)
    struct in_addr gateway;     // Gateway IP address (network byte order)
    uint32_t ifindex;           // Interface index
    uint32_t metric;            // Route metric (priority)
    uint8_t prefix_len;         // Prefix length (CIDR notation)
} kernel_route_t;

/**
 * @brief Add a route to the kernel routing table.
 *
 * @param route Pointer to the route structure.
 * @return True on success, false on failure.
 */
bool kernel_route_add(const kernel_route_t *route);

/**
 * @brief Delete a route from the kernel routing table.
 *
 * @param route Pointer to the route structure.
 * @return True on success, false on failure.
 */
bool kernel_route_delete(const kernel_route_t *route);

/**
 * @brief Modify a route in the kernel routing table.
 *
 * @param route Pointer to the route structure.
 * @return True on success, false on failure.
 */
bool kernel_route_modify(const kernel_route_t *route);

#endif // KERNEL_ROUTE_H
