#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
#include "prefix.h"

int main(void)
{
    printf("Running prefix module tests...\n");

    char buffer[INET6_ADDRSTRLEN + 4]; // Enough to hold address and prefix length

    // Test IPv4 prefix initialization and conversion
    struct in_addr ipv4_addr;
    inet_pton(AF_INET, "192.168.1.0", &ipv4_addr);

    prefix_t p_ipv4;
    if (!prefix_init_ipv4(&p_ipv4, ipv4_addr, 24))
    {
        printf("Failed to initialize IPv4 prefix.\n");
        return 1;
    }

    if (!prefix_to_str(&p_ipv4, buffer, sizeof(buffer)))
    {
        printf("Failed to convert IPv4 prefix to string.\n");
        return 1;
    }
    printf("IPv4 Prefix: %s\n", buffer);

    // Test IPv4 netmask conversion
    uint32_t netmask = prefixlen_to_netmask_ipv4(p_ipv4.prefixlen);
    if (netmask == 0)
    {
        printf("Failed to convert prefix length to netmask.\n");
        return 1;
    }
    printf("Netmask: %s\n", inet_ntoa(*(struct in_addr *)&netmask));

    uint8_t prefixlen = netmask_to_prefixlen_ipv4(netmask);
    if (prefixlen == 255)
    {
        printf("Invalid netmask detected.\n");
        return 1;
    }
    printf("Prefix Length from Netmask: %u\n", prefixlen);

    // Test IPv4 prefix comparison and containment
    struct in_addr ipv4_subnet_addr;
    inet_pton(AF_INET, "192.168.1.128", &ipv4_subnet_addr);

    prefix_t p_ipv4_subnet;
    prefix_init_ipv4(&p_ipv4_subnet, ipv4_subnet_addr, 25);

    if (prefix_contains(&p_ipv4, &p_ipv4_subnet))
    {
        printf("IPv4 prefix containment test passed.\n");
    }
    else
    {
        printf("IPv4 prefix containment test failed.\n");
        return 1;
    }

    // Test IPv6 prefix initialization and conversion
    struct in6_addr ipv6_addr;
    inet_pton(AF_INET6, "2001:db8::", &ipv6_addr);

    prefix_t p_ipv6;
    if (!prefix_init_ipv6(&p_ipv6, ipv6_addr, 32))
    {
        printf("Failed to initialize IPv6 prefix.\n");
        return 1;
    }

    if (!prefix_to_str(&p_ipv6, buffer, sizeof(buffer)))
    {
        printf("Failed to convert IPv6 prefix to string.\n");
        return 1;
    }
    printf("IPv6 Prefix: %s\n", buffer);

    // Test IPv6 prefix comparison and containment
    struct in6_addr ipv6_subnet_addr;
    inet_pton(AF_INET6, "2001:db8::1", &ipv6_subnet_addr);

    prefix_t p_ipv6_subnet;
    prefix_init_ipv6(&p_ipv6_subnet, ipv6_subnet_addr, 64);

    if (prefix_contains(&p_ipv6, &p_ipv6_subnet))
    {
        printf("IPv6 prefix containment test passed.\n");
    }
    else
    {
        printf("IPv6 prefix containment test failed.\n");
        return 1;
    }

    // Test invalid prefix lengths
    if (prefix_init_ipv4(&p_ipv4, ipv4_addr, 33))
    {
        printf("Invalid IPv4 prefix length accepted (should not happen).\n");
        return 1;
    }

    if (prefix_init_ipv6(&p_ipv6, ipv6_addr, 129))
    {
        printf("Invalid IPv6 prefix length accepted (should not happen).\n");
        return 1;
    }

    printf("All prefix module tests passed.\n");
    return 0;
}
