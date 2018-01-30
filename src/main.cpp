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
    player->xPos = get<3>(maze->getDataMWH()).first;
    player->yPos = get<3>(maze->getDataMWH()).second ;

    ui->ShowUI(player);
    return 0;
}
