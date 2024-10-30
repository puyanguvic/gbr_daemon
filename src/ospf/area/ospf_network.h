#ifndef OSPF_NETWORK_H
#define OSPF_NETWORK_H

// Structure to represent an OSPF network
typedef struct ospf_network
{
    const char *network_prefix; // Network prefix
    struct ospf_network *next;  // Pointer to the next network in the area
} ospf_network_t;

// Function declarations
ospf_network_t *ospf_network_create(const char *network_prefix);
void ospf_network_delete(ospf_network_t *network);

#endif // OSPF_NETWORK_H
