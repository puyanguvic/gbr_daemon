#include "ospf/neighbor/ospf_neighbor.h"
#include <stdio.h>

int main(void)
{
    printf("Running test_ospf_neighbor...\n");

    // 创建接口和邻居列表
    ospf_interface_t test_interface = {"eth0", 0xC0A80101, 0xFFFFFF00, 1500, 10, 40, 1};
    ospf_neighbor_t neighbors[10] = {0};

    // 测试添加邻居
    if (add_neighbor(neighbors, 10, 1, &test_interface) != 0)
    {
        printf("add_neighbor failed.\n");
        return 1;
    }

    // 测试邻居状态更新
    update_neighbor_state(&neighbors[0], TWO_WAY);
    if (neighbors[0].state != TWO_WAY)
    {
        printf("update_neighbor_state failed.\n");
        return 1;
    }

    // 测试处理Hello包
    ospf_hello_t hello_packet = {0};
    handle_hello_packet(&neighbors[0], &hello_packet);
    if (neighbors[0].state != TWO_WAY)
    {
        printf("handle_hello_packet failed.\n");
        return 1;
    }

    // 测试删除邻居
    remove_neighbor(neighbors, 10, 1);
    if (neighbors[0].state != DOWN)
    {
        printf("remove_neighbor failed.\n");
        return 1;
    }

    printf("All ospf_neighbor tests passed.\n");
    return 0;
}