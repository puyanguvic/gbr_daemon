#include "ospf_packet.h"
#include "memory.h"
#include <string.h>
#include <arpa/inet.h>

// 解析 OSPF 包
ospf_packet_t *parse_ospf_packet(const unsigned char *data, size_t len)
{
    // 检查数据长度是否足够
    if (len < sizeof(ospf_header_t))
        return NULL;

    // 分配 OSPF 包结构体
    ospf_packet_t *pkt = xmalloc(sizeof(ospf_packet_t));
    // 复制包头部
    memcpy(&pkt->header, data, sizeof(ospf_header_t));

    // 转换字节序
    pkt->header.length = ntohs(pkt->header.length);
    pkt->header.router_id = ntohl(pkt->header.router_id);
    pkt->header.area_id = ntohl(pkt->header.area_id);
    pkt->header.checksum = ntohs(pkt->header.checksum);
    pkt->header.autype = ntohs(pkt->header.autype);

    // 根据包类型解析包体
    switch (pkt->header.type)
    {
    case OSPF_HELLO:
        // 解析 Hello 包特定字段
        break;
    // 其他包类型的解析
    default:
        break;
    }

    return pkt;
}

// 释放 OSPF 包
void free_ospf_packet(ospf_packet_t *pkt)
{
    if (pkt)
    {
        // 如果有动态分配的包体数据，需要释放
        xfree(pkt);
    }
}
