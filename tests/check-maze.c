/**
 * File: check-maze.c
 *
 * A testfile to check functionality of 
 * maze struct and maze functions.
 */

#include <stdlib.h>
#include <check.h>
#include <micromouse/core/maze/maze.h>

// Test to ensure check works
START_TEST(check_basic) {
    ck_assert_int_eq(1, 1);
}
END_TEST

// Check that all values are defined corectly
START_TEST(check_maze_definitions) {
    ck_assert_uint_eq(NORTH_WALL,   1);
    ck_assert_uint_eq(SOUTH_WALL,   2);
    ck_assert_uint_eq(EAST_WALL,    4);
    ck_assert_uint_eq(WEST_WALL,    8);
    ck_assert_uint_eq(VISITED,     16);
    ck_assert_uint_eq(UNCERTAIN,   32);
}
END_TEST

// Check that all bits are zero in array representing maze
START_TEST(check_maze_bits_zeroed) {

    Maze maze;
    clear_maze(&maze);
    set_maze_dimensions(&maze, MAX_WIDTH, MAX_HEIGHT);

    ck_assert_uint_eq(maze.width,  MAX_WIDTH);
    ck_assert_uint_eq(maze.height, MAX_HEIGHT);

    for(unsigned x = 0; x < maze.width; ++x) {
        for(unsigned y = 0; y < maze.height; ++y) {
            ck_assert_uint_eq(has_wall(&maze, x, y, NORTH_WALL), 0);
            ck_assert_uint_eq(has_wall(&maze, x, y, SOUTH_WALL), 0);
            ck_assert_uint_eq(has_wall(&maze, x, y, EAST_WALL),  0);
            ck_assert_uint_eq(has_wall(&maze, x, y, WEST_WALL),  0);

            ck_assert_uint_eq(has_property(&maze, x, y, VISITED),   0);
            ck_assert_uint_eq(has_property(&maze, x, y, UNCERTAIN), 0);
        }
    }
}
END_TEST


START_TEST(check_wall_setters) {

    const unsigned x = 1;
    const unsigned y = 1;

    Maze maze;
    clear_maze(&maze);
    set_maze_dimensions(&maze, MAX_WIDTH, MAX_HEIGHT);

    // Check top wall is zero, set it on, check that it is on for both block.
    ck_assert_uint_eq(has_wall(&maze, x, y,     NORTH_WALL), 0);
    ck_assert_uint_eq(has_wall(&maze, x, y + 1, SOUTH_WALL), 0);
    set_wall_on(&maze, x, y, NORTH_WALL);
    ck_assert_uint_eq(has_wall(&maze, x, y,     NORTH_WALL), 1);
    ck_assert_uint_eq(has_wall(&maze, x, y + 1, SOUTH_WALL), 1);
    clear_maze(&maze);

    ck_assert_uint_eq(has_wall(&maze, x, y,     SOUTH_WALL), 0);
    ck_assert_uint_eq(has_wall(&maze, x, y - 1, NORTH_WALL), 0);
    set_wall_on(&maze, x, y, SOUTH_WALL);
    ck_assert_uint_eq(has_wall(&maze, x, y,     SOUTH_WALL), 1);
    ck_assert_uint_eq(has_wall(&maze, x, y - 1, NORTH_WALL), 1);
    clear_maze(&maze);

    ck_assert_uint_eq(has_wall(&maze, x, y,     EAST_WALL), 0);
    ck_assert_uint_eq(has_wall(&maze, x + 1, y, WEST_WALL), 0);
    set_wall_on(&maze, x, y, EAST_WALL);
    ck_assert_uint_eq(has_wall(&maze, x, y,     EAST_WALL), 1);
    ck_assert_uint_eq(has_wall(&maze, x + 1, y, WEST_WALL), 1);
    clear_maze(&maze);

    ck_assert_uint_eq(has_wall(&maze, x, y,     WEST_WALL), 0);
    ck_assert_uint_eq(has_wall(&maze, x - 1, y, EAST_WALL), 0);
    set_wall_on(&maze, x, y, WEST_WALL);
    ck_assert_uint_eq(has_wall(&maze, x, y,     WEST_WALL), 1);
    ck_assert_uint_eq(has_wall(&maze, x - 1, y, EAST_WALL), 1);
    clear_maze(&maze);
}
END_TEST

START_TEST(check_property_setters) {

    const unsigned x = 1;
    const unsigned y = 1;
    Maze maze;
    clear_maze(&maze);
    set_maze_dimensions(&maze, MAX_WIDTH, MAX_HEIGHT);

    ck_assert_uint_eq(has_property(&maze, x, y, UNCERTAIN), 0);
    set_property_on(&maze, x, y, UNCERTAIN);
    ck_assert_uint_eq(has_property(&maze, x, y, UNCERTAIN), 1);
    set_property_off(&maze, x, y, UNCERTAIN);
    ck_assert_uint_eq(has_property(&maze, x, y, UNCERTAIN), 0);

    ck_assert_uint_eq(has_property(&maze, x, y, VISITED), 0);
    set_property_on(&maze, x, y, VISITED);
    ck_assert_uint_eq(has_property(&maze, x, y, VISITED), 1);
    set_property_off(&maze, x, y, VISITED);
    ck_assert_uint_eq(has_property(&maze, x, y, VISITED), 0);

}
END_TEST

// Check that box_maze works
START_TEST(check_box_maze) {

    const unsigned width  = 16;
    const unsigned height = 16;
    Maze maze;
    clear_maze(&maze);
    set_maze_dimensions(&maze, width, height);
    box_maze(&maze);

    // Check North and South walls
    for(unsigned i = 0; i < width; ++i) {
        ck_assert_uint_eq(has_wall(&maze, i, 0, SOUTH_WALL), 1);
        ck_assert_uint_eq(has_wall(&maze, i, height - 1, NORTH_WALL), 1);
    }

    // Check East and West walls
    for(unsigned j = 0; j < height; ++j) {
        ck_assert_uint_eq(has_wall(&maze, 0, j, WEST_WALL), 1);
        ck_assert_uint_eq(has_wall(&maze, width - 1, j, EAST_WALL), 1);
    }
}
END_TEST

// Check that setBlockBitOn function works and does not affect other bits
START_TEST(check_maze_bit_on) {
    unsigned checkx = 0;
    unsigned checky = 0;
    Maze maze;
    clear_maze(&maze);
    set_maze_dimensions(&maze, MAX_WIDTH, MAX_HEIGHT);

    // Assert all important bits are 0
    ck_assert_uint_eq(has_wall(&maze, checkx, checky, NORTH_WALL), 0);
    ck_assert_uint_eq(has_wall(&maze, checkx, checky, SOUTH_WALL), 0);
    ck_assert_uint_eq(has_wall(&maze, checkx, checky, EAST_WALL),  0);
    ck_assert_uint_eq(has_wall(&maze, checkx, checky, WEST_WALL),  0);
    ck_assert_uint_eq(has_property(&maze, checkx, checky, VISITED),    0);
    ck_assert_uint_eq(has_property(&maze, checkx, checky, UNCERTAIN),  0);

    // Set first bit on
    set_wall_on(&maze, checkx, checky, NORTH_WALL);

    // Assert all bits are 0 except the NORTH_WALL bit
    ck_assert_uint_eq(has_wall(&maze, checkx, checky, NORTH_WALL), 1);
    ck_assert_uint_eq(has_wall(&maze, checkx, checky, SOUTH_WALL), 0);
    ck_assert_uint_eq(has_wall(&maze, checkx, checky, EAST_WALL),  0);
    ck_assert_uint_eq(has_wall(&maze, checkx, checky, WEST_WALL),  0);
    ck_assert_uint_eq(has_property(&maze, checkx, checky, VISITED),    0);
    ck_assert_uint_eq(has_property(&maze, checkx, checky, UNCERTAIN),  0);

    // Set third bit on
    set_wall_on(&maze, checkx, checky, EAST_WALL);

    // Assert all bits are 0 except first and third
    ck_assert_uint_eq(has_wall(&maze, checkx, checky, NORTH_WALL), 1);
    ck_assert_uint_eq(has_wall(&maze, checkx, checky, SOUTH_WALL), 0);
    ck_assert_uint_eq(has_wall(&maze, checkx, checky, EAST_WALL),  1);
    ck_assert_uint_eq(has_wall(&maze, checkx, checky, WEST_WALL),  0);
    ck_assert_uint_eq(has_property(&maze, checkx, checky, VISITED),    0);
    ck_assert_uint_eq(has_property(&maze, checkx, checky, UNCERTAIN),  0);

    // Set sixth bit on
    set_property_on(&maze, checkx, checky, UNCERTAIN);

    // Assert all bits are 0 except first, third, and sixth
    ck_assert_uint_eq(has_wall(&maze, checkx, checky, NORTH_WALL), 1);
    ck_assert_uint_eq(has_wall(&maze, checkx, checky, SOUTH_WALL), 0);
    ck_assert_uint_eq(has_wall(&maze, checkx, checky, EAST_WALL),  1);
    ck_assert_uint_eq(has_wall(&maze, checkx, checky, WEST_WALL),  0);
    ck_assert_uint_eq(has_property(&maze, checkx, checky, VISITED),    0);
    ck_assert_uint_eq(has_property(&maze, checkx, checky, UNCERTAIN),  1);
}
END_TEST

// Check that a bit that is on can be turned off
START_TEST(check_maze_bit_off) {
    unsigned checkx = 0;
    unsigned checky = 0;
    Maze maze;
    clear_maze(&maze);
    set_maze_dimensions(&maze, MAX_WIDTH, MAX_HEIGHT);

    // Assert bit is not set
    ck_assert_uint_eq(has_wall(&maze, checkx, checky, NORTH_WALL), 0);
    // Set the bit
    set_wall_on(&maze, checkx, checky, NORTH_WALL);
    // Assert bit is turned on
    ck_assert_uint_eq(has_wall(&maze, checkx, checky, NORTH_WALL), 1);
    // Turn bit off
    set_wall_off(&maze, checkx, checky, NORTH_WALL);
    // Assert bit is turned off
    ck_assert_uint_eq(has_wall(&maze, checkx, checky, NORTH_WALL), 0);
}
END_TEST


/** 
 * Function to create a test suite and add tests to it.
 */
Suite* maze_suite(void) {
    Suite* s;
    TCase* tc_core;
    s = suite_create("Maze");
    tc_core = tcase_create("Core");

    /*
     * Add tests here
     */
    tcase_add_test(tc_core, check_basic);
    tcase_add_test(tc_core, check_maze_definitions);
    tcase_add_test(tc_core, check_maze_bits_zeroed);
    tcase_add_test(tc_core, check_wall_setters);
    tcase_add_test(tc_core, check_property_setters);
    tcase_add_test(tc_core, check_box_maze);
    tcase_add_test(tc_core, check_maze_bit_on);
    tcase_add_test(tc_core, check_maze_bit_off);

    suite_add_tcase(s, tc_core);
    return s;
}

int main(void) {

    int number_failed;
    Suite* s;
    SRunner* sr;

    s = maze_suite();
    sr = srunner_create(s);
    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);
    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
