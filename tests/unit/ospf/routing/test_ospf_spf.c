#include "ospf_spf.h"
#include <stdio.h>

void test_ospf_spf()
{
    OSPFRouter router;
    init_router(&router);

    // Test SPF calculation
    spf_calculate(&router);
    printf("SPF calculation test completed.\n");
}

int main()
{
    printf("Running OSPF SPF tests...\n");
    test_ospf_spf();
    return 0;
}
