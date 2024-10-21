#include "ospf_neighbor.h"
#include <stdio.h>
#include <string.h>

// 处理收到的Hello包
void handle_hello_packet(ospf_neighbor_t *neighbor, const ospf_hello_t *hello_packet)
{
    if (neighbor->state == DOWN)
    {
        update_neighbor_state(neighbor, INIT);
    }
    else if (neighbor->state == INIT || neighbor->state == TWO_WAY)
    {
        update_neighbor_state(neighbor, TWO_WAY);
    }
    // 更新其他状态逻辑
}

// 更新邻居状态
void update_neighbor_state(ospf_neighbor_t *neighbor, ospf_neighbor_state_t new_state)
{
    neighbor->state = new_state;
    printf("Neighbor %u state updated to %d\n", neighbor->neighbor_id, new_state);
}

// 添加邻居
int add_neighbor(ospf_neighbor_t *neighbors, size_t max_neighbors, uint32_t neighbor_id, ospf_interface_t *interface)
{
    for (size_t i = 0; i < max_neighbors; i++)
    {
        if (neighbors[i].state == DOWN)
        {
            neighbors[i].neighbor_id = neighbor_id;
            neighbors[i].interface = interface;
            neighbors[i].state = INIT;
            printf("Neighbor %u added.\n", neighbor_id);
            return 0;
        }
    }
    return -1;
}

// 删除邻居
void remove_neighbor(ospf_neighbor_t *neighbors, size_t max_neighbors, uint32_t neighbor_id)
{
    for (size_t i = 0; i < max_neighbors; i++)
    {
        if (neighbors[i].neighbor_id == neighbor_id)
        {
            neighbors[i].state = DOWN;
            printf("Neighbor %u removed.\n", neighbor_id);
            break;
        }
    }
}
