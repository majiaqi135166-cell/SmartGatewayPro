cmake_minimum_required(VERSION 3.10)
project(SmartGatewayPro)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 1. 告诉编译器头文件在 include 目录
include_directories(include)

# 2. 寻找线程库
find_package(Threads REQUIRED)

# 3. 核心修复：自动搜寻 src 目录下所有的 .cpp 文件
# GLOB_RECURSE 会递归寻找 src 下的所有 cpp，并存入 SOURCES 变量
file(GLOB_RECURSE SOURCES "src/*.cpp")

# 4. 打印一下找到的文件（调试用，可以看到到底找没找到）
message(STATUS "Found sources: ${SOURCES}")

# 5. 生成可执行文件
add_executable(gateway ${SOURCES})

# 6. 链接线程库
target_link_libraries(gateway PRIVATE Threads::Threads)
