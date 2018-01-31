#include "Maze.h"
#include "UI.h"
#include <iostream>
#include "Player.h"
#include <tuple>

using namespace std;

int main()
{
    Maze* maze = new Maze(31, 31);
    UI* ui = new UI(maze);

    Player* player = new Player();
    player->maze = maze;
    player->xPos = maze->getMazeStart().first;
    player->yPos = maze->getMazeStart().second ;

    ui->ShowUI(player);
    return 0;
}
