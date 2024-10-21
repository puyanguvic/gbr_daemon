#ifndef OSPF_LSA_H
#define OSPF_LSA_H

#include <stdint.h>
#include <stddef.h>
#include <stdlib.h> // 添加 malloc 函数的定义

// LSA 类型枚举
typedef enum
{
    ROUTER_LSA,
    NETWORK_LSA,
    SUMMARY_LSA,
    AS_EXTERNAL_LSA
} ospf_lsa_type_t;

// OSPF LSA 结构
typedef struct
{
    ospf_lsa_type_t type;
    uint32_t link_state_id;
    uint32_t advertising_router;
    uint32_t sequence_number;
    uint16_t age;
    uint16_t checksum;
    uint16_t length;
    uint8_t *data; // 指向具体LSA数据的指针
} ospf_lsa_t;

// 函数声明
void create_lsa(ospf_lsa_t *lsa, ospf_lsa_type_t type, uint32_t link_state_id, uint32_t advertising_router);
void age_lsa(ospf_lsa_t *lsa);
int validate_lsa(const ospf_lsa_t *lsa);
int serialize_lsa(const ospf_lsa_t *lsa, uint8_t *buffer, size_t buffer_size);
int deserialize_lsa(ospf_lsa_t *lsa, const uint8_t *buffer, size_t buffer_size);

#endif // OSPF_LSA_H
