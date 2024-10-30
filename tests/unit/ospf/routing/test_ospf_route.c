#include "ospf/routing/ospf_route.h"
#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>

// Ensure to include necessary headers for inet_ntop
#ifdef __APPLE__
#include <netinet/in.h>
#include <sys/socket.h>
#endif

void ospf_route_table_init(ospf_route_table_t *table)
{
    table->count = 0;
}

int ospf_route_add(ospf_route_table_t *table, struct in_addr destination, struct in_addr next_hop, uint32_t cost, uint8_t prefix_len)
{
    if (table->count >= MAX_ROUTES)
    {
        return -1; // Route table is full
    }

    for (int i = 0; i < table->count; i++)
    {
        if (table->routes[i].destination.s_addr == destination.s_addr &&
            table->routes[i].prefix_len == prefix_len)
        {
            table->routes[i].next_hop = next_hop;
            table->routes[i].cost = cost;
            return 0;
        }
    }

    ospf_route_entry_t *new_route = &table->routes[table->count];
    new_route->destination = destination;
    new_route->next_hop = next_hop;
    new_route->cost = cost;
    new_route->prefix_len = prefix_len;
    table->count++;

    return 0;
}

int ospf_route_remove(ospf_route_table_t *table, struct in_addr destination, uint8_t prefix_len)
{
    for (int i = 0; i < table->count; i++)
    {
        if (table->routes[i].destination.s_addr == destination.s_addr &&
            table->routes[i].prefix_len == prefix_len)
        {
            memmove(&table->routes[i], &table->routes[i + 1],
                    (table->count - i - 1) * sizeof(ospf_route_entry_t));
            table->count--;
            return 0;
        }
    }

    return -1; // Route not found
}

void ospf_route_print(const ospf_route_table_t *table)
{
    printf("OSPF Route Table:\n");
    for (int i = 0; i < table->count; i++)
    {
        char dest_str[INET_ADDRSTRLEN];
        char next_hop_str[INET_ADDRSTRLEN];
        if (inet_ntop(AF_INET, &table->routes[i].destination, dest_str, INET_ADDRSTRLEN) == NULL)
        {
            perror("inet_ntop failed for destination");
            continue;
        }
        if (inet_ntop(AF_INET, &table->routes[i].next_hop, next_hop_str, INET_ADDRSTRLEN) == NULL)
        {
            perror("inet_ntop failed for next hop");
            continue;
        }
        printf("Destination: %s/%d, Next Hop: %s, Cost: %u\n", dest_str, table->routes[i].prefix_len, next_hop_str, table->routes[i].cost);
    }
}

void test_ospf_route()
{
    ospf_route_table_t route_table;
    ospf_route_table_init(&route_table);

    struct in_addr dest1, next_hop1;
    if (inet_aton("192.168.1.0", &dest1) == 0)
    {
        fprintf(stderr, "inet_aton failed for destination\n");
        return;
    }
    if (inet_aton("192.168.1.1", &next_hop1) == 0)
    {
        fprintf(stderr, "inet_aton failed for next hop\n");
        return;
    }

    // Test adding a route
    int add_result = ospf_route_add(&route_table, dest1, next_hop1, 10, 24);
    if (add_result == 0)
    {
        printf("Route added successfully.\n");
    }
    else
    {
        printf("Failed to add route.\n");
    }

    // Test getting the route
    ospf_route_print(&route_table);

    // Test removing the route
    int remove_result = ospf_route_remove(&route_table, dest1, 24);
    if (remove_result == 0)
    {
        printf("Route removed successfully.\n");
    }
    else
    {
        printf("Failed to remove route.\n");
    }

    // Test getting the route after removal
    ospf_route_print(&route_table);
}

int main()
{
    printf("Running OSPF route tests...\n");
    test_ospf_route();
    return 0;
}
