# List test source files
set(LIB_TESTS
    test_buffer.c
    test_command.c
    test_log.c
    test_memory.c
    test_prefix.c
    test_thread.c
)

# Tests that require libnl and possibly root privileges
set(LIBNL_TESTS
    test_kernel_route.c
    test_network.c
)

# Set the output directory for test executables
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin/tests/lib)

# Handle tests that do not require libnl
foreach(test_source ${LIB_TESTS})
    # Get the test name (without extension)
    get_filename_component(test_name ${test_source} NAME_WE)

    # Create the executable
    add_executable(${test_name} ${test_source})

    # Link libraries
    target_link_libraries(${test_name} PRIVATE
        ospf_lib
        pthread
    )

    # Include header directories
    target_include_directories(${test_name} PRIVATE
        ${PROJECT_SOURCE_DIR}/src
        ${PROJECT_SOURCE_DIR}/src/lib
    )

    # Add the test to CTest
    add_test(NAME ${test_name} COMMAND ${test_name})
endforeach()

# Handle tests that require libnl
foreach(test_source ${LIBNL_TESTS})
    # Get the test name (without extension)
    get_filename_component(test_name ${test_source} NAME_WE)

    # Create the executable
    add_executable(${test_name} ${test_source})

    # Include header directories
    target_include_directories(${test_name} PRIVATE
        ${PROJECT_SOURCE_DIR}/src
        ${PROJECT_SOURCE_DIR}/src/lib
        ${LIBNL_INCLUDE_DIRS}
    )

    # Link libraries
    target_link_libraries(${test_name} PRIVATE
        ospf_lib
        ${LIBNL_LIBRARIES}
        pthread
    )

    # Add the test to CTest, accounting for root privileges
    if (test_name STREQUAL "test_kernel_route" OR test_name STREQUAL "test_network")
        # Use sudo to run tests requiring root privileges
        add_test(NAME ${test_name} COMMAND sudo ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${test_name})
    else()
        add_test(NAME ${test_name} COMMAND ${test_name})
    endif()
endforeach()
