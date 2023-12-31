CMAKE_MINIMUM_REQUIRED (VERSION 3.27.7)
project (notes)

set (CMAKE_CXX_STANDARD 20)

file (GLOB db)

find_package(PostgreSQL REQUIRED)

add_executable(${PROJECT_NAME} notes.cpp notes.h)

target_link_libraries(${PROJECT_NAME} PRIVATE PostgreSQL::PostgreSQL)