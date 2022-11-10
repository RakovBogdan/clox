cmake_minimum_required(VERSION 3.10)

project(Clox)

set(SOURCES "src/linked_list/double_linked_list.c" "src/linked_list/test_list.c" "src/main.c" "src/chunk.c" "src/memory.c" "src/debug.c")

add_executable(Clox ${SOURCES})

target_include_directories(Clox PRIVATE ${PROJECT_SOURCE_DIR}/include/linked_list ${PROJECT_SOURCE_DIR}/include)
