#include "Player.h"
#include "LevelManager.h"
#include "Enemy.h"
#include "BattleScene.h"
#include "UI.h"

Player::Player(weak_ptr<LevelManager> lvlman)
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
    for(shared_ptr<Enemy> e : lvlmanager->enemies)
    {
        if((x == e->xPos) && (y == e->yPos))
        {
            lvlmanager->ui->btlScene = make_shared<BattleScene>(lvlmanager, e); // Andre's code
        }
    }
}

