#include "ospf_ase.h"
#include "../packet/ospf_lsa.h"
#include "ospf_route.h"
#include <stdlib.h>
#include <stdio.h>

// Function to originate an AS-external LSA
void ospf_ase_lsa_originate(struct ospf *ospf, struct route *route)
{
    if (ospf == NULL || route == NULL)
    {
        printf("Error: OSPF or route is NULL\n");
        return;
    }

    // Create a new LSA for the external route
    ospf_lsa_t *new_lsa = malloc(sizeof(ospf_lsa_t));
    if (new_lsa == NULL)
    {
        printf("Error: Unable to allocate memory for new LSA\n");
        return;
    }

    // Fill in the LSA details
    new_lsa->type = AS_EXTERNAL_LSA;
    new_lsa->link_state_id = route->destination.s_addr; // Use the route destination as the LSA ID
    new_lsa->advertising_router = ospf->router_id;
    new_lsa->sequence_number = 1; // Initial sequence number
    new_lsa->age = 0;             // Newly originated LSA
    new_lsa->checksum = 0;        // Placeholder, calculate checksum later
    new_lsa->length = sizeof(ospf_lsa_t);
    new_lsa->data = NULL; // No additional data for now

    // Add the new LSA to the OSPF LSA database
    ospf_lsa_add(new_lsa);

    printf("Originated AS-external LSA for route: %s\n", inet_ntoa(route->destination));
}

// Function to update AS external routes
void ospf_ase_route_update(struct ospf *ospf, struct route *route)
{
    if (ospf == NULL || route == NULL)
    {
        printf("Error: OSPF or route is NULL\n");
        return;
    }

    // Check if the route already exists in the routing table
    ospf_route_table_t *route_table = &ospf->route_table;
    for (int i = 0; i < route_table->count; i++)
    {
        if (route_table->routes[i].destination.s_addr == route->destination.s_addr &&
            route_table->routes[i].prefix_len == route->prefix_len)
        {
            // Route exists, update the metric if necessary
            if (route_table->routes[i].cost != route->metric)
            {
                route_table->routes[i].cost = route->metric;
                // Re-originate the LSA with the updated metric
                ospf_ase_lsa_originate(ospf, route);
            }
            printf("Updated AS-external route for destination: %s\n", inet_ntoa(route->destination));
            return;
        }
    }

    // Route does not exist, add a new route
    if (route_table->count < MAX_ROUTES)
    {
        ospf_route_add(route_table, route->destination, route->next_hop, route->metric, route->prefix_len);
        // Originate a new LSA for this external route
        ospf_ase_lsa_originate(ospf, route);
        printf("Added new AS-external route for destination: %s\n", inet_ntoa(route->destination));
    }
    else
    {
        printf("Error: Route table is full, cannot add new route\n");
    }
}
