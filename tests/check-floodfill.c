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
    FloodObj floodObj;
    Coord goal1;
    Coord goal2;
    goal1.x = x_goal1;
    goal1.y = y_goal1;
    goal2.x = x_goal2;
    goal2.y = y_goal2;
    
    ck_assert_uint_eq(set_maze_dimensions(&maze, width, height), 1);
    clear_maze(&maze);
    box_maze(&maze);

    ck_assert_uint_eq(
        floodfill(&floodObj, &maze, &goal1),
        1
    );

    ck_assert_uint_eq(floodObj.map[0][0], 6);
    ck_assert_uint_eq(floodObj.map[0][1], 5);
    ck_assert_uint_eq(floodObj.map[0][2], 4);
    ck_assert_uint_eq(floodObj.map[0][3], 3);
    ck_assert_uint_eq(floodObj.map[1][0], 5);
    ck_assert_uint_eq(floodObj.map[1][1], 4);
    ck_assert_uint_eq(floodObj.map[1][2], 3);
    ck_assert_uint_eq(floodObj.map[1][3], 2);
    ck_assert_uint_eq(floodObj.map[2][0], 4);
    ck_assert_uint_eq(floodObj.map[2][1], 3);
    ck_assert_uint_eq(floodObj.map[2][2], 2);
    ck_assert_uint_eq(floodObj.map[2][3], 1);
    ck_assert_uint_eq(floodObj.map[3][0], 3);
    ck_assert_uint_eq(floodObj.map[3][1], 2);
    ck_assert_uint_eq(floodObj.map[3][2], 1);
    ck_assert_uint_eq(floodObj.map[3][3], 0);


    ck_assert_uint_eq(
        floodfill(&floodObj, &maze, &goal2),
        1
    );
    ck_assert_uint_eq(floodObj.map[0][0], 0);
    ck_assert_uint_eq(floodObj.map[0][1], 1);
    ck_assert_uint_eq(floodObj.map[0][2], 2);
    ck_assert_uint_eq(floodObj.map[0][3], 3);
    ck_assert_uint_eq(floodObj.map[1][0], 1);
    ck_assert_uint_eq(floodObj.map[1][1], 2);
    ck_assert_uint_eq(floodObj.map[1][2], 3);
    ck_assert_uint_eq(floodObj.map[1][3], 4);
    ck_assert_uint_eq(floodObj.map[2][0], 2);
    ck_assert_uint_eq(floodObj.map[2][1], 3);
    ck_assert_uint_eq(floodObj.map[2][2], 4);
    ck_assert_uint_eq(floodObj.map[2][3], 5);
    ck_assert_uint_eq(floodObj.map[3][0], 3);
    ck_assert_uint_eq(floodObj.map[3][1], 4);
    ck_assert_uint_eq(floodObj.map[3][2], 5);
    ck_assert_uint_eq(floodObj.map[3][3], 6);

}
END_TEST

// Check floodfil values on empty maze.
START_TEST(check_floodfill_nonblocking_walls) {

    const unsigned width  = 4;
    const unsigned height = 4;
    const unsigned x_goal1 = 3;
    const unsigned y_goal1 = 3;
    const unsigned x_goal2 = 0;
    const unsigned y_goal2 = 0;
    Maze maze;
    FloodObj floodObj;
    Coord goal1;
    Coord goal2;

    goal1.x = x_goal1;
    goal1.y = y_goal1;
    goal2.x = x_goal2;
    goal2.y = y_goal2;
    
    ck_assert_uint_eq(set_maze_dimensions(&maze, width, height), 1);
    clear_maze(&maze);
    box_maze(&maze);

    // Add single wall in middle of maze that 
    // shouldn't affect floodfill outcome.
    set_wall_on(&maze, 1, 1, SOUTH_WALL);

    ck_assert_uint_eq(
        floodfill(&floodObj, &maze, &goal1),
        1
    );
    ck_assert_uint_eq(floodObj.map[0][0], 6);
    ck_assert_uint_eq(floodObj.map[0][1], 5);
    ck_assert_uint_eq(floodObj.map[0][2], 4);
    ck_assert_uint_eq(floodObj.map[0][3], 3);
    ck_assert_uint_eq(floodObj.map[1][0], 5);
    ck_assert_uint_eq(floodObj.map[1][1], 4);
    ck_assert_uint_eq(floodObj.map[1][2], 3);
    ck_assert_uint_eq(floodObj.map[1][3], 2);
    ck_assert_uint_eq(floodObj.map[2][0], 4);
    ck_assert_uint_eq(floodObj.map[2][1], 3);
    ck_assert_uint_eq(floodObj.map[2][2], 2);
    ck_assert_uint_eq(floodObj.map[2][3], 1);
    ck_assert_uint_eq(floodObj.map[3][0], 3);
    ck_assert_uint_eq(floodObj.map[3][1], 2);
    ck_assert_uint_eq(floodObj.map[3][2], 1);
    ck_assert_uint_eq(floodObj.map[3][3], 0);

    ck_assert_uint_eq(
        floodfill(&floodObj, &maze, &goal2),
        1
    );
    ck_assert_uint_eq(floodObj.map[0][0], 0);
    ck_assert_uint_eq(floodObj.map[0][1], 1);
    ck_assert_uint_eq(floodObj.map[0][2], 2);
    ck_assert_uint_eq(floodObj.map[0][3], 3);
    ck_assert_uint_eq(floodObj.map[1][0], 1);
    ck_assert_uint_eq(floodObj.map[1][1], 2);
    ck_assert_uint_eq(floodObj.map[1][2], 3);
    ck_assert_uint_eq(floodObj.map[1][3], 4);
    ck_assert_uint_eq(floodObj.map[2][0], 2);
    ck_assert_uint_eq(floodObj.map[2][1], 3);
    ck_assert_uint_eq(floodObj.map[2][2], 4);
    ck_assert_uint_eq(floodObj.map[2][3], 5);
    ck_assert_uint_eq(floodObj.map[3][0], 3);
    ck_assert_uint_eq(floodObj.map[3][1], 4);
    ck_assert_uint_eq(floodObj.map[3][2], 5);
    ck_assert_uint_eq(floodObj.map[3][3], 6);
}
END_TEST

START_TEST(check_ff_get_path) {
    
    const unsigned width  = 4;
    const unsigned height = 4;
    const unsigned x_goal = 3;
    const unsigned y_goal = 3;
    Maze maze;
    FloodObj floodObj;
    Path path;
    Coord goal;
    Coord mouse_pos;
    goal.x = x_goal;
    goal.y = y_goal;
    mouse_pos.x = 0;
    mouse_pos.y = 0;
    
    ck_assert_uint_eq(set_maze_dimensions(&maze, width, height), 1);
    clear_maze(&maze);
    box_maze(&maze);

    // Check floodfill success
    ck_assert_uint_eq(
        floodfill(&floodObj, &maze, &goal),
        1
    );

    // get path from 0, 0 to 0, 0
    ck_assert_uint_eq(
        ff_get_path(&floodObj, &maze, &goal, &path),
        1
    );
    ck_assert_uint_eq(path.curr, 0);
    ck_assert_uint_eq(path.end , 0);
    ck_assert_uint_eq(path.coords[0].x, x_goal);
    ck_assert_uint_eq(path.coords[0].y, y_goal);


    // Get path from 0, 0 to 3, 3
    ck_assert_uint_eq(
        ff_get_path(&floodObj, &maze, &mouse_pos, &path),
        1
    );
    ck_assert_uint_eq(path.curr, 0);
    ck_assert_uint_eq(path.end , 6);
    ck_assert_uint_eq(path.coords[0].x, 0);
    ck_assert_uint_eq(path.coords[0].y, 0);
    ck_assert_uint_eq(path.coords[1].x, 0);
    ck_assert_uint_eq(path.coords[1].y, 1);
    ck_assert_uint_eq(path.coords[2].x, 0);
    ck_assert_uint_eq(path.coords[2].y, 2);
    ck_assert_uint_eq(path.coords[3].x, 0);
    ck_assert_uint_eq(path.coords[3].y, 3);
    ck_assert_uint_eq(path.coords[4].x, 1);
    ck_assert_uint_eq(path.coords[4].y, 3);
    ck_assert_uint_eq(path.coords[5].x, 2);
    ck_assert_uint_eq(path.coords[5].y, 3);
    ck_assert_uint_eq(path.coords[6].x, 3);
    ck_assert_uint_eq(path.coords[6].y, 3);
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
    tcase_add_test(tc_core, check_floodfill_nonblocking_walls);
    tcase_add_test(tc_core, check_ff_get_path);

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
