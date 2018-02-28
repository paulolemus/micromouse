# Developer Log October 16th 2017

I ran into a couple of issues when trying to make my code compatible with any size maze.

## Leading up to finding the issue

Here is what I have been doing and where I planned on going.
I am currently building all code that that does not contain a "main" into a single "micromouse" library.
This includes all the functions that modify a maze, the parser, the pid controllers.
All of this code references a config.h file that contains values such as the maze width and height.

To determine maze size for each executable I link this library to, I would then undef the width and height macros and then redefine them to the appropriate size per the executable.
For example, in my tests I would have a small maze that is 4x4 because it is easy to check every possible block to ensure all values are correct. In the simulation program, I would use a 16x16 maze.

## The Problems

I am unable to redefine a macro in an executable that exists in the library. The functions that had the macros baked in would not change, and my clear\_maze function would always iterate through a maze of size 16 regardless of the redefined size of width and height.

I am unable to define differently sized mazes per executable.

## The Solution (?)

To work around this, I am going to limit the max size of the maze to whatever is originally defined for the width and height in config.h. This means that I can parse and operate on any maze leading up to this maze width and height.
