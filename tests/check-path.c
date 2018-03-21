/**
 * File:
 *     check-path.c
 *
 * Description:
 *     Unit tests for the Path struct defined in path.h
 *
 * Notes:
 *     Path acts as a way to describe a path in the maze struct.
 *
 * Author:
 *     Paulo Lemus
 */

#include <stdlib.h>
#include <check.h>

#include "micromouse/core/path.h"

// Test to ensure check works
START_TEST(check_basic) {
    ck_assert_int_eq(1, 1);
}
END_TEST

START_TEST(check_create_path) {
    Path path;
    ck_assert_int_eq(sizeof(Path), sizeof(path));
}
END_TEST


/** 
 * Function to create a test suite and add tests to it.
 */
Suite* maze_suite(void) {
    Suite* s;
    TCase* tc_core;
    s = suite_create("Path");
    tc_core = tcase_create("Core");

    /*
     * Add tests here
     */
    tcase_add_test(tc_core, check_basic);
    tcase_add_test(tc_core, check_create_path);

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
