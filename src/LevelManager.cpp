#include "LevelManager.h"
#include "UI.h"
#include "Maze.h"
#include "Player.h"
#include "ScoreTime.h"
#include "Enemy.h"
#include "EnemyAI.h"

LevelManager::LevelManager(int pID)
{
    playerID = pID;

    int xWidth, yLength;
    xWidth = rand() % 100 + 10;
    yLength = rand() % 30 + 10;

    maze = new Maze(xWidth, yLength);
    mazeSeed = maze->getSeed();

    player = new Player(this);
    scoretime = new ScoreTime(this);
    enemyai = new EnemyAI(this);

/*
    enemies.emplace_back(new Enemy(maze));
    enemies.emplace_back(new Enemy(maze));
    enemies.emplace_back(new Enemy(maze));
    enemies.emplace_back(new Enemy(maze));
    enemies.emplace_back(new Enemy(maze));
    enemies.emplace_back(new Enemy(maze));
    enemies.emplace_back(new Enemy(maze));
    enemies.emplace_back(new Enemy(maze));
*/

    ui = new UI(this);
    ui->ShowSelectionScreen();
    ui->ShowUI();
}

int LevelManager::getPlayerID()
{
    return playerID;
}

int LevelManager::getMazeSeed()
{
    return mazeSeed;
}
