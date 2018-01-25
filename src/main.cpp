#include "Maze.h"
#include <iostream>

using namespace std;

int main()
{
    Maze* maze = new Maze(15, 15);
    maze->printMaze();
    return 0;
}
