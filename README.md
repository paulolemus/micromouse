# Micromouse
Code, schematics, and documentation for the University of Hawaii at Manoa UNICORN X mouse.

NOTE: THE REPO IS CURRENTLY BEING REFACTORED. THIS NOTE WILL BE REMOVED WHEN THE REFACTOR IS FINISHED

## The Team

* Paulo Lemus => Software lead
* Nicole Hortizuela => Hardware lead
* Rodolfo Julian => Hardware
* Eva Keeslar => Hardware

## Table of Contents

* [Purpose](#purpose)
* [Getting Started](#getting-started)
* [Prerequisites](#prerequisites)
* [Building for Linux](#building-for-linux)
* [Building for MCU](#building-for-mcu)
* [Testing](#testing)

## Purpose

We are Team UNICORN X. Our purpose is to build an autonomous robotic mouse that is exemplary at mapping and solving NxN mazes. Our mouse, the UNICORN X, is a side-sensing, DC motor mouse controlled by a dsPIC33 MCU. Our goal for this semester is to win first place at the University of Hawaii at Manoa fall Micromouse competition.

## Getting Started

### Prerequisites

All the code has been run and tested primarily on Arch Linux (4.9.61-1-lts) and Ubuntu 17.10. All the installation instructions will assume that you are using Ubuntu.

For a desktop build you will need to install [CMake](https://cmake.org/), [Check](https://github.com/libcheck/check), and [NCurses](https://www.gnu.org/software/ncurses/).

```bash
sudo apt install cmake check libncurses-dev
```

To build for the dsPIC33FJ128MC804 MCU, please install both the [MPLAB X IDE](http://www.microchip.com/mplab/mplab-x-ide) and the [MPLAB XC16 Compiler](http://www.microchip.com/mplab/compilers).


### Building for Linux

To build a desktop executables as well as tests:
```bash
cd build
cmake -DPIC_TARGET:BOOL=OFF ..
make
```
These commands should build all tests into the tests/ folder, and all executables into the bin/ folder in this root directory.

### Building for MCU

The code is written targeting a specific Microchip MCU, the dsPIC33FJ128MC804. The MPLAB X IDE is used with a [PICkit 3](http://www.microchip.com/Developmenttools/ProductDetails.aspx?PartNO=PG164130) to build and flash code to the mouse. To build for the MCU follow these steps:

* Open the MPLAB X IDE.
* Open the micromouse project.
* Set the project as default in the "Production" tab.
* Plug the PICkit 3 into your computer.
* Connect pin 1 of the PICkit to pin 1 of the 5 pin breakout male header on the mouse.
* Press the green arrow "Run Main Project" button in MPLAB X.

### Testing

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
