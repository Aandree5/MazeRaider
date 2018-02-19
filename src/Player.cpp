#include "Player.h"

Player::Player()
{
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
            if(maze->getMazeArray()[xPos-1][yPos+steps] == 0 || maze->getMazeArray()[xPos+1][yPos+steps] == 0)
            {
                steps+=1;
                break;
            }
            else if(maze->getMazeArray()[xPos][yPos+steps] == 3)
            {
                Player::chestEvent();
                break;
            }/*
            if(maze->getMazeArray()[xPos][yPos+steps]==4) //checks to see if enemy is there
            {
                break;
            }*/
            steps+=1;


        }
        yPos += steps-1;
    }
    else if(direction == 'a')
    {
        while(maze->getMazeArray()[xPos-steps][yPos]!=1)
        {
            if(maze->getMazeArray()[xPos-steps][yPos+1] == 0 || maze->getMazeArray()[xPos-steps][yPos-1] == 0)
            {
                steps+=1;
                break;
            }
            else if(maze->getMazeArray()[xPos-steps][yPos] == 3)
            {
                Player::chestEvent();
                break;
            }/*
            if(maze->getMazeArray()[xPos-steps][yPos]==4) //checks to see if enemy is there
            {
                break;
            }*/
            steps+=1;

        }
        xPos -= steps-1;

    }else if(direction=='d')
    {
        while(maze->getMazeArray()[xPos+steps][yPos]!=1)
        {
            if(maze->getMazeArray()[xPos+steps][yPos+1] == 0 || maze->getMazeArray()[xPos+steps][yPos-1] == 0)
            {
                steps+=1;
                break;
            }
            else if(maze->getMazeArray()[xPos+steps][yPos] == 3)
            {
                Player::chestEvent();
                break;
            }/*
            if(maze->getMazeArray()[xPos+steps][yPos]==4) //checks to see if enemy is there
            {
                break;
            }*/
            steps+=1;

        }
        xPos += steps-1;

    }else if(direction=='w')
    {
        while(maze->getMazeArray()[xPos][yPos-steps]!=1)
        {
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
            /*if(maze->getMazeArray()[xPos][yPos-steps]==4) //checks to see if enemy is there
            {
                break;
            }*/
            steps+=1;

        }
        yPos -= steps-1;

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
    int randomScore, addHealth, addArmor, addDamage, addKeys;
    randomScore = rand() % 100 + 1;
    addArmor = rand() % 10 + 1;
    addHealth = rand() % 10 + 1;
    addKeys = rand() % 2;
    addDamage = rand() % 10 + 1;

    pPoints += randomScore;
    pArmor += addArmor;
    pHealth += addHealth;
    pKeys += addKeys;
    pDamage += addDamage;
}


void Player::spawnPlayer(int x, int y)
{
    xPos = x;
    yPos = y;
}
