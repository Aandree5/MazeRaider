#include "LevelManager.h"

LevelManager::LevelManager()
{
    ui = new UI(this);
    maze = new Maze(31, 31);
    player = new Player();

    player->maze = maze;
    player->xPos = maze->getMazeStart().first;
    player->yPos = maze->getMazeStart().second;

    ui->ShowUI(player);
}
