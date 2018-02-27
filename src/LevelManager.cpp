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

    mazeSize = make_pair(25,25);
    nrEnemies = 5;

    loadLevel();

    player = new Player(this);
    scoretime = new ScoreTime(this);
    enemyai = new EnemyAI(this);


    ui = new UI(this);
    ui->ShowSelectionScreen();
    ui->ShowUI();
}

int LevelManager::getPlayerID()
{
    return playerID;
}


/*void LevelManager::saveS()
{
     //connecting to database
    //MYSQL* connection;

    connection = mysql_init(0);
    mysql_real_connect(connection,"server1.jesseprescott.co.uk","jessepre","Mazeraider123?","jessepre_mazeraider",0,NULL,0);
    if(!connection)
    {
        cout << "Failed to connect to the database." << endl;
    }
    int getS = maze->getSeed();
    string inSeed = "INSERT into maze(mazeid)values('"getS"')";
    int qstate = mysql_query(connection,inSeed.c_str());

    if(!qstate) {
        cout<<"Registration successful" << endl;
        system("pause");
        cin;
    } else {
        cout<<"Failed to register, error: " << mysql_error(connection) << endl;
        system("pause");
    }





*/





//Next level is chosen by computer according to the score value

void LevelManager::nextLevel()
{
    if(scoretime->getHScore() >=195000)
    {
         mazeSize = make_pair(mazeSize.first +6, mazeSize.second +6);

    nrEnemies = 8;
    for(Enemy *e : enemies)
    {
        delete e;
        e = nullptr;
    }

    enemies.clear();

    delete maze;

    loadLevel();

    player->maze = maze;
    player->xPos = maze->getMazeStart().first;
    player->yPos = maze->getMazeStart().second;
    }

    else if(scoretime->getHScore()<195000||scoretime->getHScore()>=180000)

    {
        mazeSize = make_pair(mazeSize.first -4, mazeSize.second -4);

        nrEnemies = 4;
        for(Enemy *e : enemies)
        {
            delete e;
            e = nullptr;
        }

        enemies.clear();

        delete maze;

        loadLevel();

        player->maze = maze;
        player->xPos = maze->getMazeStart().first;
        player->yPos = maze->getMazeStart().second;
    }

    else
    {
        mazeSize = make_pair(mazeSize.first-10, mazeSize.second - 10);

        nrEnemies = 2;
        for(Enemy *e : enemies)
        {
            delete e;
            e = nullptr;
        }

        enemies.clear();

        delete maze;

        loadLevel();

        player->maze = maze;
        player->xPos = maze->getMazeStart().first;
        player->yPos = maze->getMazeStart().second;
    }
}

void LevelManager::loadLevel()
{
    maze = new Maze(mazeSize.first, mazeSize.second);
    for(int i=0; i<nrEnemies; i++)
     {
         enemies.emplace_back(new Enemy(maze));
     }

}

void LevelManager::lowLevel()
{
  mazeSize = make_pair(mazeSize.first - 10, mazeSize.second - 10);

    nrEnemies = 3;
    for(Enemy *e : enemies)
    {
        delete e;
        e = nullptr;
    }

    enemies.clear();

    delete maze;

    loadLevel();

    player->maze = maze;
    player->xPos = maze->getMazeStart().first;
    player->yPos = maze->getMazeStart().second;


}


void LevelManager::mediumLevel()
{
  mazeSize = make_pair(mazeSize.first - 6, mazeSize.second - 6);

    nrEnemies =6;
    for(Enemy *e : enemies)
    {
        delete e;
        e = nullptr;
    }

    enemies.clear();

    delete maze;

    loadLevel();

    player->maze = maze;
    player->xPos = maze->getMazeStart().first;
    player->yPos = maze->getMazeStart().second;


}

void LevelManager::highLevel()
{
  mazeSize = make_pair(mazeSize.first + 10, mazeSize.second + 10);

    nrEnemies = 10 ;
    for(Enemy *e : enemies)
    {
        delete e;
        e = nullptr;
    }

    enemies.clear();

    delete maze;

    loadLevel();

    player->maze = maze;
    player->xPos = maze->getMazeStart().first;
    player->yPos = maze->getMazeStart().second;


}
