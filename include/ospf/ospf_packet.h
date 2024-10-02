#ifndef OSPF_PACKET_H
#define OSPF_PACKET_H

#include <stdint.h>

// 定义 OSPF 包类型
#define OSPF_HELLO 1
#define OSPF_DBD 2
#define OSPF_LSR 3
#define OSPF_LSU 4
#define OSPF_LSAck 5

// 定义 OSPF 包头部结构
typedef struct
{
    uint8_t version;         // 版本号
    uint8_t type;            // 包类型
    uint16_t length;         // 包长度
    uint32_t router_id;      // 路由器 ID
    uint32_t area_id;        // 区域 ID
    uint16_t checksum;       // 校验和
    uint16_t autype;         // 认证类型
    uint64_t authentication; // 认证数据
    // 包体部分根据类型不同而不同
} ospf_header_t;

// 定义 OSPF 包结构
typedef struct
{
    ospf_header_t header; // 包头部
    // 根据包类型添加相应的字段
} ospf_packet_t;

// 解析收到的 OSPF 包
ospf_packet_t *parse_ospf_packet(const unsigned char *data, size_t len);

// 释放 OSPF 包
void free_ospf_packet(ospf_packet_t *pkt);

#endif // OSPF_PACKET_H
