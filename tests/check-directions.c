/**
 * File: check-path.c
 *
 * Ensure that functions that operate on the Path struct
 * are successful.
 */

#include <stdlib.h>
#include <check.h>
#include <micromouse/core/pathplanning/directions.h>

// Test to ensure check works
START_TEST(check_basic) {
    ck_assert_int_eq(1, 1);
}
END_TEST

START_TEST(check_definitions) {
    ck_assert_int_eq(NORTH, 0);
    ck_assert_int_eq(EAST,  1);
    ck_assert_int_eq(SOUTH, 2);
    ck_assert_int_eq(WEST,  3);
    ck_assert_int_eq(DIRECT_COUNT,  4);
    ck_assert_uint_gt(DIRECTIONS_SIZE, 0);
}
END_TEST


START_TEST(check_relative_to_direct) {

    Direct direct = NORTH;
    ck_assert_int_eq(relative_to_direct(direct, FORWARD), NORTH);
    ck_assert_int_eq(relative_to_direct(direct, LEFT),    WEST);
    ck_assert_int_eq(relative_to_direct(direct, BACK),    SOUTH);
    ck_assert_int_eq(relative_to_direct(direct, RIGHT),   EAST);

    direct = EAST;
    ck_assert_int_eq(relative_to_direct(direct, FORWARD), EAST);
    ck_assert_int_eq(relative_to_direct(direct, LEFT),    NORTH);
    ck_assert_int_eq(relative_to_direct(direct, BACK),    WEST);
    ck_assert_int_eq(relative_to_direct(direct, RIGHT),   SOUTH);

    direct = SOUTH;
    ck_assert_int_eq(relative_to_direct(direct, FORWARD), SOUTH);
    ck_assert_int_eq(relative_to_direct(direct, LEFT),    EAST);
    ck_assert_int_eq(relative_to_direct(direct, BACK),    NORTH);
    ck_assert_int_eq(relative_to_direct(direct, RIGHT),   WEST);

    direct = WEST;
    ck_assert_int_eq(relative_to_direct(direct, FORWARD), WEST);
    ck_assert_int_eq(relative_to_direct(direct, LEFT),    SOUTH);
    ck_assert_int_eq(relative_to_direct(direct, BACK),    EAST);
    ck_assert_int_eq(relative_to_direct(direct, RIGHT),   NORTH);
}
END_TEST


START_TEST(check_clear_directions) {

    Directions directions;
    clear_directions(&directions);
    ck_assert_uint_eq(directions.curr, 0);
    ck_assert_uint_eq(directions.end,  0);

    for(unsigned i = 0; i < DIRECTIONS_SIZE; ++i) {
        ck_assert_int_eq(directions.directions[i], DIRECT_COUNT);
    }
}
END_TEST

START_TEST(check_get_direction) {
    Directions directions;
    clear_directions(&directions);

    directions.end = 3;
    directions.directions[0] = NORTH;
    directions.directions[1] = SOUTH;
    directions.directions[2] = EAST;
    directions.directions[3] = WEST;

    ck_assert_int_eq(get_direction(&directions), NORTH);
    directions.curr++;
    ck_assert_int_eq(get_direction(&directions), SOUTH);
    directions.curr++;
    ck_assert_int_eq(get_direction(&directions), EAST);
    directions.curr++;
    ck_assert_int_eq(get_direction(&directions), WEST);
}
END_TEST

START_TEST(check_shift_directions_up) {

    Directions directions;
    clear_directions(&directions);

    ck_assert_uint_eq(shift_directions_up(&directions), 0);

    directions.end = 1;
    ck_assert_uint_eq(shift_directions_up(&directions), 1);
    ck_assert_uint_eq(directions.curr, 1);
        
}
END_TEST



/** 
 * Function to create a test suite and add tests to it.
 */
Suite* maze_suite(void) {
    Suite* s;
    TCase* tc_core;
    s = suite_create("Directions");
    tc_core = tcase_create("Core");

    /*
     * Add tests here
     */
    tcase_add_test(tc_core, check_basic);
    tcase_add_test(tc_core, check_definitions);
    tcase_add_test(tc_core, check_relative_to_direct);
    tcase_add_test(tc_core, check_clear_directions);
    tcase_add_test(tc_core, check_get_direction);
    tcase_add_test(tc_core, check_shift_directions_up);

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
