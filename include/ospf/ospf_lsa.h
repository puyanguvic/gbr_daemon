#ifndef OSPF_LSA_H
#define OSPF_LSA_H

#include <stdint.h>
#include "memory.h"

// 定义 LSA 头部结构
typedef struct
{
    uint16_t age;        // 老化时间
    uint8_t options;     // 选项
    uint8_t type;        // LSA 类型
    uint32_t id;         // 链路状态 ID
    uint32_t adv_router; // 广告路由器
    uint32_t seq_num;    // 序列号
    uint16_t checksum;   // 校验和
    uint16_t length;     // 长度
    // LSA 特定数据根据类型不同而不同
} ospf_lsa_header_t;

// 定义 LSA 结构
typedef struct ospf_lsa
{
    ospf_lsa_header_t header; // LSA 头部
    void *data;               // LSA 数据
    struct ospf_lsa *next;    // 指向下一个 LSA（链表）
} ospf_lsa_t;

// 定义 LSA 数据库结构
typedef struct
{
    ospf_lsa_t *lsa_list; // LSA 链表
} ospf_lsa_db_t;

// 创建 LSA 数据库
ospf_lsa_db_t *ospf_lsa_db_create();

// 向 LSA 数据库添加 LSA
void ospf_lsa_db_add(ospf_lsa_db_t *db, ospf_lsa_t *lsa);

// 创建 LSA
ospf_lsa_t *ospf_lsa_create();

// 释放 LSA
void ospf_lsa_free(ospf_lsa_t *lsa);

#endif // OSPF_LSA_H
