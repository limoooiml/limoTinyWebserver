

# 查找 MySQL 客户端库
find_library(MYSQL_CLIENT_LIBRARY NAMES mysqlclient PATHS /usr/lib /usr/local/lib REQUIRED)

# 查找 MySQL 头文件路径
find_path(MYSQL_INCLUDE_DIR mysql.h PATHS /usr/include/mysql /usr/local/include/mysql REQUIRED)

# 输出查找结果
message(STATUS "MySQL client library: ${MYSQL_CLIENT_LIBRARY}")
message(STATUS "MySQL include directory: ${MYSQL_INCLUDE_DIR}")

# 添加 MySQL 头文件目录
include_directories(${MYSQL_INCLUDE_DIR})




add_library(http STATIC httpconn.cpp httprequest.cpp httpresponse.cpp)

target_include_directories(http PUBLIC ${CMAKE_SOURCE_DIR}/include/http)
target_link_libraries(http PUBLIC log pool ${MYSQL_CLIENT_LIBRARY})