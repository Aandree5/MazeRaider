#include "Player.h"
#include "LevelManager.h"
#include "Enemy.h"
#include "BattleScene.h"
#include "UI.h"

Player::Player(LevelManager* lvlman)
{
    lvlmanager = lvlman;
    maze = lvlman->maze;
    xPos = lvlman->maze->getMazeStart().first;
    yPos = lvlman->maze->getMazeStart().second;

}
/*
check to see if player has key to open exit
check to see if player meets enemy



*/



void Player::movePlayer(char direction)
{
    Player::checkEnemy(xPos,yPos);
    int steps = 1;
    if(direction == 's')
    {
        while(maze->getMazeArray()[xPos][yPos+steps]!=1)  //this works
        {
            checkEnemy(xPos,yPos+steps);
            if(maze->getMazeArray()[xPos-1][yPos+steps] == 0 || maze->getMazeArray()[xPos+1][yPos+steps] == 0)
            {
                steps+=1;
                break;
            }
            else if(maze->getMazeArray()[xPos][yPos+steps] == 3)
            {
                Player::chestEvent();
                break;
            }
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
            checkEnemy(xPos+steps,yPos);
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
            else if(maze->getMazeArray()[xPos+steps][yPos] == 5)
            {
                reachExit = true;
                steps+=1;
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


    //connecting to database
    MYSQL* connection;

    connection = mysql_init(0);
    mysql_real_connect(connection,"server1.jesseprescott.co.uk","jessepre","Mazeraider123?","jessepre_mazeraider",0,NULL,0);
    if(!connection){
        cout << "Failed to connect to the database." << endl;
    }

    //query for getting the weapon
    string getWeapon = "SELECT weapon_name, weapon_power, weapon_id FROM Weapon ORDER BY RAND() LIMIT 1;";

    if (!mysql_query(connection, getWeapon.c_str()))
        cout << mysql_error(connection) << endl;

    //storing and reading the result from getting the weapon from the database
    MYSQL_RES* result = mysql_store_result(connection);
    MYSQL_ROW row = mysql_fetch_row(result);
    pWeapon = make_pair(row[0],atoi(row[1]));
    cout << row[0] << row[1] << endl;

    //query for changing the value on the player's weapon
    string saveWeapon = "UPDATE PlayerChar SET weapon_id=" + to_string(atoi(row[2])) + " WHERE char_id=" + to_string(pCharID);

    if (!mysql_query(connection, saveWeapon.c_str()))
        cout << mysql_error(connection) << endl;


    //make random values for player stats and add them
    int randomScore, addHealth, addArmour, addDamage, addKeys;
    randomScore = rand() % 100 + 1;
    addArmour = rand() % 10 + 1;
    addHealth = rand() % 10 + 1;
    addKeys = rand() % 1;
    addDamage = rand() % 10 + 1;

    playerPoints += randomScore;
    pArmour += addArmour;
    pHealth += addHealth;
    pKeys += addKeys;
    pDamage += addDamage;

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
    for(Enemy* e : lvlmanager->enemies)
    {
        if((x == e->xPos) && (y == e->yPos))
        {
            lvlmanager->ui->btlScene = new BattleScene(lvlmanager, e); // Andre's code
        }
    }
}

