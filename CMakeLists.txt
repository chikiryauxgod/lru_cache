cmake_minimum_required(VERSION 3.16)
project(lru_cache_mysql LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)
include_directories(/usr/include/cppconn)

add_executable(lru_cache_mysql
    src/lru_cache.cpp
    src/database.cpp
    src/main.cpp
)

target_link_libraries(lru_cache_mysql PRIVATE mysqlcppconn)
