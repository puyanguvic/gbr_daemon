#include "ospf/flood/ospf_flood.h"
#include <stdio.h>

int main(void)
{
    printf("Running test_ospf_flood...\n");

    // 创建LSA和邻居列表
    ospf_lsa_t lsa;
    create_lsa(&lsa, ROUTER_LSA, 1, 0xC0A80101);

    ospf_neighbor_t neighbors[3] = {
        {.neighbor_id = 1, .state = TWO_WAY},
        {.neighbor_id = 2, .state = FULL},
        {.neighbor_id = 3, .state = DOWN}};

    // 测试LSA泛洪
    flood_lsa(&lsa, neighbors, 3);

    // 测试LSA确认处理
    handle_lsa_ack(&lsa, 1);

    // 测试LSA重传
    retransmit_lsa(&neighbors[0]);

    printf("All ospf_flood tests passed.\n");
    return 0;
}