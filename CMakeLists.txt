cmake_minimum_required (VERSION 3.0)
project (micromouse)

#################################################
#                   Notes
# This CMakeLists.txt file is setup to generate for
# an operating system OR for a Microchip PIC MCU.
#
#               Generate for OS
# cmake -DPIC_TARGET:BOOL=OFF <path to CMakeLists.txt>
#
#             Generate for PIC MCU
# cmake -DPIC_TARGET:BOOL=ON <path to cmakelists.txt>
#
#         Testing with verbose errors
# env CTEST_OUTPUT_ON_FAILURE=1 make test
#                   OR
# ctest --verbose
#
# Keep in mind that the PIC_TARGET flag only needs to
# be set when you switch between modes the first time.
#################################################


### General make variables
option (PIC_TARGET "Target PIC MCUs" OFF)
# Alert user if generating for PIC MCU or desktop
if (PIC_TARGET)
    message ("MICROMOUSE: Generating for PIC MCU")
else (PIC_TARGET)
    message ("MICROMOUSE: Generating for desktop compiler")
endif (PIC_TARGET)


# Compiler flags
set (GCC_COMPILER_FLAGS "-Wall -Wextra -Wconversion -Wunreachable-code -pedantic")
set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${GCC_COMPILER_FLAGS}")
# Output folder where executables are created
set (CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin)
set (EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
# Where to look for includes
include_directories (include)

# YCM Database generation
set (CMAKE_EXPORT_COMPILE_COMMANDS 1)


# Micromouse
set (MICROMOUSE_MAJOR_VERSION 0)
set (MICROMOUSE_MINOR_VERSION 1)
set (MICROMOUSE_LIBRARY_NAME
        "micromouse-core-${MICROMOUSE_MAJOR_VERSION}.${MICROMOUSE_MINOR_VERSION}")
set (MICROMOUSE_SIM_LIBRARY_NAME
        "micromouse-sim-${MICROMOUSE_MAJOR_VERSION}.${MICROMOUSE_MINOR_VERSION}")


# Core library
# Add all source files to this variable
set (SOURCE_FILES
    src/core/maze.c
    src/core/floodfill.c
    src/core/path.c
    src/core/pid.c)
add_library (${MICROMOUSE_LIBRARY_NAME} STATIC ${SOURCE_FILES})

# Simulation libraries
if (NOT PIC_TARGET)
    find_package (Curses REQUIRED)
    include_directories (${CURSES_INCLUDE_DIR})
endif (NOT PIC_TARGET)

# EXECUTABLES
if (PIC_TARGET)
    # PIC main target
    add_executable (micromouse_pic src/drivers/pic_main.c)
else (PIC_TARGET)
    # Micromouse simulation target
    add_executable (micromouse_sim src/drivers/sim_main.c)
    target_link_libraries (micromouse_sim
                            ${CURSES_LIBRARIES}
                            ${MICROMOUSE_LIBRARY_NAME})
endif (PIC_TARGET)


# TESTS
if (NOT PIC_TARGET)
    enable_testing ()
    add_subdirectory (tests)
endif (NOT PIC_TARGET)

