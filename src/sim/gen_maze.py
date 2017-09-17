#!/usr/bin/env python3
"""
A Python3 script used to draw a maze and write it to file for parsing.
"""

import curses
from curses import ascii


# GLOBALS
NORTH_WALL = 'NORTH'
SOUTH_WALL = 'SOUTH'
EAST_WALL  = 'EAST'
WEST_WALL  = 'WEST'

header = '{} {}\n' # Width and Height
template = '{},{} {}\n' # x, y, items


class Maze:
    def __init__(self, width, height):
        self.width = width
        self.height = height
        self.maze = [[[] for y in range(height)] for x in range(width)]

        # Box the maze
        for block in self.maze[0]:
            block.append(WEST_WALL)
        for block in self.maze[-1]:
            block.append(EAST_WALL)
        for x in range(len(self.maze)):
            self.maze[x][0].append(SOUTH_WALL)
            self.maze[x][-1].append(NORTH_WALL)

    def toggleNorth(self, x, y):
        if NORTH_WALL in self.maze[x][y]:
            self.maze[x][y].remove(NORTH_WALL)
        else:
            self.maze[x][y].append(NORTH_WALL)

    def toggleSouth(self, x, y):
        if SOUTH_WALL in self.maze[x][y]:
            self.maze[x][y].remove(SOUTH_WALL)
        else:
            self.maze[x][y].append(SOUTH_WALL)

    def toggleEast(self, x, y):
        if EAST_WALL in self.maze[x][y]:
            self.maze[x][y].remove(EAST_WALL)
        else:
            self.maze[x][y].append(EAST_WALL)

    def toggleWest(self, x, y):
        if WEST_WALL in self.maze[x][y]:
            self.maze[x][y].remove(WEST_WALL)
        else:
            self.maze[x][y].append(WEST_WALL)

    def sortBlocks(self):
        for lst in self.maze:
            for block in lst:
                block.sort()

    # Return string formatted for file
    def __str__(self):
        lines = []
        lines.append(header.format(self.width, self.height))

        for x in range(self.width):
            for y in range(self.height):
                line = template.format(x, y, ' '.join(self.maze[x][y]))
                lines.append(line)
        return ''.join(lines)

    def __repr__(self):
        return 'Maze(width={}, height={})\n'.format(self.width, self.height) + str(self.maze)


class GUI:
    def __init__(self, maze):
        self.maze = maze
        self.scrwidth = maze.width * 2 + 1
        self.scrheight = maze.height * 2 + 1

    @staticmethod
    def scrinit():
        stdscr = curses.initscr()
        curses.noecho()
        curses.cbreak()
        stdscr.keypad(True)
        return stdscr

    def finish(self):
        curses.nocbreak()
        self.stdscr.keypad(False)
        curses.echo()
        curses.endwin()

    def moveCursor(self):
        # left
        if self.key == 'j':
            self.xscr -= 2
        # up
        elif self.key == 'i':
            self.yscr -= 2
        # right
        elif self.key == 'l':
            self.xscr += 2
        # down
        elif self.key == 'k':
            self.yscr += 2
        self.stdscr.move(self.yscr, self.xscr)

    # convert xscr to x: x = (xscr - 1) / 2
    # convert yscr to y: y = m(aze.height - 1) - (yscr - 1) / 2
    def updateMaze(self):

        if self.key == 'a' or \
           self.key == 's' or \
           self.key == 'd' or \
           self.key == 'w':

            x = int((self.xscr - 1) / 2)
            y = int((self.maze.height - 1) - (self.yscr - 1) / 2)

            if self.key == 'a':
                self.maze.toggleWest(x, y)
                x -= 1
                if x >= 0:
                    self.maze.toggleEast(x, y)

            elif self.key == 's':
                self.maze.toggleSouth(x, y)
                y -= 1
                if y >= 0:
                    self.maze.toggleNorth(x, y)

            elif self.key == 'd':
                self.maze.toggleEast(x, y)
                x += 1
                if x < self.maze.width:
                    self.maze.toggleWest(x, y)

            elif self.key == 'w':
                self.maze.toggleNorth(x, y)
                y += 1
                if y < self.maze.height:
                    self.maze.toggleSouth(x, y)

            return True
        else:
            return False


    # convert x to scrx: scrx = x * 2 + 1
    # convery y to scry: scry = (scrheight - 2) - 2 * y
    def renderMaze(self):
        self.stdscr.clear()
        matrix = self.maze.maze

        for x in range(self.maze.width):
            for y in range(self.maze.height):

                xcenter = x * 2 + 1
                ycenter = (self.scrheight - 2) - (2 * y)

                if NORTH_WALL in matrix[x][y]:
                    self.stdscr.addch(ycenter - 1, xcenter, curses.ACS_HLINE)
                if EAST_WALL in matrix[x][y]:
                    self.stdscr.addch(ycenter, xcenter + 1, curses.ACS_VLINE)
                if SOUTH_WALL in matrix[x][y]:
                    self.stdscr.addch(ycenter + 1, xcenter, curses.ACS_HLINE)
                if WEST_WALL in matrix[x][y]:
                    self.stdscr.addch(ycenter, xcenter - 1, curses.ACS_VLINE)



    def main(self):
        self.stdscr = GUI.scrinit()
        self.xscr = 1
        self.yscr = 1
        self.key = None

        self.renderMaze()
        self.stdscr.move(self.yscr, self.xscr)

        while self.key != '\n':
            self.key = self.stdscr.getkey()
            self.moveCursor()

            if self.updateMaze():
                self.renderMaze()
                self.stdscr.move(self.yscr, self.xscr)

            self.stdscr.refresh()

        self.finish()





def main():
    # Text user input
    print('Welcome to the maze generator!')
    width = int(input('Enter maze width : '))
    height = int(input('Enter maze height: '))
    filename = input('Enter generated filename: ')

    # create maze
    maze = Maze(width, height)

    # Allow user to fill maze
    gui = GUI(maze)
    try:
        gui.main()
    except Exception as err:
        curses.nocbreak()
        curses.echo()
        curses.endwin()
        print('CAUGHT EXCEPTION')
        print(err)

    # Write maze to text file
    maze.sortBlocks()
    contents = str(maze)
    print(contents)

    filehandle = open(filename, 'w')
    filehandle.write(contents)
    filehandle.close()



if __name__ == '__main__':
    main()
