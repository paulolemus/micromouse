# micromouse
Code, schematics, and documentation for the University of Hawaii at Manoa UNICORN X mouse.

# Architecture

The project is structured like an OOP project.
"core" package = All the base code that is necessary to get the mouse running.
"sim" package = Code used for simulation of the micromouse. This includes floodfill, astar, and mouse-vision sims.

# "Core" breakdown

The core package consists of the following core components of the mouse:

* Astar - Powerful pathplanning algorithm
* Floodfill - an alternate and simpler pathplanning algorithm that Astar
* Maze - struct to model a maze, and functions used to create, modify, and delete it.
* PID - Proportional-Integral-Derivative controller used for motor control.

# "Sim" breakdown

This package contains several programs used for simulating a micromouse navigating a maze.
This will be used to determine if the pathplanning algorithms behave as expected, amongst others.

TODO: Everything
