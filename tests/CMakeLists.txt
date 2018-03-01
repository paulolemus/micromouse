# CMakeLists.txt
# Add this folder as a subdirectory to enable tests.

project (micromouse_tests)

enable_testing ()

macro (macro_micromouse_test TEST_NAME)
    message ("Test: ${TEST_NAME}")
    find_package (Threads)
    add_executable (${TEST_NAME}.out ${TEST_NAME}.c)
    target_link_libraries (${TEST_NAME}.out ${MICROMOUSE_LIBRARY_NAME})
    target_link_libraries (${TEST_NAME}.out check)
    target_link_libraries (${TEST_NAME}.out m)
    target_link_libraries (${TEST_NAME}.out rt)
    target_link_libraries (${TEST_NAME}.out subunit)
    target_link_libraries (${TEST_NAME}.out ${CMAKE_THREAD_LIBS_INIT})
    set_target_properties (${TEST_NAME}.out PROPERTIES
            RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
    add_test (NAME ${TEST_NAME} COMMAND ${TEST_NAME}.out
            WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
endmacro (macro_micromouse_test)

# All tests below
macro_micromouse_test (check-maze)
#macro_micromouse_test (check-maze-parser)
macro_micromouse_test (check-coord)
#macro_micromouse_test (check-path)
#macro_micromouse_test (check-directions)
macro_micromouse_test (check-floodfill)

