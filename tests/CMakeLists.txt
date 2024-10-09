# 启用测试
enable_testing()

# 包含头文件目录
include_directories(
    ${PROJECT_SOURCE_DIR}/src
    ${PROJECT_SOURCE_DIR}/src/lib
    ${PROJECT_SOURCE_DIR}/src/ospf
)

# 添加子目录
add_subdirectory(unit)
