// #include "prefix.h"
// #include <arpa/inet.h>

// // 判断两个前缀是否匹配
// int prefix_match(const prefix_ipv4_t *p1, const prefix_ipv4_t *p2)
// {
//     if (p1->prefixlen != p2->prefixlen)
//         return 0;

//     uint32_t mask = htonl(~((1 << (32 - p1->prefixlen)) - 1));
//     return (p1->prefix.s_addr & mask) == (p2->prefix.s_addr & mask);
// }

// // 根据前缀长度生成子网掩码
// void prefix_to_mask(uint8_t prefixlen, struct in_addr *mask)
// {
//     if (prefixlen == 0)
//     {
//         mask->s_addr = 0;
//     }
//     else
//     {
//         mask->s_addr = htonl(~((1 << (32 - prefixlen)) - 1));
//     }
// }

// // 根据子网掩码计算前缀长度
// void mask_to_prefix(const struct in_addr *mask, uint8_t *prefixlen)
// {
//     uint32_t m = ntohl(mask->s_addr);
//     *prefixlen = 0;
//     while (m & 0x80000000)
//     {
//         (*prefixlen)++;
//         m <<= 1;
//     }
// }
