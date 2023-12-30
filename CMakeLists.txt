CMAKE_MINIMUM_REQUIRED (VERSION 3.27.7)
project(notes)

file (GLOB db)

find_package(PostgreSQL REQUIRED)

add_executable(${PROJECT_NAME} notes.cpp)

target_link_libraries(${PROJECT_NAME} PRIVATE PostgreSQL::PostgreSQL)