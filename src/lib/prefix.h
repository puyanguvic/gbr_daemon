#ifndef PREFIX_H
#define PREFIX_H

#include <stdint.h>
#include <stdbool.h>
#include <netinet/in.h>

/**
 * @brief Enum to specify the IP address family.
 */
typedef enum
{
    PREFIX_FAMILY_IPV4,
    PREFIX_FAMILY_IPV6
} prefix_family_t;

/**
 * @brief Structure representing an IP prefix.
 */
typedef struct
{
    prefix_family_t family; // Address family (IPv4 or IPv6)
    union
    {
        struct in_addr ipv4;  // IPv4 address
        struct in6_addr ipv6; // IPv6 address
    } addr;                   // IP address
    uint8_t prefixlen;        // Prefix length
} prefix_t;

/**
 * @brief Initialize a prefix with IPv4 address and prefix length.
 *
 * @param p Pointer to the prefix structure.
 * @param addr IPv4 address in network byte order.
 * @param prefixlen Prefix length (0-32).
 * @return True on success, false on failure.
 */
bool prefix_init_ipv4(prefix_t *p, struct in_addr addr, uint8_t prefixlen);

/**
 * @brief Initialize a prefix with IPv6 address and prefix length.
 *
 * @param p Pointer to the prefix structure.
 * @param addr IPv6 address in network byte order.
 * @param prefixlen Prefix length (0-128).
 * @return True on success, false on failure.
 */
bool prefix_init_ipv6(prefix_t *p, struct in6_addr addr, uint8_t prefixlen);

/**
 * @brief Convert prefix to string representation (e.g., "192.168.1.0/24").
 *
 * @param p Pointer to the prefix structure.
 * @param buffer Buffer to store the string.
 * @param buflen Length of the buffer.
 * @return Pointer to the buffer, or NULL on failure.
 */
char *prefix_to_str(const prefix_t *p, char *buffer, size_t buflen);

/**
 * @brief Check if two prefixes are equal.
 *
 * @param p1 Pointer to the first prefix.
 * @param p2 Pointer to the second prefix.
 * @return True if equal, false otherwise.
 */
bool prefix_equal(const prefix_t *p1, const prefix_t *p2);

/**
 * @brief Check if one prefix contains another prefix.
 *
 * @param p Pointer to the parent prefix.
 * @param sub Pointer to the sub-prefix.
 * @return True if 'p' contains 'sub', false otherwise.
 */
bool prefix_contains(const prefix_t *p, const prefix_t *sub);

/**
 * @brief Convert CIDR prefix length to netmask (IPv4 only).
 *
 * @param prefixlen Prefix length (0-32).
 * @return Netmask in network byte order.
 */
uint32_t prefixlen_to_netmask_ipv4(uint8_t prefixlen);

/**
 * @brief Convert netmask to CIDR prefix length (IPv4 only).
 *
 * @param netmask Netmask in network byte order.
 * @return Prefix length (0-32), or 255 on error.
 */
uint8_t netmask_to_prefixlen_ipv4(uint32_t netmask);

#endif // PREFIX_H
