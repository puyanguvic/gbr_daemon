# 包含目录
include_directories(
    ${PROJECT_SOURCE_DIR}/src
    ${PROJECT_SOURCE_DIR}/src/lib
    ${PROJECT_SOURCE_DIR}/src/ospf
    ${CMAKE_CURRENT_SOURCE_DIR}
)

# 查找必要的库
find_package(PkgConfig REQUIRED)
pkg_check_modules(LIBNL REQUIRED libnl-3.0 libnl-route-3.0)

# 收集所有子目录的测试源文件
file(GLOB_RECURSE OSPF_TEST_SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/core/*.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/routing/*.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/packet/*.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/neighbor/*.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/area/*.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/flood/*.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/utils/*.c"
)

# 设置测试可执行文件的输出目录
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin/tests/ospf)

# 为每个测试源文件创建可执行文件并添加测试
foreach(test_source ${OSPF_TEST_SOURCES})
    # 获取测试名（文件名，不含路径和扩展名）
    get_filename_component(test_name ${test_source} NAME_WE)

    # 创建可执行文件
    add_executable(${test_name} ${test_source})

    # 链接库
    target_link_libraries(${test_name} PRIVATE
        ospf_lib
        ospf_daemon
        ${LIBNL_LIBRARIES}
        pthread
    )

    # 包含头文件目录
    target_include_directories(${test_name} PRIVATE
        ${PROJECT_SOURCE_DIR}/src
        ${PROJECT_SOURCE_DIR}/src/lib
        ${PROJECT_SOURCE_DIR}/src/ospf
        ${CMAKE_CURRENT_SOURCE_DIR}
    )

    # 添加测试到 CTest
    add_test(NAME ${test_name} COMMAND ${test_name})
endforeach()
