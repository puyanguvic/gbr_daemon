#ifndef OSPF_PACKET_H
#define OSPF_PACKET_H

#include <stdint.h>
#include <stddef.h>    // 添加 size_t 的定义
#include <arpa/inet.h> // 添加 htons 和 ntohs 的定义

// OSPF通用报头结构
typedef struct
{
    uint8_t version;
    uint8_t type;
    uint16_t packet_length;
    uint32_t router_id;
    uint32_t area_id;
    uint16_t checksum;
    uint16_t autype;
    uint64_t authentication;
} ospf_header_t;

// OSPF Hello包结构
typedef struct
{
    ospf_header_t header;
    uint32_t network_mask;
    uint16_t hello_interval;
    uint16_t options;
    uint16_t dead_interval;
    uint32_t designated_router;
    uint32_t backup_designated_router;
    uint32_t neighbors[];
} ospf_hello_t;

// 函数声明
void parse_ospf_header(const uint8_t *packet, ospf_header_t *header);
void create_ospf_hello_packet(ospf_hello_t *hello_packet, uint32_t network_mask, uint16_t hello_interval);
uint16_t calculate_checksum(const uint8_t *data, size_t length);

#endif // OSPF_PACKET_H