/**
 * File:
 *     check-maze.c
 *
 * Description:
 *     Unit test the maze interface defined in maze.h.
 *
 * Notes:
 *
 *
 * Author:
 *     Paulo Lemus
 */

#include <stdlib.h>
#include <stdbool.h>
#include <check.h>

#include <micromouse/core/maze.h>

// Test to ensure check works
START_TEST(check_basic) {
    ck_assert_int_eq(1, 1);
}
END_TEST

// Check that all values are defined corectly
START_TEST(check_maze_definitions) {
    ck_assert_uint_eq(WALL_NORTH, 1);
    ck_assert_uint_eq(WALL_SOUTH, 2);
    ck_assert_uint_eq(WALL_EAST,  4);
    ck_assert_uint_eq(WALL_WEST,  8);
}
END_TEST

// Check that all bits are zero in array representing maze
START_TEST(check_maze_bits_zeroed) {

    unsigned x, y;
    Maze maze;

    init_maze(&maze, MAX_WIDTH, MAX_HEIGHT);

    ck_assert_uint_eq(maze.width,  MAX_WIDTH);
    ck_assert_uint_eq(maze.height, MAX_HEIGHT);

    for(x = 0; x < maze.width; ++x) {
        for(y = 0; y < maze.height; ++y) {
            ck_assert_uint_eq(has_field(&maze, x, y, WALL_NORTH), false);
            ck_assert_uint_eq(has_field(&maze, x, y, WALL_SOUTH), false);
            ck_assert_uint_eq(has_field(&maze, x, y, WALL_EAST),  false);
            ck_assert_uint_eq(has_field(&maze, x, y, WALL_WEST),  false);
        }
    }
}
END_TEST


START_TEST(check_wall_setters) {

    const unsigned x = 1;
    const unsigned y = 1;

    Maze maze;

    init_maze(&maze, MAX_WIDTH, MAX_HEIGHT);

    // Check top wall is zero, set it on, check that it is on for both block.
    ck_assert_uint_eq(has_field(&maze, x, y,     WALL_NORTH), false);
    ck_assert_uint_eq(has_field(&maze, x, y + 1, WALL_SOUTH), false);
    set_field_on(&maze, x, y, WALL_NORTH);
    ck_assert_uint_eq(has_field(&maze, x, y,     WALL_NORTH), true);
    ck_assert_uint_eq(has_field(&maze, x, y + 1, WALL_SOUTH), true);
    init_maze(&maze, MAX_WIDTH, MAX_HEIGHT);

    ck_assert_uint_eq(has_field(&maze, x, y,     WALL_SOUTH), false);
    ck_assert_uint_eq(has_field(&maze, x, y - 1, WALL_NORTH), false);
    set_field_on(&maze, x, y, WALL_SOUTH);
    ck_assert_uint_eq(has_field(&maze, x, y,     WALL_SOUTH), true);
    ck_assert_uint_eq(has_field(&maze, x, y - 1, WALL_NORTH), true);
    init_maze(&maze, MAX_WIDTH, MAX_HEIGHT);

    ck_assert_uint_eq(has_field(&maze, x, y,     WALL_EAST), false);
    ck_assert_uint_eq(has_field(&maze, x + 1, y, WALL_WEST), false);
    set_field_on(&maze, x, y, WALL_EAST);
    ck_assert_uint_eq(has_field(&maze, x, y,     WALL_EAST), true);
    ck_assert_uint_eq(has_field(&maze, x + 1, y, WALL_WEST), true);
    init_maze(&maze, MAX_WIDTH, MAX_HEIGHT);

    ck_assert_uint_eq(has_field(&maze, x, y,     WALL_WEST), false);
    ck_assert_uint_eq(has_field(&maze, x - 1, y, WALL_EAST), false);
    set_field_on(&maze, x, y, WALL_WEST);
    ck_assert_uint_eq(has_field(&maze, x, y,     WALL_WEST), true);
    ck_assert_uint_eq(has_field(&maze, x - 1, y, WALL_EAST), true);
    init_maze(&maze, MAX_WIDTH, MAX_HEIGHT);
}
END_TEST

// Check that box_maze works
START_TEST(check_box_maze) {

    unsigned i, j;
    const unsigned width  = 16;
    const unsigned height = 16;

    Maze maze;
    init_maze(&maze, width, height);
    box_maze(&maze);

    // Check North and South walls
    for(i = 0; i < width; ++i) {
        ck_assert_uint_eq(has_field(&maze, i, 0, WALL_SOUTH), true);
        ck_assert_uint_eq(has_field(&maze, i, height - 1, WALL_NORTH), true);
    }

    // Check East and West walls
    for(j = 0; j < height; ++j) {
        ck_assert_uint_eq(has_field(&maze, 0, j, WALL_WEST), true);
        ck_assert_uint_eq(has_field(&maze, width - 1, j, WALL_EAST), true);
    }
}
END_TEST

// Check that set_field_on function works and does not affect other bits
START_TEST(check_maze_bit_on) {

    unsigned checkx = 0;
    unsigned checky = 0;
    Maze maze;
    init_maze(&maze, MAX_WIDTH, MAX_HEIGHT);

    // Assert all important bits are 0
    ck_assert_uint_eq(has_field(&maze, checkx, checky, WALL_NORTH), false);
    ck_assert_uint_eq(has_field(&maze, checkx, checky, WALL_SOUTH), false);
    ck_assert_uint_eq(has_field(&maze, checkx, checky, WALL_EAST),  false);
    ck_assert_uint_eq(has_field(&maze, checkx, checky, WALL_WEST),  false);

    // Set first bit on
    set_field_on(&maze, checkx, checky, WALL_NORTH);

    // Assert all bits are 0 except the WALL_NORTH bit
    ck_assert_uint_eq(has_field(&maze, checkx, checky, WALL_NORTH), true);
    ck_assert_uint_eq(has_field(&maze, checkx, checky, WALL_SOUTH), false);
    ck_assert_uint_eq(has_field(&maze, checkx, checky, WALL_EAST),  false);
    ck_assert_uint_eq(has_field(&maze, checkx, checky, WALL_WEST),  false);

    // Set third bit on
    set_field_on(&maze, checkx, checky, WALL_EAST);

    // Assert all bits are 0 except first and third
    ck_assert_uint_eq(has_field(&maze, checkx, checky, WALL_NORTH), true);
    ck_assert_uint_eq(has_field(&maze, checkx, checky, WALL_SOUTH), false);
    ck_assert_uint_eq(has_field(&maze, checkx, checky, WALL_EAST),  true);
    ck_assert_uint_eq(has_field(&maze, checkx, checky, WALL_WEST),  false);

    // Set fourth bit on
    set_field_on(&maze, checkx, checky, WALL_WEST);

    // Assert all bits are 0 except first, third, and sixth
    ck_assert_uint_eq(has_field(&maze, checkx, checky, WALL_NORTH), true);
    ck_assert_uint_eq(has_field(&maze, checkx, checky, WALL_SOUTH), false);
    ck_assert_uint_eq(has_field(&maze, checkx, checky, WALL_EAST),  true);
    ck_assert_uint_eq(has_field(&maze, checkx, checky, WALL_WEST),  true);
}
END_TEST

// Check that a bit that is on can be turned off
START_TEST(check_maze_bit_off) {

    unsigned checkx = 0;
    unsigned checky = 0;
    Maze maze;
    init_maze(&maze, MAX_WIDTH, MAX_HEIGHT);

    // Assert bit is not set
    ck_assert_uint_eq(has_field(&maze, checkx, checky, WALL_NORTH), false);
    // Set the bit
    set_field_on(&maze, checkx, checky, WALL_NORTH);
    // Assert bit is turned on
    ck_assert_uint_eq(has_field(&maze, checkx, checky, WALL_NORTH), true);
    // Turn bit off
    set_field_off(&maze, checkx, checky, WALL_NORTH);
    // Assert bit is turned off
    ck_assert_uint_eq(has_field(&maze, checkx, checky, WALL_NORTH), false);
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
