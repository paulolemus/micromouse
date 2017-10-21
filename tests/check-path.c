/**
 * File: check-path.c
 *
 * Ensure that functions that operate on the Path struct
 * are successful.
 */

#include <stdlib.h>
#include <check.h>
#include <micromouse/core/pathplanning/path.h>

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

START_TEST(check_clear_path) {
    Path path;
    clear_path(&path);
    for(unsigned i = 0; i < PATH_SIZE; ++i) {
        ck_assert_uint_eq(path.coords[i].x, 0);
        ck_assert_uint_eq(path.coords[i].y, 0);
    }
}
END_TEST

START_TEST(check_get_next_coord_succ) {
    Path path;
    clear_path(&path);
    path.coords[0].x = 3;
    path.coords[0].y = 4;

    Coord coord = get_next_coord(&path);
    ck_assert_uint_eq(coord.x, 3);
    ck_assert_uint_eq(coord.y, 4);
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
    tcase_add_test(tc_core, check_clear_path);
    tcase_add_test(tc_core, check_get_next_coord_succ);

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
