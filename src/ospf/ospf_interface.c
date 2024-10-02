#include "ospf_interface.h"
#include "log.h"
#include <net/if.h>
#include <ifaddrs.h>
#include <string.h>

// 初始化所有活动的网络接口
void ospf_interface_init_all(ospf_instance_t *ospf)
{
    struct ifaddrs *ifaddr, *ifa;
    // 获取本地接口列表
    getifaddrs(&ifaddr);

    // 遍历接口列表
    for (ifa = ifaddr; ifa != NULL; ifa = ifa->ifa_next)
    {
        // 检查接口是否为活动状态
        if (!(ifa->ifa_flags & IFF_UP) || !(ifa->ifa_flags & IFF_RUNNING))
            continue;

        // 只处理 IPv4 接口
        if (ifa->ifa_addr->sa_family != AF_INET)
            continue;

        // 创建并初始化 OSPF 接口结构体
        ospf_interface_t *iface = xmalloc(sizeof(ospf_interface_t));
        strncpy(iface->name, ifa->ifa_name, IFNAMSIZ);
        iface->ip_addr = ((struct sockaddr_in *)ifa->ifa_addr)->sin_addr;
        iface->netmask = ((struct sockaddr_in *)ifa->ifa_netmask)->sin_addr;
        iface->sockfd = create_ospf_socket();

        // 绑定套接字到接口 IP 地址
        struct sockaddr_in addr = {0};
        addr.sin_family = AF_INET;
        addr.sin_addr = iface->ip_addr;
        bind_socket(iface->sockfd, &addr);

        // 加入 OSPF 多播组
        join_multicast_group(iface->sockfd, "224.0.0.5", iface->name);

        // 将接口添加到 OSPF 实例的接口列表
        iface->next = ospf->interfaces;
        ospf->interfaces = iface;

        // 创建线程，接收并处理接口上的 OSPF 包
        thread_t *recv_thread = xmalloc(sizeof(thread_t));
        thread_create(recv_thread, ospf_interface_receive_packet, iface);

        log_info("Initialized interface %s with IP %s",
                 iface->name, inet_ntoa(iface->ip_addr));
    }

    freeifaddrs(ifaddr);
}

// 接收并处理接口上的 OSPF 包
void *ospf_interface_receive_packet(void *arg)
{
    ospf_interface_t *iface = (ospf_interface_t *)arg;
    while (1)
    {
        unsigned char buffer[65535];
        // 接收数据包
        ssize_t len = recvfrom(iface->sockfd, buffer, sizeof(buffer), 0, NULL, NULL);
        if (len > 0)
        {
            // 解析 OSPF 包
            ospf_packet_t *pkt = parse_ospf_packet(buffer, len);
            if (pkt)
            {
                // 根据包类型进行处理
                switch (pkt->header.type)
                {
                case OSPF_HELLO:
                    // 处理 Hello 包
                    // 调用邻居管理模块处理
                    break;
                // 其他包类型处理
                default:
                    break;
                }
                // 释放解析后的包
                free_ospf_packet(pkt);
            }
        }
    }
    return NULL;
}
