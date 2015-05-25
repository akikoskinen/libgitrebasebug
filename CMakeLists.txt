cmake_minimum_required(VERSION 2.8)
project(libgitrebasebug)

# Change to correct directory
set(LIBGIT2_DIR "${CMAKE_CURRENT_LIST_DIR}/libgit2")

add_subdirectory("${LIBGIT2_DIR}" "${CMAKE_CURRENT_BINARY_DIR}/libgit2")
include_directories("${LIBGIT2_DIR}/include")

add_definitions("-DTESTDIR=\"${CMAKE_CURRENT_LIST_DIR}/testrepo\"")

set(SRC_LIST main.c)
add_executable(${PROJECT_NAME} ${SRC_LIST})
target_link_libraries(${PROJECT_NAME} git2)
