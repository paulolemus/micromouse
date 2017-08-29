/**
 * File: check-maze.c
 *
 * A testfile to check functionality of 
 * maze struct and maze functions.
 */

#include <stdlib.h>
#include <check.h>
#include "core/maze/maze.h"
#include "core/maze/maze.c"

// Test to ensure check works
START_TEST(check_basic) {
    ck_assert_int_eq(1, 1);
}
END_TEST

// Check that all values are defined corectly
START_TEST(check_maze_definitions) {
    ck_assert_int_eq(M_NORTH_WALL, 1);
    ck_assert_int_eq(M_SOUTH_WALL, 2);
    ck_assert_int_eq(M_EAST_WALL, 4);
    ck_assert_int_eq(M_WEST_WALL, 8);
    ck_assert_int_eq(M_NORTH_WALL_IDX, 0);
    ck_assert_int_eq(M_SOUTH_WALL_IDX, 1);
    ck_assert_int_eq(M_EAST_WALL_IDX, 2);
    ck_assert_int_eq(M_WEST_WALL_IDX, 3);
}
END_TEST

// Check that maze default contruction works
START_TEST(check_maze_created) {
    int width = 16;
    int height = 16;
    struct Maze maze1 = newMaze(width, height);

    ck_assert_int_eq(maze1.width, width);
    ck_assert_int_eq(maze1.height, height);
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
    tcase_add_test(tc_core, check_maze_created);

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
