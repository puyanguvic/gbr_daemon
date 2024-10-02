#ifndef OSPF_INTERFACE_H
#define OSPF_INTERFACE_H

#include <netinet/in.h>
#include "network.h"
#include "thread.h"
#include "ospf_packet.h"

// 定义 OSPF 接口结构体
typedef struct ospf_interface
{
    char name[IFNAMSIZ];         // 接口名称
    int sockfd;                  // 套接字文件描述符
    struct in_addr ip_addr;      // 接口 IP 地址
    struct in_addr netmask;      // 子网掩码
    struct ospf_interface *next; // 指向下一个接口（链表）
    // 其他接口信息，如 MTU、HelloInterval 等
} ospf_interface_t;

// 初始化所有活动接口
void ospf_interface_init_all(ospf_instance_t *ospf);

// 接收并处理从接口收到的 OSPF 包
void *ospf_interface_receive_packet(void *arg);

#endif // OSPF_INTERFACE_H
