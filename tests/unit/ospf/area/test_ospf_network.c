#include "ospf/area/ospf_network.h"
#include "log.h"
#include <assert.h>
#include <stdio.h>

void test_ospf_network_create()
{
    ospf_network_t *network = ospf_network_create("192.168.1.0/24");
    assert(network != NULL);
    assert(network->network_prefix != NULL);
    assert(network->next == NULL);
    ospf_network_delete(network);
    printf("test_ospf_network_create passed\n");
}

void test_ospf_network_delete()
{
    ospf_network_t *network = ospf_network_create("192.168.1.0/24");
    ospf_network_delete(network);
    printf("test_ospf_network_delete passed\n");
}

int main()
{
    test_ospf_network_create();
    test_ospf_network_delete();
    return 0;
}
