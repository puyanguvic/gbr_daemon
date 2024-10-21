#include "ospf/packet/ospf_lsa.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
    printf("Running test_ospf_lsa...\n");

    // 测试创建LSA
    ospf_lsa_t lsa;
    create_lsa(&lsa, ROUTER_LSA, 1, 0xC0A80101);
    if (lsa.type != ROUTER_LSA || lsa.link_state_id != 1 || lsa.advertising_router != 0xC0A80101)
    {
        printf("create_lsa failed.\n");
        return 1;
    }

    // 测试LSA老化
    for (int i = 0; i < 3601; i++)
    {
        age_lsa(&lsa);
    }
    if (lsa.age != 3600)
    {
        printf("age_lsa failed.\n");
        return 1;
    }

    // 测试LSA验证
    if (validate_lsa(&lsa) != 0)
    {
        printf("validate_lsa failed.\n");
        return 1;
    }

    // 测试LSA序列化和反序列化
    uint8_t buffer[1024];
    if (serialize_lsa(&lsa, buffer, sizeof(buffer)) != 0)
    {
        printf("serialize_lsa failed.\n");
        return 1;
    }

    ospf_lsa_t deserialized_lsa;
    if (deserialize_lsa(&deserialized_lsa, buffer, sizeof(buffer)) != 0)
    {
        printf("deserialize_lsa failed.\n");
        return 1;
    }

    if (deserialized_lsa.type != lsa.type || deserialized_lsa.link_state_id != lsa.link_state_id ||
        deserialized_lsa.advertising_router != lsa.advertising_router)
    {
        printf("deserialize_lsa data mismatch.\n");
        return 1;
    }

    printf("All ospf_lsa tests passed.\n");
    return 0;
}