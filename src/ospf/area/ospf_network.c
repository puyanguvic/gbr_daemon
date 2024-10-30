#include "ospf_network.h"
#include "log.h"
#include <stdlib.h>
#include <stdio.h>

// Function to initialize a new OSPF network
ospf_network_t *ospf_network_create(const char *network_prefix)
{
    ospf_network_t *network = (ospf_network_t *)malloc(sizeof(ospf_network_t));
    if (network == NULL)
    {
        log_error("Failed to allocate memory for OSPF network\n");
        return NULL;
    }

    network->network_prefix = network_prefix;
    network->next = NULL;
    log_info("OSPF network created with prefix: %s\n", network_prefix);
    return network;
}

// Function to delete an OSPF network
void ospf_network_delete(ospf_network_t *network)
{
    if (network == NULL)
    {
        return;
    }

    free(network);
    log_info("OSPF network deleted\n");
}