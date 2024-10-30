#ifndef OSPF_ASE_H
#define OSPF_ASE_H

#include "../packet/ospf_lsa.h"
#include "ospf_route.h"

#include <arpa/inet.h>

// Enum for external route types
typedef enum
{
    EXTERNAL_TYPE_1,
    EXTERNAL_TYPE_2
} external_route_type;

// Define the ospf structure
struct ospf
{
    uint32_t router_id;
    ospf_route_table_t route_table; // OSPF route table
    // Other OSPF-related data members
};

// Define the route structure
struct route
{
    struct in_addr destination;
    uint32_t metric;
    external_route_type type;
    struct in_addr next_hop;
    uint8_t prefix_len;
    // Other route-related data members
};

// Function declarations for managing AS external routes
void ospf_ase_lsa_originate(struct ospf *ospf, struct route *route);
void ospf_ase_route_update(struct ospf *ospf, struct route *route);

#endif // OSPF_ASE_H
