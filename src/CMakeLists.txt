# 包含目录
include_directories(
    ${PROJECT_SOURCE_DIR}/src
    ${PROJECT_SOURCE_DIR}/src/lib
    ${PROJECT_SOURCE_DIR}/src/ospf
)

# 查找必要的库
find_package(PkgConfig REQUIRED)
pkg_check_modules(LIBNL REQUIRED libnl-3.0 libnl-route-3.0)

# 添加子目录
add_subdirectory(lib)
add_subdirectory(ospf)

# 设置可执行文件的输出目录
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)

# 编译主程序
add_executable(ospf_d main.c)

# 链接库
target_link_libraries(ospf_d PRIVATE
    ospf_lib
    ospf_daemon
    ${LIBNL_LIBRARIES}
    pthread
)

# 包含头文件目录
target_include_directories(ospf_d PRIVATE
    ${LIBNL_INCLUDE_DIRS}
)

# 安装可执行文件
install(TARGETS ospf_d RUNTIME DESTINATION bin)
