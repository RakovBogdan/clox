cmake_minimum_required(VERSION 3.10)

project(Clox)

set(SOURCES src/double_linked_list.c src/test_list.c)

add_executable(Clox ${SOURCES})

target_include_directories(Clox PRIVATE ${PROJECT_SOURCE_DIR}/include)
