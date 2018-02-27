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
    isPaused = false;
    exitToMenu = false;

    maze = new Maze(31, 31);
    player = new Player(this);
    scoretime = new ScoreTime(this);
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
    ui->ShowSelectionScreen();
    ui->ShowUI();
}

int LevelManager::getPlayerID()
{
    return playerID;
}
