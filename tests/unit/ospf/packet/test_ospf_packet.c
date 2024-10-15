#include "ospf/packet/ospf_packet.h"
#include <stdio.h>
#include <string.h>
#include <arpa/inet.h> // 添加 htons 和 ntohs 的定义

int main(void)
{
    printf("Running test_ospf_packet...\n");

    // 测试解析OSPF通用报头
    uint8_t packet[] = {
        0x02, 0x01, 0x00, 0x24, 0xC0, 0xA8, 0x01, 0x01, 0x00, 0x00, 0x00, 0x01,
        0x12, 0x34, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00};
    ospf_header_t header;
    parse_ospf_header(packet, &header);
    if (header.version != 2 || header.type != 1 || header.packet_length != 36 ||
        header.router_id != 0xC0A80101 || header.area_id != 0x00000001 ||
        header.checksum != 0x1234)
    {
        printf("test_parse_ospf_header failed.\n");
        return 1;
    }

    // 测试创建OSPF Hello包
    ospf_hello_t hello_packet;
    create_ospf_hello_packet(&hello_packet, 0xFFFFFF00, 10);
    if (ntohs(hello_packet.hello_interval) != 10)
    {
        printf("test_create_ospf_hello_packet failed.\n");
        return 1;
    }

    printf("All ospf_packet tests passed.\n");
    return 0;
}