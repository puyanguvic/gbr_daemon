#include "ospf/area/ospf_area.h"
#include "log.h"
#include <assert.h>
#include <stdio.h>

void test_ospf_area_create()
{
    ospf_area_t *area = ospf_area_create(1);
    assert(area != NULL);
    assert(area->area_id == 1);
    assert(area->network_list == NULL);
    ospf_area_delete(area);
    printf("test_ospf_area_create passed\n");
}

void test_ospf_area_add_network()
{
    ospf_area_t *area = ospf_area_create(1);
    ospf_network_t *network = ospf_network_create("192.168.1.0/24");
    int result = ospf_area_add_network(area, network);
    assert(result == 0);
    assert(area->network_list == network);
    ospf_area_delete(area);
    printf("test_ospf_area_add_network passed\n");
}

void test_ospf_area_delete()
{
    ospf_area_t *area = ospf_area_create(1);
    ospf_network_t *network1 = ospf_network_create("192.168.1.0/24");
    ospf_network_t *network2 = ospf_network_create("10.0.0.0/8");
    ospf_area_add_network(area, network1);
    ospf_area_add_network(area, network2);
    ospf_area_delete(area);
    printf("test_ospf_area_delete passed\n");
}

int main()
{
    test_ospf_area_create();
    test_ospf_area_add_network();
    test_ospf_area_delete();
    return 0;
}
