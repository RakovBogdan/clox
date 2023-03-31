cmake_minimum_required(VERSION 3.10)

project(Clox)

set(SOURCES "src/linked_list/double_linked_list.c" "src/linked_list/test_list.c" "src/main.c" "src/chunk.c" "src/memory.c" "src/debug.c" "src/value.c" "src/vm.c" "src/compiler.c" "src/scanner.c" "src/object.c")
set(HEADER_FILES "include/linked_list/double_linked_list.h" "include/linked_list/test_list.h" "include/chunk.h" "include/memory.h" "include/debug.h" "include/value.h" "include/vm.h" "include/compiler.h" "include/scanner.h" "include/object.h")

add_executable(Clox ${SOURCES} ${HEADER_FILES})
target_include_directories(Clox PRIVATE ${PROJECT_SOURCE_DIR}/include/linked_list ${PROJECT_SOURCE_DIR}/include)
