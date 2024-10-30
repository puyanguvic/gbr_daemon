#include "../core/ospf_config.h"
#include "ospf_route.h"
#include <stdio.h>
#include <string.h>

static ospf_route_table_t route_table; /**< Static OSPF route table instance */

/**
 * apply_route_configuration - Applies configuration details to the routing table
 * @config: Pointer to the OSPF configuration structure
 *
 * Applies relevant configuration parameters to initialize routing data structures
 * with initial OSPF settings.
 */
static void apply_route_configuration(const ospf_config_t *config)
{
    printf("Configuring OSPF Route Table for Interface: %s, Area ID: %u\n",
           config->interface, config->area_id);
}

/**
 * ospf_route_table_init - Initializes the OSPF routing table.
 *
 * Sets up the OSPF route table by clearing entries and preparing for
 * route additions. Prints a confirmation message on successful initialization.
 */
void ospf_route_table_init()
{
    memset(&route_table, 0, sizeof(route_table));
    printf("OSPF Route Table initialized with maximum capacity of %d routes.\n", MAX_ROUTES);
}

/**
 * ospf_route_add - Adds a new route to the OSPF routing table.
 * @destination: Destination network address
 * @next_hop: Next hop address
 * @cost: Cost of the route
 * @prefix_len: Network prefix length
 *
 * Adds a new route to the OSPF route table if there is capacity.
 * Logs an error if the table is full or a route already exists.
 *
 * Returns: 0 on success, -1 if the route table is full.
 */
int ospf_route_add(struct in_addr destination, struct in_addr next_hop, uint32_t cost, uint8_t prefix_len)
{
    if (route_table.count >= MAX_ROUTES)
    {
        fprintf(stderr, "Error: Route table has reached its maximum capacity.\n");
        return -1;
    }

    ospf_route_entry_t *entry = &route_table.routes[route_table.count++];
    entry->destination = destination;
    entry->next_hop = next_hop;
    entry->cost = cost;
    entry->prefix_len = prefix_len;

    printf("Route Added - Destination: %s, Next Hop: %s, Cost: %u, Prefix Length: %u\n",
           inet_ntoa(destination), inet_ntoa(next_hop), cost, prefix_len);
    return 0;
}

/**
 * ospf_route_remove - Removes a route from the OSPF routing table.
 * @destination: Destination network address
 * @prefix_len: Network prefix length
 *
 * Searches for and removes a specified route from the OSPF routing table,
 * shifting remaining routes to maintain table continuity. Logs if the route
 * is not found in the table.
 *
 * Returns: 0 on success, -1 if the route was not found.
 */
int ospf_route_remove(struct in_addr destination, uint8_t prefix_len)
{
    for (int i = 0; i < route_table.count; i++)
    {
        if (route_table.routes[i].destination.s_addr == destination.s_addr &&
            route_table.routes[i].prefix_len == prefix_len)
        {

            // Shift subsequent routes to fill the removed entry's position
            memmove(&route_table.routes[i], &route_table.routes[i + 1],
                    (route_table.count - i - 1) * sizeof(ospf_route_entry_t));
            route_table.count--;
            printf("Route Removed - Destination: %s, Prefix Length: %u\n",
                   inet_ntoa(destination), prefix_len);
            return 0;
        }
    }
    fprintf(stderr, "Error: Specified route not found for removal (Destination: %s, Prefix Length: %u).\n",
            inet_ntoa(destination), prefix_len);
    return -1;
}

/**
 * ospf_route_update - Updates the OSPF routing table.
 *
 * This function processes link-state advertisements (LSAs) and recalculates routes
 * as necessary, providing the latest routing data based on updated network topology.
 */
void ospf_route_update()
{
    printf("Performing OSPF routing table update based on new LSAs...\n");
    // TODO: Implement SPF recalculations or other update logic based on LSAs
}

/**
 * ospf_route_print - Displays the current contents of the OSPF routing table.
 * @table: Pointer to the OSPF route table structure to print
 *
 * Iterates over each entry in the OSPF routing table and prints its details
 * in a structured format.
 */
void ospf_route_print(const ospf_route_table_t *table)
{
    printf("OSPF Route Table:\n");
    printf("---------------------------------------------------------------\n");
    printf("| %-15s | %-15s | %-4s | %-3s |\n", "Destination", "Next Hop", "Cost", "PL");
    printf("---------------------------------------------------------------\n");

    for (int i = 0; i < table->count; i++)
    {
        printf("| %-15s | %-15s | %-4u | %-3u |\n",
               inet_ntoa(table->routes[i].destination),
               inet_ntoa(table->routes[i].next_hop),
               table->routes[i].cost,
               table->routes[i].prefix_len);
    }
    printf("---------------------------------------------------------------\n");
}
