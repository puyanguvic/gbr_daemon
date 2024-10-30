#include "../core/ospf_config.h"
#include "ospf_area.h"
#include <stdio.h>
#include <string.h>

static ospf_area_table_t area_table; /**< Static instance of the OSPF area table */

/**
 * ospf_area_table_init - Initializes the OSPF area table.
 *
 * Sets up the OSPF area table, clearing any existing entries and preparing
 * for the addition of areas. Logs a confirmation message upon initialization.
 */
void ospf_area_table_init()
{
    memset(&area_table, 0, sizeof(area_table));
    printf("OSPF Area Table initialized with capacity for up to %d areas.\n", MAX_AREAS);
}

/**
 * ospf_area_add - Adds a new OSPF area to the area table.
 * @area_id: Identifier for the new OSPF area
 * @is_stub: Indicates if the area is a stub area
 *
 * Adds an area to the OSPF area table if there is space available and logs
 * details about the addition. Prevents duplicate areas by checking for existing
 * entries with the same area ID.
 *
 * Returns: 0 on success, -1 if the area already exists or the table is full.
 */
int ospf_area_add(uint32_t area_id, int is_stub)
{
    if (area_table.count >= MAX_AREAS)
    {
        fprintf(stderr, "Error: Maximum area capacity reached.\n");
        return -1;
    }

    for (int i = 0; i < area_table.count; i++)
    {
        if (area_table.areas[i].area_id == area_id)
        {
            fprintf(stderr, "Error: Area with ID %u already exists.\n", area_id);
            return -1;
        }
    }

    ospf_area_t *area = &area_table.areas[area_table.count++];
    area->area_id = area_id;
    area->is_stub = is_stub;
    area->num_interfaces = 0;

    printf("OSPF Area Added - Area ID: %u, Stub: %d\n", area_id, is_stub);
    return 0;
}

/**
 * ospf_area_remove - Removes an OSPF area from the area table.
 * @area_id: Identifier of the OSPF area to be removed
 *
 * Searches for the specified area by its ID and removes it from the table if found.
 * Shifts remaining areas to maintain table continuity. Logs if the area is not found.
 *
 * Returns: 0 on success, -1 if the area was not found.
 */
int ospf_area_remove(uint32_t area_id)
{
    for (int i = 0; i < area_table.count; i++)
    {
        if (area_table.areas[i].area_id == area_id)
        {
            // Shift subsequent entries to fill the gap
            memmove(&area_table.areas[i], &area_table.areas[i + 1],
                    (area_table.count - i - 1) * sizeof(ospf_area_t));
            area_table.count--;
            printf("OSPF Area Removed - Area ID: %u\n", area_id);
            return 0;
        }
    }
    fprintf(stderr, "Error: Area ID %u not found in table.\n", area_id);
    return -1;
}

/**
 * ospf_area_update - Updates the OSPF area configurations.
 *
 * Processes recent configuration changes and reapplies area settings.
 * This function would typically be triggered by configuration updates
 * or interface state changes.
 */
void ospf_area_update()
{
    printf("Updating OSPF Area configurations...\n");
    // TODO: Implement configuration re-evaluation or state update logic for areas
}

/**
 * ospf_area_print - Displays the contents of the OSPF area table.
 * @table: Pointer to the OSPF area table structure to print
 *
 * Prints each area in the table, including its ID and stub status, in
 * a formatted table layout for readability.
 */
void ospf_area_print(const ospf_area_table_t *table)
{
    printf("OSPF Area Table:\n");
    printf("-------------------------------------------------------\n");
    printf("| %-10s | %-5s | %-13s |\n", "Area ID", "Stub", "Interfaces");
    printf("-------------------------------------------------------\n");

    for (int i = 0; i < table->count; i++)
    {
        printf("| %-10u | %-5d | %-13d |\n",
               table->areas[i].area_id,
               table->areas[i].is_stub,
               table->areas[i].num_interfaces);
    }
    printf("-------------------------------------------------------\n");
}
