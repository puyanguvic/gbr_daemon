#include "network.h"
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdio.h>
#include <net/if.h>
#include <unistd.h>

// 创建用于 OSPF 的原始套接字
int create_ospf_socket()
{
    // 创建原始套接字，使用 IPPROTO_OSPF（89）协议
    int sockfd = socket(AF_INET, SOCK_RAW, IPPROTO_OSPF);
    if (sockfd < 0)
    {
        perror("socket");
        return -1;
    }
    // 设置套接字选项，以便操作 IP 头部
    int on = 1;
    if (setsockopt(sockfd, IPPROTO_IP, IP_HDRINCL, &on, sizeof(on)) < 0)
    {
        perror("setsockopt");
        close(sockfd);
        return -1;
    }
    return sockfd;
}

// 绑定套接字到指定的 IP 地址
int bind_socket(int sockfd, struct sockaddr_in *addr)
{
    if (bind(sockfd, (struct sockaddr *)addr, sizeof(*addr)) < 0)
    {
        perror("bind");
        return -1;
    }
    return 0;
}

// 加入指定的多播组
int join_multicast_group(int sockfd, const char *multicast_ip, const char *interface)
{
    struct ip_mreqn mreq;
    memset(&mreq, 0, sizeof(mreq));
    inet_aton(multicast_ip, &mreq.imr_multiaddr); // 设置多播地址
    mreq.imr_address.s_addr = htonl(INADDR_ANY);  // 接收所有本地接口的数据
    mreq.imr_ifindex = if_nametoindex(interface); // 指定网络接口

    if (setsockopt(sockfd, IPPROTO_IP, IP_ADD_MEMBERSHIP, &mreq, sizeof(mreq)) < 0)
    {
        perror("setsockopt");
        return -1;
    }
    return 0;
}
