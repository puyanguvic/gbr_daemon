ospf_d/
├── docker/
│   ├── Dockerfile                # Dockerfile for building the ospf_d container image
│   ├── entrypoint.sh             # Entrypoint script for initializing and running ospf_d inside the container
│   └── ospf_d.conf               # Default OSPF configuration file to be copied into the container
├── src/
│   ├── ospf/
│   │   ├── ospf_main.c           # Main logic for initializing and running the OSPF daemon
│   │   ├── ospf_route.c          # Handles route calculations and kernel routing table modifications
│   │   ├── ospf_packet.c         # Responsible for packet formation and processing (LSAs, Hello packets)
│   │   ├── ospf_neighbor.c       # Manages neighbor discovery, state, and related protocol messages
│   │   ├── ospf_interface.c      # Handles OSPF interfaces, including configuration and status tracking
│   │   ├── ospf_flood.c          # Logic for LSA flooding and database synchronization
│   │   ├── ospf_lsa.c            # Creation and parsing of OSPF Link State Advertisements (LSAs)
│   │   ├── ospf_area.c           # Management of OSPF areas and their related LSAs and routes
│   │   ├── ospf_network.c        # Handles OSPF network events and adjacency formations
│   │   ├── ospf_spf.c            # Shortest Path First (SPF) calculations for building the routing table
│   │   ├── ospf_ase.c            # Support for Autonomous System External (ASE) routes
│   │   ├── ospf_snmp.c           # Optional support for SNMP interactions (if necessary)
│   │   ├── ospf_vty.c            # Vty server code for CLI interaction (if included)
│   │   ├── ospf_debug.c          # Debugging functions and log handlers
│   ├── lib/
│   │   ├── thread.c              # Thread management for handling asynchronous tasks
│   │   ├── network.c             # Generic networking utilities for socket operations
│   │   ├── log.c                 # Logging and debug utilities
│   │   ├── memory.c              # Memory management helpers for efficient allocations
│   │   ├── buffer.c              # Buffer management for efficient packet processing
│   │   ├── prefix.c              # Functions for handling IP prefixes and related operations
│   │   ├── command.c             # Command parsing for Vty server (if included)
│   │   └── kernel_route.c        # Utilities for interacting with the kernel routing table (Netlink)
├── include/
│   ├── ospf/
│   │   ├── ospf.h                # Main OSPF daemon definitions
│   │   ├── ospf_route.h          # Routing calculations and kernel interaction functions
│   │   ├── ospf_packet.h         # Packet processing definitions
│   │   ├── ospf_neighbor.h       # Neighbor management definitions
│   │   ├── ospf_interface.h      # OSPF interface handling definitions
│   │   ├── ospf_flood.h          # Flooding mechanisms and LSA synchronization
│   │   ├── ospf_lsa.h            # LSA processing and creation functions
│   │   ├── ospf_area.h           # Area management and related structures
│   │   ├── ospf_network.h        # Network adjacency and event processing
│   │   ├── ospf_spf.h            # SPF calculation definitions
│   │   ├── ospf_ase.h            # ASE route support definitions
│   │   ├── ospf_snmp.h           # SNMP interaction definitions (if needed)
│   │   ├── ospf_vty.h            # Vty server function prototypes (if included)
│   │   ├── ospf_debug.h          # Debugging and logging definitions
│   ├── lib/
│   │   ├── thread.h              # Thread management definitions
│   │   ├── network.h             # Networking utilities definitions
│   │   ├── log.h                 # Logging utility definitions
│   │   ├── memory.h              # Memory management function prototypes
│   │   ├── buffer.h              # Buffer utility function prototypes
│   │   ├── prefix.h              # Prefix utility function prototypes
│   │   ├── command.h             # Command parsing for Vty (if included)
│   │   └── kernel_route.h        # Definitions for kernel routing table interaction
├── config/
│   └── ospf_d.conf.sample        # Sample configuration file for OSPF settings
├── scripts/
│   ├── setup_network.sh          # Script for setting up network for testing
│   └── test_ospf.sh              # Script for running unit tests on the OSPF daemon
├── tests/
│   ├── test_route.c              # Unit tests for OSPF routing
│   ├── test_packet.c             # Unit tests for packet processing
│   ├── test_neighbor.c           # Unit tests for neighbor management
│   └── test_spf.c                # Unit tests for SPF calculations
├── Makefile                      # Build and compilation instructions
├── README.md                     # Documentation and usage instructions
└── LICENSE                       # License for the project
