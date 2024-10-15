#ifndef OSPF_INTERFACE_H
#define OSPF_INTERFACE_H

#include <stdint.h>
#include <net/if.h>
#include <sys/ioctl.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <ifaddrs.h>

// OSPF接口结构
typedef struct
{
    char name[IFNAMSIZ];
    uint32_t ip_address;
    uint32_t network_mask;
    uint16_t mtu;
    uint16_t hello_interval;
    uint16_t dead_interval;
    int enabled;
} ospf_interface_t;

// 函数声明
int discover_interfaces(ospf_interface_t *interfaces, size_t max_interfaces);
void configure_interface(ospf_interface_t *interface, uint16_t hello_interval, uint16_t dead_interval, int enable);
void monitor_interface_status(ospf_interface_t *interface);

#endif // OSPF_INTERFACE_H