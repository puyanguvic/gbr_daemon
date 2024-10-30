#ifndef OSPF_AREA_H
#define OSPF_AREA_H

#include <stdint.h>
#include <netinet/in.h>

#define MAX_AREAS 128 /**< Maximum number of OSPF areas supported */

/**
 * struct ospf_area_t - Represents an OSPF area.
 * @area_id: Unique identifier for the OSPF area.
 * @is_stub: Indicates if this area is a stub area (1 = true, 0 = false).
 * @interfaces: List of interfaces associated with the area.
 * @num_interfaces: Number of interfaces in the area.
 *
 * This structure holds key information about an OSPF area,
 * including its identifier, stub status, and associated interfaces.
 */
typedef struct
{
    uint32_t area_id;
    int is_stub;
    struct in_addr interfaces[MAX_AREAS]; /**< IP addresses of associated interfaces */
    int num_interfaces;
} ospf_area_t;

/**
 * struct ospf_area_table_t - OSPF area table for managing multiple areas.
 * @areas: Array of defined OSPF areas.
 * @count: Number of active areas in the table.
 *
 * This structure provides a centralized table for managing multiple OSPF areas.
 */
typedef struct
{
    ospf_area_t areas[MAX_AREAS];
    int count;
} ospf_area_table_t;

/* Function declarations for OSPF area management */
void ospf_area_table_init();                          /**< Initializes the OSPF area table */
int ospf_area_add(uint32_t area_id, int is_stub);     /**< Adds a new area to the OSPF table */
int ospf_area_remove(uint32_t area_id);               /**< Removes an area from the OSPF table */
void ospf_area_update();                              /**< Updates the OSPF area configurations */
void ospf_area_print(const ospf_area_table_t *table); /**< Prints the OSPF area table */

#endif // OSPF_AREA_H
