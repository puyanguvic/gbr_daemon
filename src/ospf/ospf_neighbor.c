// #include "ospf_neighbor.h"
// #include "log.h"

// // 处理收到的 Hello 包
// void ospf_neighbor_receive_hello(ospf_neighbor_t *nbr, ospf_hello_packet_t *pkt)
// {
//     log_debug("Received Hello from neighbor %s", inet_ntoa(nbr->address));

//     // 更新邻居状态机
//     if (nbr->state == NBR_STATE_DOWN)
//     {
//         ospf_neighbor_update_state(nbr, NBR_STATE_INIT);
//     }
//     // 其他状态更新逻辑，根据协议规范处理
// }

// // 更新邻居状态并执行相应操作
// void ospf_neighbor_update_state(ospf_neighbor_t *nbr, nbr_state_t new_state)
// {
//     log_info("Neighbor %s state changed from %d to %d",
//              inet_ntoa(nbr->address), nbr->state, new_state);
//     nbr->state = new_state;

//     // 根据新状态执行相应的操作
//     switch (new_state)
//     {
//     case NBR_STATE_TWO_WAY:
//         // 建立邻接关系，可能需要选举 DR/BDR
//         break;
//     case NBR_STATE_FULL:
//         // 邻居完全同步，LSA 数据库已更新
//         break;
//     default:
//         break;
//     }
// }
