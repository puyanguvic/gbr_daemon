# 包含目录
include_directories(
    ${PROJECT_SOURCE_DIR}/src
    ${PROJECT_SOURCE_DIR}/src/lib
)

# 查找必要的库
find_package(PkgConfig REQUIRED)
pkg_check_modules(LIBNL REQUIRED libnl-3.0 libnl-route-3.0)

# 收集所有子目录的源文件
file(GLOB_RECURSE OSPF_SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/core/*.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/routing/*.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/packet/*.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/neighbor/*.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/area/*.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/flood/*.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/utils/*.c"
)

# 检查是否找到源文件
if(NOT OSPF_SOURCES)
    message(FATAL_ERROR "No source files found for OSPF daemon.")
endif()

# 创建静态库
add_library(ospf_daemon STATIC ${OSPF_SOURCES})

# 包含头文件目录
target_include_directories(ospf_daemon PUBLIC
    ${PROJECT_SOURCE_DIR}/src
    ${PROJECT_SOURCE_DIR}/src/ospf
)

# 链接库
target_link_libraries(ospf_daemon PUBLIC
    ospf_lib
    ${LIBNL_LIBRARIES}
)

# 安装库文件
install(TARGETS ospf_daemon ARCHIVE DESTINATION lib)

# 安装头文件
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/
    DESTINATION include/ospf_d/ospf
    FILES_MATCHING PATTERN "*.h"
)
