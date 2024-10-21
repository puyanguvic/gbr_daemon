#ifndef OSPF_FLOOD_H
#define OSPF_FLOOD_H

#include <stdint.h>
#include "../packet/ospf_lsa.h"
#include "../neighbor/ospf_neighbor.h"

// 函数声明
void flood_lsa(const ospf_lsa_t *lsa, ospf_neighbor_t *neighbors, size_t num_neighbors);
void handle_lsa_ack(const ospf_lsa_t *lsa, uint32_t neighbor_id);
void retransmit_lsa(ospf_neighbor_t *neighbor);

#endif // OSPF_FLOOD_H