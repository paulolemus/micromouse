# Micromouse
Code, schematics, and documentation for the University of Hawaii at Manoa UNICORN X mouse.

## The Team

* Paulo Lemus => Software lead
* Nicole Hortizuela => Hardware Lead
* Rodolfo Julian => Hardware
* Eva Keeslar => Hardware and Software

## Table of Contents

* [Purpose](#purpose)
* [Building](#building)
* [Architecture](#architecture)

## Purpose

We are Team UNICORN X. Our purpose is to build an autonomous micromouse that is exemplary at mapping and solving NxN mazes. Our mouse, the UNICORN X, is a side-sensing, DC motor mouse controlled by a PIC32MK MCU. Our goal for this semester is to win first place at the University of Hawaii at Manoa fall Micromouse competition.

## Building

This is primarily a C project. We use CMake as our primary build system for desktop builds.
To build the code, do the following from the project root:
```bash
cd build
cmake ../
make
```
These commands should build all tests into the tests/ folder, and all executables into the bin/ folder.

## Architecture

This project has three primary "modules", which are **core**, **sim**, and **pic**.
**Core** contains all the code that makes up the library that is our micromouse. This code is independent from any specific PIC, simulation, or display. It contains the data structures and functions used for creating and modifying a representation of a maze. It contains pathplanning algorithms used to solve a maze, and our PID controllers. It also contains useful functions for parsing a maze from file.
**Sim** is the module that allows us to have a graphical representation of a maze, and to simulate what happens when we try to send our mouse through it, or when we would like to run a pathplanning algorithm on a maze. It makes use of **core** to build structures, and displays them to a screen.
**Pic** contains all the code required to flash everything to our MCU. This includes MCU specific configurations (PRAGMAS), and mouse maze solving logic, as well as sensor polling / motor control / ADC functions.
