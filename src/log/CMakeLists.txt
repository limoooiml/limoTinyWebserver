add_library(log STATIC log.cpp)

target_include_directories(log PUBLIC ${CMAKE_SOURCE_DIR}/include/log)
target_link_libraries(log PUBLIC buffer)