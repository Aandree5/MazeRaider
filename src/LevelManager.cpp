#include "LevelManager.h"
#include "UI.h"
#include "Maze.h"
#include "Player.h"
#include "ScoreTime.h"
#include "Enemy.h"
#include "EnemyAI.h"
#include <cstdlib>
#include <sstream>
#include <string>

LevelManager::LevelManager(int pID)
{
    playerID = pID;
    isPaused = false;
    exitToMenu = false;

    mazeSize = make_pair(25,25);
    nrEnemies = 5;

    loadLevel();

    player = new Player(this);
    enemyai = new EnemyAI(this);


    ui = new UI(this);
    ui->ShowSelectionScreen();

    scoretime = new ScoreTime(this);

    ui->ShowUI();
}

LevelManager::~LevelManager()
{
    delete ui;
    ui = nullptr;
    delete maze;
    maze = nullptr;
    delete player;
    player = nullptr;
    delete scoretime;
    scoretime = nullptr;
    delete enemyai;
    enemyai = nullptr;

    for(Enemy *e : enemies)
    {
        delete e;
        e = nullptr;
    }
}

int LevelManager::getPlayerID()
{
    return playerID;
}

void LevelManager::changeMusic(Music m){

    if(music != m && !isMuted){
        music = m;
        std::ostringstream oss;
        int i;
        switch(music){

        case Music::SelectionScreen:
            PlaySound(TEXT("sounds/musics/SelectionScreen.wav"),NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
            break;

        case Music::Map:
            i = rand() % 7 + 1;
            oss << "sounds/musics/Map_" << i << ".wav";
            PlaySound(TEXT(oss.str().c_str()), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
            break;

        case Music::Muted:
            PlaySound(NULL, 0,0);
            break;

        default:
            PlaySound(TEXT("sounds/musics/MainMenu.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
            break;

        }
    }

}

void LevelManager::playEffect(Effect e){

    if(!isMuted){
        switch(e){
    case Effect::Move:
        mciSendString("close Move", NULL, 0, NULL);
        mciSendString("open sounds/effects/Move.wav alias Move", NULL, 0, 0);
        mciSendString("play Move", NULL, 0, NULL);
        break;

    case Effect::Run:
        mciSendString("close Run", NULL, 0, NULL);
        mciSendString("open sounds/effects/Run.wav alias Run", NULL, 0, 0);
        mciSendString("play Run", NULL, 0, NULL);
        break;

    case Effect::PickUp:
        mciSendString("close PickUp", NULL, 0, NULL);
        mciSendString("open sounds/effects/PickUp.wav alias PickUp", NULL, 0, 0);
        mciSendString("play PickUp", NULL, 0, NULL);
        break;

    case Effect::Attack:
        mciSendString("close Attack", NULL, 0, NULL);
        mciSendString("open sounds/effects/Attack.wav alias Attack", NULL, 0, 0);
        mciSendString("play Attack", NULL, 0, NULL);
        break;

    case Effect::Defend:
        mciSendString("close Defend", NULL, 0, NULL);
        mciSendString("open sounds/effects/Defend.wav alias Defend", NULL, 0, 0);
        mciSendString("play Defend", NULL, 0, NULL);
        break;

    case Effect::EnemyKilled:
        mciSendString("close EnemyKilled", NULL, 0, NULL);
        mciSendString("open sounds/effects/EnemyKilled.wav alias EnemyKilled", NULL, 0, 0);
        mciSendString("play EnemyKilled", NULL, 0, NULL);
        break;

    case Effect::Heal:
        mciSendString("close Heal", NULL, 0, NULL);
        mciSendString("open sounds/effects/Heal.wav alias Heal", NULL, 0, 0);
        mciSendString("play Heal", NULL, 0, NULL);
        break;

    case Effect::LevelPassed:
        mciSendString("close LevelPassed", NULL, 0, NULL);
        mciSendString("open sounds/effects/LevelPassed.wav alias LevelPassed", NULL, 0, 0);
        mciSendString("play LevelPassed", NULL, 0, NULL);
        break;

    case Effect::LevelLost:
        mciSendString("close LevelLost", NULL, 0, NULL);
        mciSendString("open sounds/effects/LevelLost.wav alias LevelLost", NULL, 0, 0);
        mciSendString("play LevelLost", NULL, 0, NULL);
        break;

    case Effect::PauseOpen:
        mciSendString("close PauseOpen", NULL, 0, NULL);
        mciSendString("open sounds/effects/PauseOpen.wav alias PauseOpen", NULL, 0, 0);
        mciSendString("play PauseOpen", NULL, 0, NULL);
        break;

    case Effect::PauseClose:
        mciSendString("close PauseClose", NULL, 0, NULL);
        mciSendString("open sounds/effects/PauseClose.wav alias PauseClose", NULL, 0, 0);
        mciSendString("play PauseClose", NULL, 0, NULL);
        break;
        }
    }

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
    maze = nullptr;

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
        maze = nullptr;

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
        maze = nullptr;

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
    maze = nullptr;

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
    maze = nullptr;

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
    maze = nullptr;

    loadLevel();

    player->maze = maze;
    player->xPos = maze->getMazeStart().first;
    player->yPos = maze->getMazeStart().second;


}
