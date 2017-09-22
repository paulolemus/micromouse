cmake_minimum_required (VERSION 3.0)
project (micromouse)

#################################################
#                   Notes
# CMAKE_SOURCE_FOLDER:
#   The folder containing this CMakeLists.txt file.
#   In this case, it is "micromouse"
#
#               Using cmake
# use cmake -Bbuild H.
# -B flag specifies build dir, -H specifies source dir
# Alternatively, cd into build/ folder and type cmake ../
#
# Once everything is built, I can type:
# cmake --build .
# To call the generated build system to execute the makefiles.
#
#
#################################################


# Micromouse
set (MICROMOUSE_MAJOR_VERSION 0)
set (MICROMOUSE_MINOR_VERSION 1)
set (MICROMOUSE_LIBRARY_NAME
        "micromouse-core-${MICROMOUSE_MAJOR_VERSION}.${MICROMOUSE_MINOR_VERSION}")
include_directories (include)


# C compiler flags
set (GCC_COMPILER_FLAGS "-Wall -Wextra -Wconversion -Wunreachable-code -pedantic")
set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${GCC_COMPILER_FLAGS}")

# Output folder where executables are created
set (CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin)
set (EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})


# Core library
# Add all source files to this variable
set (SOURCE_FILES
    src/core/maze/maze.c
    src/core/maze/parser.c
    src/core/pathplanning/floodfill.c)
add_library (${MICROMOUSE_LIBRARY_NAME} SHARED ${SOURCE_FILES})


# EXECUTABLES
add_executable (micromouse ${SOURCE_FILES} src/main.c)
target_link_libraries (micromouse ${MICROMOUSE_LIBRARY_NAME})


# TESTS
enable_testing ()
add_subdirectory (tests)

