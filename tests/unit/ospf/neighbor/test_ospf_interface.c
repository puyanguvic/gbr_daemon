#include "ospf_interface.h"
#include <stdio.h>

int main(void)
{
    printf("Running test_ospf_interface...\n");

    // 测试接口发现
    ospf_interface_t interfaces[10];
    int num_interfaces = discover_interfaces(interfaces, 10);
    if (num_interfaces < 0)
    {
        printf("discover_interfaces failed.\n");
        return 1;
    }
    printf("Discovered %d interfaces.\n", num_interfaces);

    // 测试接口配置
    if (num_interfaces > 0)
    {
        configure_interface(&interfaces[0], 10, 40, 1);
        if (interfaces[0].hello_interval != 10 || interfaces[0].dead_interval != 40 || !interfaces[0].enabled)
        {
            printf("configure_interface failed.\n");
            return 1;
        }
    }

    // 测试接口状态监控
    if (num_interfaces > 0)
    {
        monitor_interface_status(&interfaces[0]);
    }

    printf("All ospf_interface tests passed.\n");
    return 0;
}