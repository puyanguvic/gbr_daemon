#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include "kernel_route.h"

int main(void)
{
    printf("Running kernel routing interaction tests...\n");

    kernel_route_t route;
    memset(&route, 0, sizeof(kernel_route_t));

    // Set destination to 10.0.0.0/24
    inet_pton(AF_INET, "10.0.0.0", &route.destination);
    route.prefix_len = 24;

    // Set gateway to 192.168.1.1
    inet_pton(AF_INET, "192.168.1.1", &route.gateway);

    // Use interface index 2 (adjust as appropriate)
    route.ifindex = 2;

    // Set metric
    route.metric = 100;

    // Add the route
    if (!kernel_route_add(&route))
    {
        fprintf(stderr, "Failed to add route.\n");
        return 1;
    }
    printf("Route added successfully.\n");

    // Modify the route (change metric)
    route.metric = 50;
    if (!kernel_route_modify(&route))
    {
        fprintf(stderr, "Failed to modify route.\n");
        return 1;
    }
    printf("Route modified successfully.\n");

    // Delete the route
    if (!kernel_route_delete(&route))
    {
        fprintf(stderr, "Failed to delete route.\n");
        return 1;
    }
    printf("Route deleted successfully.\n");

    printf("All kernel routing interaction tests completed.\n");
    return 0;
}
