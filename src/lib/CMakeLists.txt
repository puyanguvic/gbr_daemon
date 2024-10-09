# Collect source files
set(LIB_SOURCES
    buffer.c
    command.c
    kernel_route.c
    log.c
    memory.c
    network.c
    prefix.c
    thread.c
)

# Create the static library
add_library(ospf_lib STATIC ${LIB_SOURCES})

# Include header directories (your own headers)
target_include_directories(ospf_lib PUBLIC
    ${PROJECT_SOURCE_DIR}/src/lib
)

# Find the libnl packages
find_package(PkgConfig REQUIRED)
pkg_check_modules(LIBNL REQUIRED libnl-3.0 libnl-route-3.0)

# Include libnl directories
target_include_directories(ospf_lib PRIVATE ${LIBNL_INCLUDE_DIRS})

# Link libnl libraries
target_link_libraries(ospf_lib PRIVATE ${LIBNL_LIBRARIES})

# Install library files
install(TARGETS ospf_lib ARCHIVE DESTINATION lib)

# Install header files
install(FILES
    buffer.h
    command.h
    kernel_route.h
    log.h
    memory.h
    network.h
    prefix.h
    thread.h
    DESTINATION include/ospf_d/lib
)
