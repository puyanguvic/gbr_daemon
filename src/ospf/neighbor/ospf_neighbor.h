#ifndef OSPF_NEIGHBOR_H
#define OSPF_NEIGHBOR_H

#include <stdint.h>
#include "../packet/ospf_packet.h"
#include "ospf_interface.h"

// OSPF邻居结构
typedef struct
{
    uint32_t neighbor_id;
    uint32_t neighbor_ip;
    uint8_t state;
    ospf_interface_t *interface;
} ospf_neighbor_t;

// 邻居状态枚举
typedef enum
{
    DOWN,
    INIT,
    TWO_WAY,
    EXSTART,
    EXCHANGE,
    LOADING,
    FULL
} ospf_neighbor_state_t;

// 函数声明
void handle_hello_packet(ospf_neighbor_t *neighbor, const ospf_hello_t *hello_packet);
void update_neighbor_state(ospf_neighbor_t *neighbor, ospf_neighbor_state_t new_state);
int add_neighbor(ospf_neighbor_t *neighbors, size_t max_neighbors, uint32_t neighbor_id, ospf_interface_t *interface);
void remove_neighbor(ospf_neighbor_t *neighbors, size_t max_neighbors, uint32_t neighbor_id);

#endif // OSPF_NEIGHBOR_H
