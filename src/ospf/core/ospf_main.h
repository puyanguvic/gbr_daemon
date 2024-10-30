/*
 * OSPF Daemon - Main Header
 *
 * (c) 2024 Pu Yang <email@example.com>
 *
 * This program is distributed under the terms of the GNU General Public License.
 */

/**
 * DOC: OSPF Daemon Main Header
 *
 * This header defines the primary entry points for the OSPF daemon,
 * including functions for initialization, the main event loop, and shutdown.
 * It also integrates various OSPF modules for routing, neighbor management,
 * and link-state advertisement processing.
 */

#ifndef OSPF_MAIN_H
#define OSPF_MAIN_H

// Include configuration and subsystem modules
#include "../ospf/core/ospf_config.h"
#include "../ospf/routing/ospf_route.h"
#include "../ospf/neighbor/ospf_neighbor.h"
#include "../ospf/packet/ospf_lsa.h"
#include "../ospf/area/ospf_area.h"
#include "../ospf/flood/ospf_flood.h"
#include "../ospf/routing/ospf_spf.h"

// Global configuration structure
extern ospf_config_t ospf_config;

/* Function Prototypes */

/**
 * ospf_init - Initializes the OSPF daemon with a specified configuration file.
 * @config_file: Path to the configuration file containing OSPF settings.
 *
 * Loads configuration settings, initializes key OSPF data structures, and
 * prepares the daemon for protocol operation.
 */
void ospf_init(const char *config_file);

/**
 * ospf_main_loop - Main event loop for the OSPF daemon.
 *
 * Continuously polls for incoming OSPF events and performs periodic tasks,
 * such as sending hello packets, updating routing tables, and flooding LSAs.
 * The loop continues until a termination signal is received.
 */
void ospf_main_loop();

/**
 * ospf_shutdown - Shuts down the OSPF daemon and cleans up resources.
 *
 * Releases dynamically allocated memory, closes open sockets, and performs
 * any other necessary cleanup tasks before the daemon exits.
 */
void ospf_shutdown();

#endif // OSPF_MAIN_H
