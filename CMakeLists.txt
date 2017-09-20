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

#################################################
# Folder structure setup
#################################################

# C compiler flags
set (GCC_COMPILER_FLAGS "-Wall -Wextra -Wconversion -Wunreachable-code")
set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${GCC_COMPILER_FLAGS}")

# Output folder where executables are created
set (CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin)
set (EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})



# src/ folder
set (MICROMOUSE_SRC_DIR ${CMAKE_SOURCE_DIR}/src)

# Source files
#set (SOURCE_FILES )

# Consider folder "include" for header includes from -I
include_directories (include)



add_executable (micromouse ${PROJECT_SOURCE_DIR}/src/main.c)
