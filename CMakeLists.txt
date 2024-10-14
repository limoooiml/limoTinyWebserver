cmake_minimum_required(VERSION 3.10)
project(LimoTinyWebserver)

set(CXX_STANDARD 14)
set(CXX_STANDARD_REQUIRED true)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

add_subdirectory(src/log)
add_subdirectory(src/buffer)
add_subdirectory(src/http)
add_subdirectory(src/pool)
add_subdirectory(src/timer)
add_subdirectory(src/server)

message(${CMAKE_SOURCE_DIR}/include)
include_directories(${CMAKE_SOURCE_DIR}/include)

# 添加可执行文件
add_executable(${PROJECT_NAME} main.cpp)

# 链接各个库和 pthread, MySQL client 库
target_link_libraries(${PROJECT_NAME} PRIVATE server)
