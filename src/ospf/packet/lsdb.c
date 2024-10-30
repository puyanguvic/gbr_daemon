#include "lsdb.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

static ospf_lsa_t lsdb[LSDB_MAX_ENTRIES]; /**< In-memory array to store LSAs */
static int lsdb_count = 0;                /**< Current count of entries in the LSDB */

/**
 * ospf_lsdb_init - Initializes the OSPF Link-State Database.
 */
void ospf_lsdb_init()
{
    lsdb_count = 0;
    memset(lsdb, 0, sizeof(lsdb));
    printf("OSPF LSDB initialized.\n");
}

/**
 * ospf_lsdb_lookup - Finds an LSA in the database by its link state ID and advertising router.
 * @link_state_id: The link-state ID of the LSA.
 * @advertising_router: The router ID of the router advertising the LSA.
 *
 * Returns: Pointer to the LSA if found, NULL otherwise.
 */
ospf_lsa_t *ospf_lsdb_lookup(uint32_t link_state_id, uint32_t advertising_router)
{
    for (int i = 0; i < lsdb_count; i++)
    {
        if (lsdb[i].link_state_id == link_state_id &&
            lsdb[i].advertising_router == advertising_router)
        {
            return &lsdb[i];
        }
    }
    return NULL;
}

/**
 * ospf_lsdb_add - Adds or updates an LSA in the database.
 * @lsa: Pointer to the LSA to add or update.
 *
 * If an LSA with the same ID and advertising router exists, it is replaced.
 */
void ospf_lsdb_add(const ospf_lsa_t *lsa)
{
    ospf_lsa_t *existing_lsa = ospf_lsdb_lookup(lsa->link_state_id, lsa->advertising_router);

    if (existing_lsa)
    {
        // Replace the existing LSA
        free(existing_lsa->data); // Free the previous data
        *existing_lsa = *lsa;
        existing_lsa->data = malloc(lsa->length);
        memcpy(existing_lsa->data, lsa->data, lsa->length);
        printf("Updated existing LSA in LSDB: ID %u\n", lsa->link_state_id);
    }
    else if (lsdb_count < LSDB_MAX_ENTRIES)
    {
        // Add new LSA to the database
        lsdb[lsdb_count] = *lsa;
        lsdb[lsdb_count].data = malloc(lsa->length);
        memcpy(lsdb[lsdb_count].data, lsa->data, lsa->length);
        lsdb_count++;
        printf("Added new LSA to LSDB: ID %u\n", lsa->link_state_id);
    }
    else
    {
        fprintf(stderr, "Error: LSDB is full, cannot add LSA ID %u.\n", lsa->link_state_id);
    }
}

/**
 * ospf_lsdb_remove - Removes an LSA from the database by link state ID and advertising router.
 * @link_state_id: The link-state ID of the LSA to remove.
 * @advertising_router: The router ID of the router advertising the LSA.
 */
void ospf_lsdb_remove(uint32_t link_state_id, uint32_t advertising_router)
{
    for (int i = 0; i < lsdb_count; i++)
    {
        if (lsdb[i].link_state_id == link_state_id &&
            lsdb[i].advertising_router == advertising_router)
        {
            free(lsdb[i].data); // Free allocated data

            // Shift the remaining entries to fill the gap
            for (int j = i; j < lsdb_count - 1; j++)
            {
                lsdb[j] = lsdb[j + 1];
            }
            lsdb_count--;
            printf("Removed LSA from LSDB: ID %u\n", link_state_id);
            return;
        }
    }
    printf("LSA ID %u not found in LSDB.\n", link_state_id);
}

/**
 * ospf_lsdb_flood - Floods an LSA to neighboring routers on all interfaces except the receiving one.
 * @lsa: Pointer to the LSA to flood.
 * @received_interface_id: The ID of the interface that received the LSA, to avoid sending it back.
 *
 * This function simulates flooding to other interfaces.
 */
void ospf_lsdb_flood(const ospf_lsa_t *lsa, int received_interface_id)
{
    // In a real implementation, this would interact with neighbor interfaces
    printf("Flooding LSA ID %u to neighbors, except on interface %d\n", lsa->link_state_id, received_interface_id);
    // TODO: Implement actual flooding logic as per neighbor communication requirements
}

/**
 * ospf_lsdb_print - Prints the entire LSDB contents for debugging.
 */
void ospf_lsdb_print()
{
    printf("OSPF LSDB - Total Entries: %d\n", lsdb_count);
    for (int i = 0; i < lsdb_count; i++)
    {
        printf("LSA ID %u, Advertising Router %u, Type %d, Seq No %u, Age %u\n",
               lsdb[i].link_state_id, lsdb[i].advertising_router, lsdb[i].type,
               lsdb[i].sequence_number, lsdb[i].age);
    }
}
