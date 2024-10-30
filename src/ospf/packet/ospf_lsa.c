#include "ospf_lsa.h"
#include "ospf_database.h" // Hypothetical database functions for lookup, add, and flood
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/**
 * create_lsa - Initializes an LSA with specified parameters.
 * @lsa: Pointer to the LSA structure to initialize.
 * @type: Type of LSA (e.g., ROUTER_LSA, NETWORK_LSA).
 * @link_state_id: Unique identifier for the LSA.
 * @advertising_router: ID of the advertising router.
 *
 * Allocates memory for the LSA data and sets initial fields.
 */
void create_lsa(ospf_lsa_t *lsa, ospf_lsa_type_t type, uint32_t link_state_id, uint32_t advertising_router)
{
    if (!lsa)
    {
        fprintf(stderr, "Error: Null LSA pointer passed to create_lsa.\n");
        return;
    }

    lsa->type = type;
    lsa->link_state_id = link_state_id;
    lsa->advertising_router = advertising_router;
    lsa->sequence_number = 0;
    lsa->age = 0;
    lsa->checksum = 0;
    lsa->length = 0;
    lsa->data = (uint8_t *)malloc(256);

    if (!lsa->data)
    {
        fprintf(stderr, "Error: Memory allocation failed for LSA data.\n");
        exit(EXIT_FAILURE);
    }
    printf("LSA created - Type: %d, Link State ID: %u, Advertising Router: %u\n",
           type, link_state_id, advertising_router);
}

/**
 * age_lsa - Increments the age of an LSA to reflect time since origination.
 * @lsa: Pointer to the LSA to age.
 *
 * This function updates the age field in the LSA. If the age reaches
 * the maximum allowed, the LSA should be removed from the database.
 */
void age_lsa(ospf_lsa_t *lsa)
{
    if (!lsa)
        return;

    const uint16_t MAX_AGE = 3600;
    if (lsa->age < MAX_AGE)
    {
        lsa->age++;
    }
    else
    {
        printf("LSA ID %u expired and should be removed.\n", lsa->link_state_id);
    }
}

/**
 * validate_lsa - Validates the checksum and format of an LSA.
 * @lsa: Pointer to the LSA to validate.
 *
 * Returns: 1 if valid, 0 if invalid.
 */
int validate_lsa(const ospf_lsa_t *lsa)
{
    if (!lsa)
        return 0;

    uint16_t calculated_checksum = 0;
    for (int i = 0; i < lsa->length; i++)
    {
        calculated_checksum += lsa->data[i];
    }

    if (calculated_checksum != lsa->checksum)
    {
        fprintf(stderr, "Error: LSA ID %u failed checksum validation.\n", lsa->link_state_id);
        return 0;
    }

    printf("LSA ID %u validated successfully.\n", lsa->link_state_id);
    return 1;
}

/**
 * serialize_lsa - Serializes an LSA into a buffer for transmission.
 * @lsa: Pointer to the LSA to serialize.
 * @buffer: Pointer to the output buffer.
 * @buffer_size: Size of the output buffer.
 *
 * Returns: Number of bytes written on success, -1 on failure.
 */
int serialize_lsa(const ospf_lsa_t *lsa, uint8_t *buffer, size_t buffer_size)
{
    if (!lsa || !buffer)
        return -1;

    size_t required_size = sizeof(ospf_lsa_type_t) + sizeof(uint32_t) * 3 + sizeof(uint16_t) * 3 + lsa->length;
    if (buffer_size < required_size)
    {
        fprintf(stderr, "Error: Buffer too small for LSA serialization.\n");
        return -1;
    }

    size_t offset = 0;
    memcpy(buffer + offset, &lsa->type, sizeof(ospf_lsa_type_t));
    offset += sizeof(ospf_lsa_type_t);

    memcpy(buffer + offset, &lsa->link_state_id, sizeof(uint32_t));
    offset += sizeof(uint32_t);

    memcpy(buffer + offset, &lsa->advertising_router, sizeof(uint32_t));
    offset += sizeof(uint32_t);

    memcpy(buffer + offset, &lsa->sequence_number, sizeof(uint32_t));
    offset += sizeof(uint32_t);

    memcpy(buffer + offset, &lsa->age, sizeof(uint16_t));
    offset += sizeof(uint16_t);

    memcpy(buffer + offset, &lsa->checksum, sizeof(uint16_t));
    offset += sizeof(uint16_t);

    memcpy(buffer + offset, &lsa->length, sizeof(uint16_t));
    offset += sizeof(uint16_t);

    memcpy(buffer + offset, lsa->data, lsa->length);
    offset += lsa->length;

    printf("LSA ID %u serialized successfully, %zu bytes written.\n", lsa->link_state_id, offset);
    return offset;
}

/**
 * deserialize_lsa - Deserializes data from a buffer into an LSA structure.
 * @lsa: Pointer to the LSA structure to populate.
 * @buffer: Pointer to the buffer containing serialized LSA data.
 * @buffer_size: Size of the input buffer.
 *
 * Returns: 0 on success, -1 if deserialization fails.
 */
int deserialize_lsa(ospf_lsa_t *lsa, const uint8_t *buffer, size_t buffer_size)
{
    if (!lsa || !buffer)
        return -1;

    if (buffer_size < sizeof(ospf_lsa_type_t) + sizeof(uint32_t) * 3 + sizeof(uint16_t) * 3)
    {
        fprintf(stderr, "Error: Buffer size too small for LSA deserialization.\n");
        return -1;
    }

    size_t offset = 0;
    memcpy(&lsa->type, buffer + offset, sizeof(ospf_lsa_type_t));
    offset += sizeof(ospf_lsa_type_t);

    memcpy(&lsa->link_state_id, buffer + offset, sizeof(uint32_t));
    offset += sizeof(uint32_t);

    memcpy(&lsa->advertising_router, buffer + offset, sizeof(uint32_t));
    offset += sizeof(uint32_t);

    memcpy(&lsa->sequence_number, buffer + offset, sizeof(uint32_t));
    offset += sizeof(uint32_t);

    memcpy(&lsa->age, buffer + offset, sizeof(uint16_t));
    offset += sizeof(uint16_t);

    memcpy(&lsa->checksum, buffer + offset, sizeof(uint16_t));
    offset += sizeof(uint16_t);

    memcpy(&lsa->length, buffer + offset, sizeof(uint16_t));
    offset += sizeof(uint16_t);

    lsa->data = (uint8_t *)malloc(lsa->length);
    if (!lsa->data)
    {
        fprintf(stderr, "Error: Memory allocation failed for LSA data.\n");
        return -1;
    }
    memcpy(lsa->data, buffer + offset, lsa->length);

    printf("LSA ID %u deserialized successfully.\n", lsa->link_state_id);
    return 0;
}

/**
 * ospf_lsa_process - Processes an incoming LSA.
 * @lsa: Pointer to the LSA to be processed.
 * @interface_id: ID of the interface where the LSA was received.
 *
 * This function validates the incoming LSA, checks if it exists in the
 * database, and updates or adds it accordingly. If the LSA is new or
 * updated, it triggers flooding to other interfaces.
 */
void ospf_lsa_process(const ospf_lsa_t *lsa, int interface_id)
{
    if (!lsa)
    {
        fprintf(stderr, "Error: Null LSA passed to ospf_lsa_process.\n");
        return;
    }

    printf("Processing incoming LSA - LSA ID: %u, Type: %d, Advertising Router: %u\n",
           lsa->link_state_id, lsa->type, lsa->advertising_router);

    // Step 1: Validate the LSA
    if (!validate_lsa(lsa))
    {
        fprintf(stderr, "Error: LSA ID %u failed validation.\n", lsa->link_state_id);
        return;
    }

    // Step 2: Check for existing LSA in the database
    ospf_lsa_t *existing_lsa = ospf_database_lookup(lsa->link_state_id, lsa->advertising_router);
    if (existing_lsa)
    {
        // Step 3: Compare sequence numbers to determine if the LSA is newer
        if (lsa->sequence_number > existing_lsa->sequence_number)
        {
            printf("Updating existing LSA ID %u with newer version\n", lsa->link_state_id);
            memcpy(existing_lsa, lsa, sizeof(ospf_lsa_t));
            ospf_database_flood(lsa, interface_id); // Flood updated LSA
        }
        else
        {
            printf("Received older or identical LSA ID %u, no update required.\n", lsa->link_state_id);
        }
    }
    else
    {
        // Step 4: Add new LSA to the database
        printf("New LSA detected, adding to database: ID %u\n", lsa->link_state_id);
        ospf_database_add(lsa);
        ospf_database_flood(lsa, interface_id); // Flood new LSA to neighbors
    }
}
