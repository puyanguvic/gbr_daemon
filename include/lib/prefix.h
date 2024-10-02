#ifndef PREFIX_H
#define PREFIX_H

#include <netinet/in.h>
#include <stdint.h>

// 定义 IPv4 前缀结构体
typedef struct
{
    struct in_addr prefix; // 网络前缀地址
    uint8_t prefixlen;     // 前缀长度
} prefix_ipv4_t;

// 比较两个前缀是否匹配
int prefix_match(const prefix_ipv4_t *p1, const prefix_ipv4_t *p2);

// 根据前缀长度生成子网掩码
void prefix_to_mask(uint8_t prefixlen, struct in_addr *mask);

// 根据子网掩码计算前缀长度
void mask_to_prefix(const struct in_addr *mask, uint8_t *prefixlen);

#endif // PREFIX_H
