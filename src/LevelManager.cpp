#include "LevelManager.h"
#include "UI.h"
#include "Maze.h"
#include "Player.h"
#include "ScoreTime.h"
#include "Enemy.h"
#include "EnemyAI.h"

LevelManager::LevelManager()
{
    maze = new Maze(31, 31);
    player = new Player(this);
    player->maze = maze;
    player->xPos = maze->getMazeStart().first;
    player->yPos = maze->getMazeStart().second;

    scoretime = new ScoreTime();
    enemyai = new EnemyAI(this);


    enemies.emplace_back(new Enemy(maze));
    enemies.emplace_back(new Enemy(maze));
    enemies.emplace_back(new Enemy(maze));
    enemies.emplace_back(new Enemy(maze));
    enemies.emplace_back(new Enemy(maze));
    enemies.emplace_back(new Enemy(maze));
    enemies.emplace_back(new Enemy(maze));
    enemies.emplace_back(new Enemy(maze));

    ui = new UI(this);
    ui->ShowUI();
}
