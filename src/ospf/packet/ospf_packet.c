/* ospf_packet.c */
#include "ospf_packet.h"
#include <string.h>
#include <arpa/inet.h>

// 解析OSPF通用报头
void parse_ospf_header(const uint8_t *packet, ospf_header_t *header)
{
    header->version = packet[0];
    header->type = packet[1];
    header->packet_length = ntohs(*(uint16_t *)(packet + 2));
    header->router_id = ntohl(*(uint32_t *)(packet + 4));
    header->area_id = ntohl(*(uint32_t *)(packet + 8));
    header->checksum = ntohs(*(uint16_t *)(packet + 12));
    header->autype = ntohs(*(uint16_t *)(packet + 14));
    header->authentication = (((uint64_t)ntohl(*(uint32_t *)(packet + 16))) << 32) | ntohl(*(uint32_t *)(packet + 20));
}

// 创建OSPF Hello包
void create_ospf_hello_packet(ospf_hello_t *hello_packet, uint32_t network_mask, uint16_t hello_interval)
{
    memset(hello_packet, 0, sizeof(ospf_hello_t));
    hello_packet->header.version = 2; // OSPF版本
    hello_packet->header.type = 1;    // Hello包类型
    hello_packet->network_mask = htonl(network_mask);
    hello_packet->hello_interval = htons(hello_interval);
    // 填充其他必要字段
}

// 计算校验和
uint16_t calculate_checksum(const uint8_t *data, size_t length)
{
    uint32_t sum = 0;
    for (size_t i = 0; i < length; i += 2)
    {
        uint16_t word = (data[i] << 8) + (i + 1 < length ? data[i + 1] : 0);
        sum += word;
        if (sum > 0xFFFF)
        {
            sum = (sum & 0xFFFF) + (sum >> 16);
        }
    }
    return ~sum;
}