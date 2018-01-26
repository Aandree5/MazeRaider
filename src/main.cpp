#include "Maze.h"
#include <iostream>

using namespace std;

int main()
{
    Maze* maze = new Maze(31, 31);
    maze->printMaze();
    return 0;
}
