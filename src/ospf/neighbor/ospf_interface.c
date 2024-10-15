#include "ospf_interface.h"
#include <string.h>
#include <stdio.h>

// 接口发现
int discover_interfaces(ospf_interface_t *interfaces, size_t max_interfaces)
{
    struct ifaddrs *ifaddr, *ifa;
    int n = 0;

    if (getifaddrs(&ifaddr) == -1)
    {
        perror("getifaddrs");
        return -1;
    }

    for (ifa = ifaddr; ifa != NULL && n < max_interfaces; ifa = ifa->ifa_next)
    {
        if (ifa->ifa_addr == NULL || ifa->ifa_addr->sa_family != AF_INET)
        {
            continue;
        }

        ospf_interface_t *iface = &interfaces[n];
        strncpy(iface->name, ifa->ifa_name, IFNAMSIZ);
        iface->ip_address = ((struct sockaddr_in *)ifa->ifa_addr)->sin_addr.s_addr;
        iface->network_mask = ((struct sockaddr_in *)ifa->ifa_netmask)->sin_addr.s_addr;
        iface->mtu = 1500; // 默认MTU，可以通过其他方式获取更准确的值
        iface->enabled = 1;
        n++;
    }

    freeifaddrs(ifaddr);
    return n;
}

// 接口配置
void configure_interface(ospf_interface_t *interface, uint16_t hello_interval, uint16_t dead_interval, int enable)
{
    interface->hello_interval = hello_interval;
    interface->dead_interval = dead_interval;
    interface->enabled = enable;
}

// 接口状态监控
void monitor_interface_status(ospf_interface_t *interface)
{
    // 模拟接口状态变化的监控逻辑，可以使用系统调用来真正监控接口状态
    if (interface->enabled)
    {
        printf("Interface %s is up.\n", interface->name);
    }
    else
    {
        printf("Interface %s is down.\n", interface->name);
    }
}