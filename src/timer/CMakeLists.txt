
add_library(timer STATIC heaptimer.cpp)

target_include_directories(timer PUBLIC ${CMAKE_SOURCE_DIR}/include/timer)
target_link_libraries(timer PUBLIC log)