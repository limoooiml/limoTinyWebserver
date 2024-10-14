add_library(server STATIC epoller.cpp webserver.cpp)





# 添加可执行文件
# add_executable(${PROJECT_NAME} main.cpp)

# 链接各个库和 pthread, MySQL client 库
# target_link_libraries(${PROJECT_NAME} PRIVATE Threads::Threads ${MYSQL_CLIENT_LIBRARY} server)

target_include_directories(server PUBLIC ${CMAKE_SOURCE_DIR}/include/server)
target_link_libraries(server PUBLIC http timer)