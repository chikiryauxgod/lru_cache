cmake_minimum_required(VERSION 3.16)
project(lru_cache_sql LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)
include_directories(/usr/include/cppconn)

option(USE_POSTGRES "Build with PostgreSQL backend" OFF)

set(SOURCES
    src/lru_cache.cpp
    src/main.cpp
)

if (USE_POSTGRES)
    list(APPEND SOURCES src/postgres_db.cpp)
    add_compile_definitions(USE_POSTGRES)
else()
    list(APPEND SOURCES src/mysql_db.cpp)
endif()

add_executable(lru_cache_sql ${SOURCES})

if (NOT USE_POSTGRES)
    target_link_libraries(lru_cache_sql PRIVATE mysqlcppconn)
endif()
