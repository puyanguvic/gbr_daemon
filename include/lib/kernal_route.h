#ifndef KERNEL_ROUTE_H
#define KERNEL_ROUTE_H

#include <netinet/in.h>

// 添加路由到内核路由表
int add_route(const struct in_addr *dest, uint8_t prefixlen, const struct in_addr *gateway);

// 从内核路由表删除路由
int delete_route(const struct in_addr *dest, uint8_t prefixlen);

#endif // KERNEL_ROUTE_H
