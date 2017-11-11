# Micromouse
Code, schematics, and documentation for the University of Hawaii at Manoa UNICORN X mouse.

## The Team

* Paulo Lemus => Software lead
* Nicole Hortizuela => Hardware lead
* Rodolfo Julian => Hardware
* Eva Keeslar => Hardware

## Table of Contents

* [Purpose](#purpose)
* [Building for Linux](#building-for-linux)
* [Building for MCU](#building-for-mcu)
* [Testing](#testing)
* [Architecture](#architecture)

## Purpose

We are Team UNICORN X. Our purpose is to build an autonomous micromouse that is exemplary at mapping and solving NxN mazes. Our mouse, the UNICORN X, is a side-sensing, DC motor mouse controlled by a PIC32MK MCU. Our goal for this semester is to win first place at the University of Hawaii at Manoa fall Micromouse competition.

## Building for Linux

This is primarily a C project. CMake is our primary build tool.
Micromouse is developed on Arch Linux (4.9.61-1-lts) using gcc (7.2.0) as the default C compiler, but has been built and executed on Ubuntu 16.04. To build for Linux, type the following from the project root folder:
```bash
cd build
cmake -DPIC_TARGET:BOOL=OFF ../
make
```
These commands should build all tests into the tests/ folder, and all executables into the bin/ folder.

## Building for MCU

The code is written targeting a specific Microchip MCU, the PIC32MK1024MCF064. The Core library has not yet been build for the MCU, nor has the cmake been configured for the Microchip XC32 compiler, however the following would be used from the root folder:
```bash
cd build
cmake -DPIC_TARGET::BOOL=ON ../
make
```

## Testing

We use *Check*, a unit testing framework for C for all tests. The test source files and binaries (once built) can be found in the tests/ folder.
To build and run all tests, do the following from the project root:
```bash
cd build
cmake -DPIC_TARGET:BOOL=OFF ../
make && make test
```
OR to view test output:
```bash
cd build
cmake -DPIC_TARGET:BOOL=OFF ../
make && ctest --verbose
```

## Architecture

This project has three primary "modules", which are **core**, **sim**, and **pic**.
**Core** contains all the code that makes up the library that is our micromouse. This code is independent from any specific PIC, simulation, or display. It contains the data structures and functions used for creating and modifying a representation of a maze. It contains pathplanning algorithms used to solve a maze, and our PID controllers. It also contains useful functions for parsing a maze from file.
**Sim** is the module that allows us to have a graphical representation of a maze, and to simulate what happens when we try to send our mouse through it, or when we would like to run a pathplanning algorithm on a maze. It makes use of **core** to build structures, and displays them to a screen.
**Pic** contains all the code required to flash everything to our MCU. This includes MCU specific configurations (PRAGMAS), and mouse maze solving logic, as well as sensor polling / motor control / ADC functions.
