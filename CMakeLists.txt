cmake_minimum_required (VERSION 3.0)
project (micromouse)

#################################################
# Folder structure setup
#################################################


# Output folder where executables are created
set (CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin)
set (EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})

# C compiler flags
set (GCC_COMPILER_FLAGS "-Wall -Wextra -Wconversion -Wunreachable-code")
set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${GCC_COMPILER_FLAGS}")

# Consider folder "include" for header includes from -I
include_directories (include)

# Instead of adding each file independently, I can just use glob
# to save a list of all matching files
# file (GLOB SOURCES "src/*.c")

add_executable (micromouse ${PROJECT_SOURCE_DIR}/src/main.c)
