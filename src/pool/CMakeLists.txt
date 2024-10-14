
find_package(Threads REQUIRED)

add_library(pool STATIC sqlconnpool.cpp)

target_include_directories(pool PUBLIC ${CMAKE_SOURCE_DIR}/include/pool)
target_link_libraries(pool PUBLIC log Threads::Threads )