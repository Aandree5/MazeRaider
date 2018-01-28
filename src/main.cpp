#include "Maze.h"
#include "UI.h"
#include <iostream>

using namespace std;

int main()
{
    Maze* maze = new Maze(31, 31);

    UI::ShowUI(maze);
    return 0;
}
