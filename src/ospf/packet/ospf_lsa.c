#include "ospf_lsa.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

// 创建LSA
void create_lsa(ospf_lsa_t *lsa, ospf_lsa_type_t type, uint32_t link_state_id, uint32_t advertising_router)
{
    lsa->type = type;
    lsa->link_state_id = link_state_id;
    lsa->advertising_router = advertising_router;
    lsa->sequence_number = 0x80000001; // 初始序列号
    lsa->age = 0;
    lsa->checksum = 0; // 校验和需要在序列化时计算
    lsa->length = sizeof(ospf_lsa_t);
    lsa->data = NULL;
    printf("LSA created: type=%d, link_state_id=%u, advertising_router=%u\n", type, link_state_id, advertising_router);
}

// LSA老化
void age_lsa(ospf_lsa_t *lsa)
{
    if (lsa->age < 3600)
    { // 最大老化时间为3600秒
        lsa->age++;
    }
}

// 验证LSA
int validate_lsa(const ospf_lsa_t *lsa)
{
    // 简单的校验，例如检查序列号和校验和是否有效
    if (lsa->sequence_number == 0 || lsa->age > 3600)
    {
        return -1;
    }
    return 0;
}

// 序列化LSA
int serialize_lsa(const ospf_lsa_t *lsa, uint8_t *buffer, size_t buffer_size)
{
    if (buffer_size < lsa->length)
    {
        return -1;
    }
    memcpy(buffer, lsa, sizeof(ospf_lsa_t));
    if (lsa->data && lsa->length > sizeof(ospf_lsa_t))
    {
        memcpy(buffer + sizeof(ospf_lsa_t), lsa->data, lsa->length - sizeof(ospf_lsa_t));
    }
    return 0;
}

// 反序列化LSA
int deserialize_lsa(ospf_lsa_t *lsa, const uint8_t *buffer, size_t buffer_size)
{
    if (buffer_size < sizeof(ospf_lsa_t))
    {
        return -1;
    }
    memcpy(lsa, buffer, sizeof(ospf_lsa_t));
    if (lsa->length > sizeof(ospf_lsa_t))
    {
        lsa->data = (uint8_t *)malloc(lsa->length - sizeof(ospf_lsa_t));
        if (lsa->data == NULL)
        {
            return -1;
        }
        memcpy(lsa->data, buffer + sizeof(ospf_lsa_t), lsa->length - sizeof(ospf_lsa_t));
    }
    return 0;
}