#include "prefix.h"
#include <string.h>
#include <arpa/inet.h>
#include <stdio.h>

/**
 * @brief Initialize a prefix with IPv4 address and prefix length.
 */
bool prefix_init_ipv4(prefix_t *p, struct in_addr addr, uint8_t prefixlen)
{
    if (!p || prefixlen > 32)
    {
        return false;
    }
    p->family = PREFIX_FAMILY_IPV4;
    p->addr.ipv4 = addr;
    p->prefixlen = prefixlen;
    return true;
}

/**
 * @brief Initialize a prefix with IPv6 address and prefix length.
 */
bool prefix_init_ipv6(prefix_t *p, struct in6_addr addr, uint8_t prefixlen)
{
    if (!p || prefixlen > 128)
    {
        return false;
    }
    p->family = PREFIX_FAMILY_IPV6;
    p->addr.ipv6 = addr;
    p->prefixlen = prefixlen;
    return true;
}

/**
 * @brief Convert prefix to string representation.
 */
char *prefix_to_str(const prefix_t *p, char *buffer, size_t buflen)
{
    if (!p || !buffer || buflen == 0)
    {
        return NULL;
    }
    char addr_str[INET6_ADDRSTRLEN];
    const char *res = NULL;

    if (p->family == PREFIX_FAMILY_IPV4)
    {
        res = inet_ntop(AF_INET, &p->addr.ipv4, addr_str, sizeof(addr_str));
    }
    else if (p->family == PREFIX_FAMILY_IPV6)
    {
        res = inet_ntop(AF_INET6, &p->addr.ipv6, addr_str, sizeof(addr_str));
    }
    else
    {
        return NULL;
    }

    if (!res)
    {
        return NULL;
    }

    snprintf(buffer, buflen, "%s/%u", addr_str, p->prefixlen);
    return buffer;
}

/**
 * @brief Check if two prefixes are equal.
 */
bool prefix_equal(const prefix_t *p1, const prefix_t *p2)
{
    if (!p1 || !p2 || p1->family != p2->family || p1->prefixlen != p2->prefixlen)
    {
        return false;
    }

    if (p1->family == PREFIX_FAMILY_IPV4)
    {
        uint32_t mask = htonl(~((1U << (32 - p1->prefixlen)) - 1));
        return (p1->addr.ipv4.s_addr & mask) == (p2->addr.ipv4.s_addr & mask);
    }
    else if (p1->family == PREFIX_FAMILY_IPV6)
    {
        uint8_t bytes = p1->prefixlen / 8;
        uint8_t bits = p1->prefixlen % 8;

        if (bytes > 0 && memcmp(&p1->addr.ipv6, &p2->addr.ipv6, bytes) != 0)
        {
            return false;
        }

        if (bits > 0)
        {
            uint8_t mask = (~0U) << (8 - bits);
            if (((uint8_t *)&p1->addr.ipv6)[bytes] & mask != ((uint8_t *)&p2->addr.ipv6)[bytes] & mask)
            {
                return false;
            }
        }
        return true;
    }

    return false;
}

/**
 * @brief Check if one prefix contains another prefix.
 */
bool prefix_contains(const prefix_t *p, const prefix_t *sub)
{
    if (!p || !sub || p->family != sub->family || p->prefixlen > sub->prefixlen)
    {
        return false;
    }

    if (p->family == PREFIX_FAMILY_IPV4)
    {
        uint32_t mask = htonl(~((1U << (32 - p->prefixlen)) - 1));
        return (p->addr.ipv4.s_addr & mask) == (sub->addr.ipv4.s_addr & mask);
    }
    else if (p->family == PREFIX_FAMILY_IPV6)
    {
        uint8_t bytes = p->prefixlen / 8;
        uint8_t bits = p->prefixlen % 8;

        if (bytes > 0 && memcmp(&p->addr.ipv6, &sub->addr.ipv6, bytes) != 0)
        {
            return false;
        }

        if (bits > 0)
        {
            uint8_t mask = (~0U) << (8 - bits);
            if (((uint8_t *)&p->addr.ipv6)[bytes] & mask != ((uint8_t *)&sub->addr.ipv6)[bytes] & mask)
            {
                return false;
            }
        }
        return true;
    }

    return false;
}

/**
 * @brief Convert CIDR prefix length to netmask (IPv4 only).
 */
uint32_t prefixlen_to_netmask_ipv4(uint8_t prefixlen)
{
    if (prefixlen > 32)
    {
        return 0;
    }
    if (prefixlen == 0)
    {
        return 0;
    }
    uint32_t mask = ~((1U << (32 - prefixlen)) - 1);
    return htonl(mask);
}

/**
 * @brief Convert netmask to CIDR prefix length (IPv4 only).
 */
uint8_t netmask_to_prefixlen_ipv4(uint32_t netmask)
{
    netmask = ntohl(netmask);
    uint8_t prefixlen = 0;
    uint32_t mask = 0x80000000;

    while (mask != 0 && (netmask & mask))
    {
        prefixlen++;
        mask >>= 1;
    }

    // Check if the rest of the bits are zero (valid netmask)
    if ((netmask << prefixlen) != 0)
    {
        return 255; // Invalid netmask
    }

    return prefixlen;
}
