#include "Player.h"
#include "LevelManager.h"
#include "Enemy.h"
#include "BattleScene.h"
#include "UI.h"
#include "UIHelpers.h"
#include "Maze.h"
#include "ScoreTime.h"

using namespace UIHelpers;

Player::Player(LevelManager *lvlman)
{
    lvlmanager = lvlman;
    maze = lvlman->maze.get();
    xPos = lvlman->maze->getMazeStart().first;
    yPos = lvlman->maze->getMazeStart().second;

}
/*
check to see if player has key to open exit
check to see if player meets enemy
*/



void Player::movePlayer(char direction)
{
    lvlmanager->playEffect(LevelManager::Effect::Move);

    Player::checkEnemy(xPos,yPos);
    int steps = 1;
    if(direction == 's')
    {
        while(maze->getMazeArray()[xPos][yPos+steps]!=1)  //this works
        {
            checkEnemy(xPos,yPos+steps);
            if(lvlmanager->ui->inBattle)
                break;

            //checking to see if there's a path on both sides
            if(maze->getMazeArray()[xPos-1][yPos+steps] == 0 || maze->getMazeArray()[xPos+1][yPos+steps] == 0)
            {
                steps+=1;
                break;
            }
            //checking to see if there's a chest in front
            else if(maze->getMazeArray()[xPos][yPos+steps] == 3)
            {
                Player::chestEvent();
                break;
            }
            //checking to see if the exit is on the right
            else if(maze->getMazeArray()[xPos+1][yPos+steps] == 5)
            {
                steps+=1;
                break;
            }
            steps+=1;
        }
        yPos += steps-1;
        checkChest();
    }
    else if(direction == 'a')
    {
        while(maze->getMazeArray()[xPos-steps][yPos]!=1)
        {
            checkEnemy(xPos-steps,yPos);
            if(lvlmanager->ui->inBattle)
                break;

            if(maze->getMazeArray()[xPos-steps][yPos+1] == 0 || maze->getMazeArray()[xPos-steps][yPos-1] == 0)
            {
                steps+=1;
                break;
            }
            else if(maze->getMazeArray()[xPos-steps][yPos] == 3)
            {
                Player::chestEvent();
                break;
            }
            steps+=1;
        }
        xPos -= steps-1;
        checkChest();
    }
    else if(direction=='d')
    {
        while(maze->getMazeArray()[xPos+steps][yPos]!=1)
        {
        void startBattleScene(Enemy &enemy);
            checkEnemy(xPos+steps,yPos);
            if(lvlmanager->ui->inBattle)
                break;

            if(maze->getMazeArray()[xPos+steps][yPos+1] == 0 || maze->getMazeArray()[xPos+steps][yPos-1] == 0)
            {
                steps+=1;
                break;
            }
            else if(maze->getMazeArray()[xPos+steps][yPos] == 3)
            {
                Player::chestEvent();
                break;
            }
            //checking to see if the player is facing the exit
            else if(maze->getMazeArray()[xPos+steps][yPos] == 5)
            {
                lvlmanager->ui->ShowNextLevel();
                break;
            }
            steps+=1;

        }
        xPos += steps-1;
        checkChest();
    }
    else if(direction=='w')
    {
        while(maze->getMazeArray()[xPos][yPos-steps]!=1)
        {
            checkEnemy(xPos, yPos-steps);
            if(lvlmanager->ui->inBattle)
                break;

            if(maze->getMazeArray()[xPos-1][yPos-steps] == 0 || maze->getMazeArray()[xPos+1][yPos-steps] == 0)
            {
                steps+=1;
                break;
            }
            else if(maze->getMazeArray()[xPos][yPos-steps] == 3)
            {
                Player::chestEvent();
                break;
            }
            else if(maze->getMazeArray()[xPos+1][yPos-steps] == 5)
            {
                steps+=1;
                break;
            }

            steps+=1;

        }
        yPos -= steps-1;
        checkChest();
    }
}

void Player::chestEvent(void)
{
    /*
    random rewards or drops
    - health
    - sword upgrade
    - armor upgrade
    - potions
    - keys
    - scores
    */

    lvlmanager->playEffect(LevelManager::Effect::PickUp);

    //connecting to database
    MYSQL* connection;

    connection = mysql_init(0);
    mysql_real_connect(connection,"server1.jesseprescott.co.uk","jessepre","Mazeraider123?","jessepre_mazeraider",0,NULL,0);
    if(!connection){
        cout << "Failed to connect to the database." << endl;
    }

    //query for getting the weapon
    string getWeapon = "SELECT weapon_name, weapon_power, weapon_id FROM Weapon ORDER BY RAND() LIMIT 1";

    if (!mysql_query(connection, getWeapon.c_str()))
        cout << mysql_error(connection) << endl;

    //storing and reading the result from getting the weapon from the database
    MYSQL_RES* result = mysql_store_result(connection);
    MYSQL_ROW row = mysql_fetch_row(result);
    pWeapon = make_pair(row[0],atoi(row[1]));
    cout << row[0] << row[1] << endl;

    //query for changing the value on the player's weapon
    string saveWeapon = SQLPrepare("UPDATE PlayerChar SET weapon_id= '%?' WHERE char_id= '%?'", atoi(row[2]), pCharID);

    if (!mysql_query(connection, saveWeapon.c_str()))
        cout << mysql_error(connection) << endl;


    //make random values for player stats and add them
    int randomScore, addHealth, addArmour, addDamage, addKeys;
    randomScore = rand() % 100 + 1;
    addArmour = rand() % 100 + 10;
    addHealth = rand() % 100 + 10;
    addKeys = rand() % 1;
    addDamage = rand() % 100 + 50;

    playerPoints += randomScore;
    lvlmanager->scoretime->addScores(playerPoints);
    pArmour += addArmour;
    pHealth += addHealth;
    pKeys += addKeys;
    pDamage += addDamage;

    // Andre's Code
    string message = "You just earned " + to_string(randomScore) + " points, " +  to_string(addArmour) +
    " armour, " + to_string(addHealth) + " health, " + to_string(addDamage) + " damage";

    if(addKeys > 0)
        message += " ," + to_string(addKeys) + " keys";

    message += ".";


    UpdateMessageInfo(lvlmanager->ui->mazeInfo, message, MessageType::PickUp);
}

void Player::checkChest()
{
    if(maze->getMazeArray()[xPos][yPos+1]==3)
    {
        maze->updateChest(xPos, yPos+1);
    }else if(maze->getMazeArray()[xPos][yPos-1]==3)
    {
        maze->updateChest(xPos, yPos-1);
    }else if(maze->getMazeArray()[xPos+1][yPos]==3)
    {
        maze->updateChest(xPos+1, yPos);
    }else if(maze->getMazeArray()[xPos-1][yPos]==3)
    {
        maze->updateChest(xPos-1, yPos);
    }
}

void Player::checkEnemy(int x, int y)
{
    for(shared_ptr<Enemy> e : lvlmanager->enemies)
    {
        if((x == e->xPos) && (y == e->yPos))
        {
           lvlmanager->ui->StartBattleScene(e); // Andre's code
           break;
        }
    }
}
