#include "ospf_config.h"
#include <stdio.h>

static ospf_config_t ospf_config; // Static configuration variable

/**
 * ospf_config_load - Load OSPF configuration from a file
 * @filename: Path to the configuration file
 *
 * Reads and populates the static `ospf_config` variable.
 * Returns 0 on success, -1 on error.
 */
int ospf_config_load(const char *filename)
{
    printf("Loading OSPF configuration from %s...\n", filename);

    // Example of loading configuration values (placeholder logic)
    ospf_config.area_id = 0;
    snprintf(ospf_config.interface, sizeof(ospf_config.interface), "eth0");
    snprintf(ospf_config.authentication_key, sizeof(ospf_config.authentication_key), "default_key");
    ospf_config.hello_interval = 10;
    ospf_config.dead_interval = 40;

    return 0; // Return 0 on successful load
}

/**
 * ospf_config_apply - Apply OSPF configuration to the instance
 *
 * Uses the values in `ospf_config` to configure the OSPF instance.
 * Returns 0 on success, -1 on error.
 */
int ospf_config_apply()
{
    printf("Applying OSPF configuration...\n");
    // Example application logic using ospf_config values
    printf("Area ID: %u\n", ospf_config.area_id);
    printf("Interface: %s\n", ospf_config.interface);
    printf("Authentication Key: %s\n", ospf_config.authentication_key);
    printf("Hello Interval: %d\n", ospf_config.hello_interval);
    printf("Dead Interval: %d\n", ospf_config.dead_interval);

    // Apply logic here (e.g., to network interfaces or OSPF modules)

    return 0;
}

/**
 * ospf_config_update - Reload and apply updated configuration
 *
 * Reloads the configuration from the existing file and reapplies it.
 * Returns 0 on success, -1 on error.
 */
int ospf_config_update()
{
    if (ospf_config_load("ospf.conf") == 0)
    {
        return ospf_config_apply();
    }
    return -1;
}

/**
 * get_ospf_config - Retrieve the static OSPF configuration
 *
 * Returns a constant pointer to the static `ospf_config`.
 */
const ospf_config_t *get_ospf_config()
{
    return &ospf_config;
}
