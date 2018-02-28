# Developer Log October 20th

Recently began thinking about how floodfill is going to be implemented, how generic I should attempt to make it's usage, and how to store the path returned from floodfill.

One note first: There should be no dynamic memory allocation because to use that with the xc32 compiler I would need to specify heap size at compile time, which I do not want to worry about. Everything should be able to make use of stack declared variables.

## Floodfill information:

Goal value is 0.
All surrounding accessable squares are given value current + 1.
Once entire maze has been numbered, then the shortest path traces from the current location following the smallest number until end is reached.

## For the primary floodfill function:

Need to get a reference to the mouse's representation of the maze.
Need get coordinates of goal.
Using maze, do floodfill, save values in matrix.

Now we have a maze with the floodfill values.
There should be another function, get\_path, which is given the floodfill maze and a path struct or variable, then gets the shortest path. Returns 1 on success 0 on failure.

Specify max length of a path, which is going to be set with a defined config value.
If we get to the end or close to the end, we should be able to re-run the function that returns the path. If it doesn't work, then we need to re-run the pathplanning function.

Floodfill just needs a matrix to fill with values.


## Food for thought

The floodfill algorithm probably should not keep any internal state, as it might be used for either finding shortest path to center or to an unexplored block.

Consider making a data structure that can be compatible with both A\* and with floodfill.

Do I need to care about keeping state outside of the function?
I'll probably need to run the algorithm again very soon if I am exploring attempting to find a path to the center.


Both algorithms need:
get path and get directions functions.

Directions needs get path function
