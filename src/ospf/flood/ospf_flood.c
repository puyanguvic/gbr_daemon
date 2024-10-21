#include "ospf_flood.h"
#include <stdio.h>
#include <string.h>

// LSA泛洪
void flood_lsa(const ospf_lsa_t *lsa, ospf_neighbor_t *neighbors, size_t num_neighbors)
{
    for (size_t i = 0; i < num_neighbors; i++)
    {
        if (neighbors[i].state >= TWO_WAY)
        {
            printf("Flooding LSA to neighbor %u\n", neighbors[i].neighbor_id);
            // 发送LSA逻辑，可以使用发送函数（未实现）
        }
    }
}

// 处理LSA确认
void handle_lsa_ack(const ospf_lsa_t *lsa, uint32_t neighbor_id)
{
    printf("Received LSA ack from neighbor %u for LSA with link_state_id %u\n", neighbor_id, lsa->link_state_id);
    // 处理确认逻辑，例如从重传队列中移除（未实现）
}

// 重传LSA
void retransmit_lsa(ospf_neighbor_t *neighbor)
{
    if (neighbor->state >= TWO_WAY)
    {
        printf("Retransmitting LSA to neighbor %u\n", neighbor->neighbor_id);
        // 重传逻辑，可以使用发送函数（未实现）
    }
}