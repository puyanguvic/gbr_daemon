#ifndef OSPF_LSDB_H
#define OSPF_LSDB_H

#include "ospf_lsa.h"
#include <stdint.h>

#define LSDB_MAX_ENTRIES 1024 /**< Maximum number of LSAs in the database */

/**
 * ospf_lsdb_init - Initializes the OSPF Link-State Database.
 */
void ospf_lsdb_init();

/**
 * ospf_lsdb_lookup - Finds an LSA in the database by its link state ID and advertising router.
 * @link_state_id: The link-state ID of the LSA.
 * @advertising_router: The router ID of the router advertising the LSA.
 *
 * Returns: Pointer to the LSA if found, NULL otherwise.
 */
ospf_lsa_t *ospf_lsdb_lookup(uint32_t link_state_id, uint32_t advertising_router);

/**
 * ospf_lsdb_add - Adds or updates an LSA in the database.
 * @lsa: Pointer to the LSA to add or update.
 *
 * If an LSA with the same ID and advertising router exists, it is replaced.
 */
void ospf_lsdb_add(const ospf_lsa_t *lsa);

/**
 * ospf_lsdb_remove - Removes an LSA from the database by link state ID and advertising router.
 * @link_state_id: The link-state ID of the LSA to remove.
 * @advertising_router: The router ID of the router advertising the LSA.
 */
void ospf_lsdb_remove(uint32_t link_state_id, uint32_t advertising_router);

/**
 * ospf_lsdb_flood - Floods an LSA to neighboring routers on all interfaces except the receiving one.
 * @lsa: Pointer to the LSA to flood.
 * @received_interface_id: The ID of the interface that received the LSA, to avoid sending it back.
 */
void ospf_lsdb_flood(const ospf_lsa_t *lsa, int received_interface_id);

/**
 * ospf_lsdb_print - Prints the entire LSDB contents for debugging.
 */
void ospf_lsdb_print();

#endif // OSPF_LSDB_H
