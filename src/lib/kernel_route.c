#include "kernel_route.h"
#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>

// Include libnl headers
#include <netlink/netlink.h>
#include <netlink/socket.h>
#include <netlink/msg.h>
#include <netlink/route/route.h>
#include <netlink/route/nexthop.h>
#include <netlink/route/addr.h>

/**
 * @brief Internal function to create a route object.
 */
static struct rtnl_route *create_route_object(const kernel_route_t *route)
{
    struct rtnl_route *r;
    struct nl_addr *dst_addr = NULL;
    struct rtnl_nexthop *nh = NULL;
    int err;

    r = rtnl_route_alloc();
    if (!r)
    {
        fprintf(stderr, "Failed to allocate rtnl_route object.\n");
        return NULL;
    }

    // Set destination address
    char dst_str[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &route->destination, dst_str, sizeof(dst_str));
    err = nl_addr_parse(dst_str, AF_INET, &dst_addr);
    if (err < 0)
    {
        fprintf(stderr, "Failed to parse destination address: %s\n", nl_geterror(err));
        rtnl_route_put(r);
        return NULL;
    }
    nl_addr_set_prefixlen(dst_addr, route->prefix_len);
    rtnl_route_set_dst(r, dst_addr);
    nl_addr_put(dst_addr); // Decrease reference count

    // Create next hop
    nh = rtnl_route_nh_alloc();
    if (!nh)
    {
        fprintf(stderr, "Failed to allocate rtnl_nexthop object.\n");
        rtnl_route_put(r);
        return NULL;
    }

    // Set gateway
    if (route->gateway.s_addr != 0)
    { // Non-zero gateway
        struct nl_addr *gw_addr = NULL;
        char gw_str[INET_ADDRSTRLEN];
        inet_ntop(AF_INET, &route->gateway, gw_str, sizeof(gw_str));
        err = nl_addr_parse(gw_str, AF_INET, &gw_addr);
        if (err < 0)
        {
            fprintf(stderr, "Failed to parse gateway address: %s\n", nl_geterror(err));
            rtnl_route_nh_free(nh);
            rtnl_route_put(r);
            return NULL;
        }
        rtnl_route_nh_set_gateway(nh, gw_addr);
        nl_addr_put(gw_addr);
    }

    // Set interface index
    rtnl_route_nh_set_ifindex(nh, route->ifindex);

    // Add next hop to the route
    rtnl_route_add_nexthop(r, nh);

    // Set priority (metric)
    rtnl_route_set_priority(r, route->metric);

    return r;
}

/**
 * @brief Add a route to the kernel routing table.
 */
bool kernel_route_add(const kernel_route_t *route)
{
    struct nl_sock *sock = NULL;
    struct rtnl_route *r = NULL;
    int err;

    if (!route)
    {
        fprintf(stderr, "kernel_route_add: Invalid route pointer.\n");
        return false;
    }

    sock = nl_socket_alloc();
    if (!sock)
    {
        fprintf(stderr, "Failed to allocate Netlink socket.\n");
        return false;
    }

    nl_socket_disable_seq_check(sock);

    if ((err = nl_connect(sock, NETLINK_ROUTE)) < 0)
    {
        fprintf(stderr, "Failed to connect Netlink socket: %s\n", nl_geterror(err));
        nl_socket_free(sock);
        return false;
    }

    r = create_route_object(route);
    if (!r)
    {
        nl_socket_free(sock);
        return false;
    }

    err = rtnl_route_add(sock, r, 0);
    if (err < 0)
    {
        fprintf(stderr, "Failed to add route: %s\n", nl_geterror(err));
        rtnl_route_put(r);
        nl_socket_free(sock);
        return false;
    }

    rtnl_route_put(r);
    nl_socket_free(sock);
    return true;
}

/**
 * @brief Delete a route from the kernel routing table.
 */
bool kernel_route_delete(const kernel_route_t *route)
{
    struct nl_sock *sock = NULL;
    struct rtnl_route *r = NULL;
    int err;

    if (!route)
    {
        fprintf(stderr, "kernel_route_delete: Invalid route pointer.\n");
        return false;
    }

    sock = nl_socket_alloc();
    if (!sock)
    {
        fprintf(stderr, "Failed to allocate Netlink socket.\n");
        return false;
    }

    nl_socket_disable_seq_check(sock);

    if ((err = nl_connect(sock, NETLINK_ROUTE)) < 0)
    {
        fprintf(stderr, "Failed to connect Netlink socket: %s\n", nl_geterror(err));
        nl_socket_free(sock);
        return false;
    }

    r = create_route_object(route);
    if (!r)
    {
        nl_socket_free(sock);
        return false;
    }

    err = rtnl_route_delete(sock, r, 0);
    if (err < 0)
    {
        fprintf(stderr, "Failed to delete route: %s\n", nl_geterror(err));
        rtnl_route_put(r);
        nl_socket_free(sock);
        return false;
    }

    rtnl_route_put(r);
    nl_socket_free(sock);
    return true;
}

/**
 * @brief Modify a route in the kernel routing table.
 */
bool kernel_route_modify(const kernel_route_t *route)
{
    // In Netlink, modifying a route is typically done by replacing it.
    // So we delete the existing route and add the new one.
    if (!kernel_route_delete(route))
    {
        fprintf(stderr, "Failed to delete existing route for modification.\n");
        return false;
    }
    if (!kernel_route_add(route))
    {
        fprintf(stderr, "Failed to add new route for modification.\n");
        return false;
    }
    return true;
}
