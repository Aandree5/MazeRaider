#include "LevelManager.h"
#include "UI.h"
#include "Maze.h"
#include "Player.h"
#include "Score.h"

LevelManager::LevelManager()
{
    maze = new Maze(31, 31);
    player = new Player();
    score = new Score();

    player->maze = maze;
    player->xPos = maze->getMazeStart().first;
    player->yPos = maze->getMazeStart().second;

    ui = new UI(this);
    ui->ShowUI();
}
