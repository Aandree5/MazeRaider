#include "LevelManager.h"
#include "UI.h"
#include "Maze.h"
#include "Player.h"
#include "ScoreTime.h"
#include "Enemy.h"

LevelManager::LevelManager()
{
    maze = new Maze(31, 31);
    player = new Player();
    scoretime = new ScoreTime();

    player->maze = maze;
    player->xPos = maze->getMazeStart().first;
    player->yPos = maze->getMazeStart().second;

    enemies.emplace_back(new Enemy(maze));

    ui = new UI(this);
    ui->ShowUI();
}
