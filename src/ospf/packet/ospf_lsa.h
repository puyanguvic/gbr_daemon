#ifndef OSPF_LSA_H
#define OSPF_LSA_H

#include <stdint.h>
#include <stddef.h>
#include <stdlib.h> /**< For memory management functions */

/**
 * enum ospf_lsa_type_t - Defines the types of OSPF LSAs.
 * @ROUTER_LSA: Router-LSA describing a router's links.
 * @NETWORK_LSA: Network-LSA describing a multi-access network.
 * @SUMMARY_LSA: Summary-LSA for aggregating network information.
 * @AS_EXTERNAL_LSA: AS-External-LSA describing external routes to an AS.
 */
typedef enum
{
    ROUTER_LSA,
    NETWORK_LSA,
    SUMMARY_LSA,
    AS_EXTERNAL_LSA
} ospf_lsa_type_t;

/**
 * struct ospf_lsa_t - Represents an OSPF Link-State Advertisement (LSA).
 * @type: Type of the LSA, indicating the LSA's role in OSPF.
 * @link_state_id: Unique identifier for the LSA.
 * @advertising_router: Router ID of the router advertising the LSA.
 * @sequence_number: Sequence number of the LSA for versioning.
 * @age: Time in seconds since the LSA was originated or refreshed.
 * @checksum: Validation checksum of the LSA.
 * @length: Length of the LSA, including headers and data.
 * @data: Pointer to the LSA-specific data.
 *
 * This structure defines an OSPF LSA, which is used to distribute
 * routing information within an OSPF network. The LSA data structure
 * stores critical information, including identifiers, versioning data,
 * and a pointer to dynamically allocated memory for specific LSA data.
 */
typedef struct
{
    ospf_lsa_type_t type;
    uint32_t link_state_id;
    uint32_t advertising_router;
    uint32_t sequence_number;
    uint16_t age;
    uint16_t checksum;
    uint16_t length;
    uint8_t *data; /**< Pointer to the data payload of the LSA */
} ospf_lsa_t;

/* Function declarations for managing and processing LSAs */

/**
 * create_lsa - Initializes an LSA with specified parameters.
 * @lsa: Pointer to the LSA structure to initialize.
 * @type: Type of LSA (e.g., ROUTER_LSA, NETWORK_LSA).
 * @link_state_id: Unique identifier for the LSA.
 * @advertising_router: ID of the advertising router.
 *
 * Allocates memory for the LSA data and sets initial fields.
 */
void create_lsa(ospf_lsa_t *lsa, ospf_lsa_type_t type, uint32_t link_state_id, uint32_t advertising_router);

/**
 * age_lsa - Increments the age of an LSA to reflect time since origination.
 * @lsa: Pointer to the LSA to age.
 *
 * This function updates the age field in the LSA. If the age reaches
 * the maximum allowed, the LSA should be removed from the database.
 */
void age_lsa(ospf_lsa_t *lsa);

/**
 * validate_lsa - Validates the checksum and format of an LSA.
 * @lsa: Pointer to the LSA to validate.
 *
 * Returns: 1 if valid, 0 if invalid.
 */
int validate_lsa(const ospf_lsa_t *lsa);

/**
 * serialize_lsa - Serializes an LSA into a buffer for transmission.
 * @lsa: Pointer to the LSA to serialize.
 * @buffer: Pointer to the output buffer.
 * @buffer_size: Size of the output buffer.
 *
 * Returns: Number of bytes written on success, -1 on failure.
 */
int serialize_lsa(const ospf_lsa_t *lsa, uint8_t *buffer, size_t buffer_size);

/**
 * deserialize_lsa - Deserializes data from a buffer into an LSA structure.
 * @lsa: Pointer to the LSA structure to populate.
 * @buffer: Pointer to the buffer containing serialized LSA data.
 * @buffer_size: Size of the input buffer.
 *
 * Returns: 0 on success, -1 if deserialization fails.
 */
int deserialize_lsa(ospf_lsa_t *lsa, const uint8_t *buffer, size_t buffer_size);

/**
 * ospf_lsa_process - Processes an incoming LSA.
 * @lsa: Pointer to the LSA to be processed.
 * @interface_id: ID of the interface where the LSA was received.
 *
 * This function is responsible for validating, storing, or updating
 * LSAs in the OSPF database and initiating flooding if necessary.
 */
void ospf_lsa_process(const ospf_lsa_t *lsa, int interface_id);

#endif // OSPF_LSA_H
