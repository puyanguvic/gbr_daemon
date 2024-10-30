#ifndef OSPF_CONFIG_H
#define OSPF_CONFIG_H

#include <stdint.h>

// Define configuration structure for OSPF settings
typedef struct
{
    uint32_t area_id;
    char interface[32];
    char authentication_key[64];
    int hello_interval;
    int dead_interval;
} ospf_config_t;

// Function prototypes
int ospf_config_load(const char *filename);
int ospf_config_apply();
int ospf_config_update();
const ospf_config_t *get_ospf_config(); // Function to access configuration

#endif // OSPF_CONFIG_H
