cmake_minimum_required(VERSION 3.10)
project(ospf_d C)

# 设置 C 标准
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED True)

# 设置默认编译类型为 Release，如果未指定
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

# 添加子目录
add_subdirectory(src)
add_subdirectory(tests)

# 设置安装前缀
set(CMAKE_INSTALL_PREFIX "/usr/local")
