/**
 * File:
 *     check-coord.c
 *
 * Description:
 *     Unit tests for the coordinate struct defined in maze.h.
 *
 * Notes:
 *     Coord acts as an alternate way to consider specific cells in the maze.
 *     Coords are helpful for keeping a list that describes paths.
 *
 * Author:
 *     Paulo Lemus
 */

#include <stdlib.h>
#include <check.h>

#include "micromouse/core/maze.h"

// Test to ensure check works
START_TEST(check_basic) {
    ck_assert_int_eq(1, 1);
}
END_TEST

START_TEST(check_create_coord) {
    Coord coord;
    ck_assert_int_eq(sizeof(Coord), sizeof(coord));
}
END_TEST

START_TEST(check_coord_values) {
    Coord coord;
    coord.x = 4;
    coord.y = 5;
    ck_assert_uint_eq(coord.x, 4);
    ck_assert_uint_eq(coord.y, 5);
}
END_TEST

START_TEST(check_set_coord_ptr) {
    Coord coord;
    Coord* coordptr = &coord;
    const unsigned x = 10;
    const unsigned y = 15;
    coordptr->x = x;
    coordptr->y = y;
    ck_assert_uint_eq(coord.x, x);
    ck_assert_uint_eq(coord.y, y);
}
END_TEST

/** 
 * Function to create a test suite and add tests to it.
 */
Suite* maze_suite(void) {
    Suite* s;
    TCase* tc_core;
    s = suite_create("Coord");
    tc_core = tcase_create("Core");

    /*
     * Add tests here
     */
    tcase_add_test(tc_core, check_basic);
    tcase_add_test(tc_core, check_create_coord);
    tcase_add_test(tc_core, check_coord_values);
    tcase_add_test(tc_core, check_set_coord_ptr);

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
