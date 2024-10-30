#ifndef OSPF_ROUTE_H
#define OSPF_ROUTE_H

#include <stdint.h>
#include <netinet/in.h>

#define MAX_ROUTES 256 /**< Maximum number of routes in the OSPF routing table */

/**
 * struct ospf_route_entry_t - Represents an OSPF route entry.
 * @destination: Destination network IP address.
 * @next_hop: IP address of the next hop for this route.
 * @cost: Metric cost associated with this route.
 * @prefix_len: Prefix length of the destination network.
 */
typedef struct
{
    struct in_addr destination;
    struct in_addr next_hop;
    uint32_t cost;
    uint8_t prefix_len;
} ospf_route_entry_t;

/**
 * struct ospf_route_table_t - Contains the OSPF routing table.
 * @routes: Array of active OSPF route entries.
 * @count: Number of current entries in the table.
 */
typedef struct
{
    ospf_route_entry_t routes[MAX_ROUTES];
    int count;
} ospf_route_table_t;

/* OSPF Route Table Function Declarations */
void ospf_route_table_init(); /**< Initializes the OSPF routing table */
int ospf_route_add(struct in_addr destination, struct in_addr next_hop, uint32_t cost, uint8_t prefix_len);
int ospf_route_remove(struct in_addr destination, uint8_t prefix_len);
void ospf_route_update();                               /**< Updates OSPF routing based on new LSAs */
void ospf_route_print(const ospf_route_table_t *table); /**< Prints the OSPF routing table */

#endif // OSPF_ROUTE_H
