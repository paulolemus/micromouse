/**
 * File: check-floodfill.c
 *
 * A testfile to check functionality of 
 * floodfill.
 */

#include <stdlib.h>
#include <check.h>
#include <micromouse/core/pathplanning/floodfill.h>

// Test to ensure check works
START_TEST(check_basic) {
    ck_assert_int_eq(1, 1);
}
END_TEST

// Check that all values are defined corectly
START_TEST(check_maze_definitions) {
    ck_assert_uint_eq(NORTH_WALL, 1);
    ck_assert_uint_eq(SOUTH_WALL, 2);
    ck_assert_uint_eq(EAST_WALL,  4);
    ck_assert_uint_eq(WEST_WALL,  8);
    ck_assert_uint_eq(VISITED,   16);
    ck_assert_uint_eq(UNCERTAIN, 32);
}
END_TEST

// Check floodfil values on empty maze.
START_TEST(check_floodfill_empty_maze) {

    const unsigned width  = 4;
    const unsigned height = 4;
    const unsigned x_goal1 = 3;
    const unsigned y_goal1 = 3;
    const unsigned x_goal2 = 0;
    const unsigned y_goal2 = 0;
    Maze maze;
    Maze ffMap;
    
    ck_assert_uint_eq(set_maze_dimensions(&maze, width, height), 1);
    clear_maze(&maze);
    box_maze(&maze);

    ck_assert_uint_eq(
        floodfill(&maze, &ffMap, x_goal1, y_goal1),
        1
    );
}
END_TEST


/** 
 * Function to create a test suite and add tests to it.
 */
Suite* maze_suite(void) {
    Suite* s;
    TCase* tc_core;
    s = suite_create("Floodfill");
    tc_core = tcase_create("Core");

    /*
     * Add tests here
     */
    tcase_add_test(tc_core, check_basic);
    tcase_add_test(tc_core, check_maze_definitions);
    tcase_add_test(tc_core, check_floodfill_empty_maze);

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
