#include "Maze.h"
#include "UI.h"
#include "Player.h"
#include "Score.h"
#include <iostream>
#include <tuple>

using namespace std;

int main()
{
    Score* score = new Score();
    Maze* maze = new Maze(31, 31);
    UI* ui = new UI(maze, score);

    Player* player = new Player();
    player->maze = maze;
    player->xPos = maze->getMazeStart().first;
    player->yPos = maze->getMazeStart().second ;

    ui->ShowUI(player);
    return 0;
}
