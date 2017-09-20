cmake_minimum_required (VERSION 3.0)
project (micromouse)

set (CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin)
set (EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})

include_directories ("${PROJECT_SOURCE_DIR}")

add_executable (micromouse ${PROJECT_SOURCE_DIR}/testing.c)
