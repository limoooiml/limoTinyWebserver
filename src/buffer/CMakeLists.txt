add_library(buffer STATIC buffer.cpp)

target_include_directories(buffer PUBLIC ${CMAKE_SOURCE_DIR}/include/buffer)