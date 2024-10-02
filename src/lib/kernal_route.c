#include "kernel_route.h"
#include <netlink/netlink.h>
#include <netlink/msg.h>
#include <netlink/route/route.h>
#include <netlink/route/nexthop.h>
#include <stdio.h>

// 添加路由到内核路由表
int add_route(const struct in_addr *dest, uint8_t prefixlen, const struct in_addr *gateway)
{
    // 创建 Netlink 套接字
    struct nl_sock *sock = nl_socket_alloc();
    if (!sock)
    {
        fprintf(stderr, "Failed to allocate netlink socket\n");
        return -1;
    }

    // 连接到路由子系统
    if (nl_connect(sock, NETLINK_ROUTE) < 0)
    {
        fprintf(stderr, "Failed to connect to netlink route\n");
        nl_socket_free(sock);
        return -1;
    }

    // 创建路由对象
    struct rtnl_route *route = rtnl_route_alloc();
    if (!route)
    {
        fprintf(stderr, "Failed to allocate rtnl_route\n");
        nl_socket_free(sock);
        return -1;
    }

    // 设置目的网络前缀
    struct nl_addr *dst = nl_addr_build(AF_INET, (void *)&dest->s_addr, 4);
    nl_addr_set_prefixlen(dst, prefixlen);
    rtnl_route_set_dst(route, dst);

    // 创建下一跳
    struct rtnl_nexthop *nh = rtnl_route_nh_alloc();
    struct nl_addr *gw = nl_addr_build(AF_INET, (void *)&gateway->s_addr, 4);
    rtnl_route_nh_set_gateway(nh, gw);
    rtnl_route_add_nexthop(route, nh);

    // 添加路由到内核
    int err = rtnl_route_add(sock, route, 0);
    if (err < 0)
    {
        fprintf(stderr, "Failed to add route: %s\n", nl_geterror(err));
    }

    // 释放资源
    nl_addr_put(dst);
    nl_addr_put(gw);
    rtnl_route_put(route);
    nl_socket_free(sock);

    return err;
}

// 从内核路由表删除路由
int delete_route(const struct in_addr *dest, uint8_t prefixlen)
{
    // 实现与 add_route 类似，使用 rtnl_route_delete
    return 0;
}
