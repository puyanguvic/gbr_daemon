/*
 * OSPF Daemon
 *
 * (c) 2024 Pu Yang <email@example.com>
 *
 * This program is distributed under the terms of the GNU General Public License.
 */

/**
 * DOC: Open Shortest Path First (OSPF)
 *
 * This file implements the main entry point for the OSPF daemon, handling
 * initialization, event processing, and shutdown. It interacts with multiple
 * OSPF modules to achieve complete protocol functionality.
 */

#include "../ospf/core/ospf_main.h"
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <poll.h>

static volatile int keep_running = 1; // Control daemon lifecycle

// Signal handler for managing graceful shutdown on SIGINT or SIGTERM
void handle_signal(int sig)
{
    if (sig == SIGINT || sig == SIGTERM)
    {
        keep_running = 0;
    }
}

/**
 * ospf_init - Initializes the OSPF daemon with a given configuration file.
 * @config_file: Path to the OSPF configuration file.
 *
 * This function sets up the OSPF daemon by loading the configuration,
 * initializing key OSPF data structures, and preparing the daemon
 * for protocol operation.
 */
void ospf_init(const char *config_file)
{
    printf("Initializing OSPF Daemon...\n");

    // Load the configuration
    if (ospf_config_load(config_file) != 0)
    {
        fprintf(stderr, "Failed to load OSPF configuration.\n");
        return;
    }

    // Access the configuration through the getter function
    const ospf_config_t *config = get_ospf_config();
    printf("Loaded OSPF Configuration:\n");
    printf("  Area ID: %u\n", config->area_id);
    printf("  Interface: %s\n", config->interface);
    printf("  Authentication Key: %s\n", config->authentication_key);
    printf("  Hello Interval: %d\n", config->hello_interval);
    printf("  Dead Interval: %d\n", config->dead_interval);

    // Apply configuration to the OSPF instance
    if (ospf_config_apply() != 0)
    {
        fprintf(stderr, "Failed to apply OSPF configuration.\n");
        return;
    }

    ospf_route_table_init();
    ospf_area_table_init();
}

/**
 * ospf_main_loop - Main event loop for the OSPF daemon
 *
 * This function runs the OSPF main event loop, polling for events
 * such as incoming OSPF packets and performing periodic tasks like
 * routing table updates and LSA flooding.
 */
void ospf_main_loop()
{
    struct pollfd fds[1];
    fds[0].fd = 0; // Placeholder for the OSPF socket descriptor
    fds[0].events = POLLIN;

    while (keep_running)
    {
        int poll_ret = poll(fds, 1, 1000); // 1-second timeout

        if (poll_ret > 0)
        {
            if (fds[0].revents & POLLIN)
            {
                ospf_lsa_process();       // Process incoming LSAs
                ospf_neighbor_discover(); // Discover and maintain neighbors
            }
        }
        else if (poll_ret == 0)
        {
            ospf_route_update(); // Update routing table periodically
            ospf_flood();        // Flood LSAs
        }
        else
        {
            perror("Poll error");
            break;
        }
    }
}

/**
 * ospf_shutdown - Shuts down the OSPF daemon
 *
 * This function releases resources and performs any necessary cleanup
 * before the OSPF daemon exits.
 */
void ospf_shutdown()
{
    printf("Shutting down OSPF Daemon...\n");
    // TODO: Implement resource cleanup (e.g., freeing memory, closing sockets)
}

/**
 * main - Entry point for the OSPF daemon
 * @argc: Argument count
 * @argv: Argument vector
 *
 * The main function initializes the OSPF daemon, starts the main event loop,
 * and handles shutdown on signal reception.
 */
int main(int argc, char **argv)
{
    const char *config_file = "../../config/ospf_d.conf.sample"; // Default configuration file

    if (argc > 1)
    {
        config_file = argv[1]; // Use specified config file if provided
    }

    printf("OSPF Daemon Starting...\n");

    // Register signal handlers
    signal(SIGINT, handle_signal);
    signal(SIGTERM, handle_signal);

    ospf_init(config_file);
    ospf_main_loop();
    ospf_shutdown();

    return 0;
}
