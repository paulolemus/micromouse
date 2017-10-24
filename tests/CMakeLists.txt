# CMakeLists.txt
# Add this folder as a subdirectory to enable tests.

project (micromouse_tests)

enable_testing ()

macro (macro_micromouse_test TEST_NAME)
    message ("Test: ${TEST_NAME}")
    add_executable (${TEST_NAME} ${TEST_NAME}.c)
    target_link_libraries (${TEST_NAME} ${MICROMOUSE_LIBRARY_NAME})
    target_link_libraries (${TEST_NAME} check)
    set_target_properties (${TEST_NAME} PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
endmacro (macro_micromouse_test)

# All tests below
macro_micromouse_test (check-maze)
macro_micromouse_test (check-maze-parser)
macro_micromouse_test (check-coord)
macro_micromouse_test (check-path)
macro_micromouse_test (check-directions)

