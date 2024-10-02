// #ifndef OSPF_NEIGHBOR_H
// #define OSPF_NEIGHBOR_H

// #include <netinet/in.h>
// #include "thread.h"
// #include "ospf_packet.h"

// // 定义邻居状态机的各个状态
// typedef enum
// {
//     NBR_STATE_DOWN,
//     NBR_STATE_INIT,
//     NBR_STATE_TWO_WAY,
//     NBR_STATE_EXSTART,
//     NBR_STATE_EXCHANGE,
//     NBR_STATE_LOADING,
//     NBR_STATE_FULL
// } nbr_state_t;

// // 定义邻居结构体
// typedef struct ospf_neighbor
// {
//     struct in_addr router_id;   // 邻居的路由器 ID
//     nbr_state_t state;          // 邻居状态
//     struct in_addr address;     // 邻居的 IP 地址
//     struct ospf_neighbor *next; // 指向下一个邻居（链表）
//     // 其他状态信息，如序列号、LSA 等
// } ospf_neighbor_t;

// // 处理收到的 Hello 包，更新邻居状态
// void ospf_neighbor_receive_hello(ospf_neighbor_t *nbr, ospf_hello_packet_t *pkt);

// // 更新邻居状态
// void ospf_neighbor_update_state(ospf_neighbor_t *nbr, nbr_state_t new_state);

// #endif // OSPF_NEIGHBOR_H
