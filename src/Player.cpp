#include "Player.h"

// Sorry forgot about it, this one needs to me here, it is the main function of your class, the one that is called
// when we instantiate an object of the class in main.cpp
// usually where you would define the default values of the variables
Player::Player()
{
}

void Player::checkSurrounding(int x, int y)
{
    xPos = x;
    yPos = y;
    //check surroundings
    if(get<0>(maze->getDataMWH())[xPos - 1][yPos]==1)
    {
        pathFinder[2] = 1;
    }else{
        pathFinder[2] = 0;
    }

    if(get<0>(maze->getDataMWH())[xPos + 1][yPos]==1)
    {
        pathFinder[3] = 1;
    }else{
        pathFinder[3] = 0;
    }

    if(get<0>(maze->getDataMWH())[xPos][yPos - 1]==1)
    {
        pathFinder[0] = 1;
    }else{
        pathFinder[0] = 0;
    }
    if(get<0>(maze->getDataMWH())[xPos][yPos + 1]==1)
    {
        pathFinder[1] = 1;
    }else{
        pathFinder[1] = 0;
    }
}

void Player::movePlayer(char direction)
{
    int steps = 0;
    if(direction=="s")
    {
        while(get<0>(maze->getDataMWH())[xPos][yPos+1]!=1) //not yet reached a wall
        {
            if(get<0>(maze->getDataMWH())[xPos-1][yPos]==1 || get<0>(maze->getDataMWH())[xPos+1][yPos]==1) //there's a path from either side
            {
                checkSurrounding(xPos, yPos+steps);
                break;
            }
            steps+=1;
        }
    }else if(direction=="a")
    {
        while(get<0>(maze->getDataMWH())[xPos-1][yPos]!=1) //not yet reached a wall
        {
            if(get<0>(maze->getDataMWH())[xPos][yPos+1]==1 || get<0>(maze->getDataMWH())[xPos][yPos-1]==1) //there's a path from either side
            {
                checkSurrounding(xPos+steps, yPos);
                steps = 0;
                break;
            }
            steps-=1;
        }
    }else if(direction=="d")
    {
        while(get<0>(maze->getDataMWH())[xPos+1][yPos]!=1) //not yet reached a wall
        {
            if(get<0>(maze->getDataMWH())[xPos][yPos+1]==1 || get<0>(maze->getDataMWH())[xPos][yPos-1]==1) //there's a path from either side
            {
                checkSurrounding(xPos+steps, yPos);
                steps = 0;
                break;
            }
            steps+=1;
        }
    }else if(direction=="w")
    {
        while(get<0>(maze->getDataMWH())[xPos][yPos-1]!=1) //not yet reached a wall
        {
            if(get<0>(maze->getDataMWH())[xPos-1][yPos]==1 || get<0>(maze->getDataMWH())[xPos+1][yPos]==1) //there's a path from either side
            {
                checkSurrounding(xPos, yPos+steps);
                steps = 0;
                break;
            }
            steps-=1;
        }
    }
}


void Player::spawnPlayer(int x, int y)
{
    xPos = x;
    yPos = y;
}
