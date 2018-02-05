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
    if(maze->getMazeArray()[xPos - 1][yPos]==1)
    {
        pathFinder[2] = 1;
    }else{
        pathFinder[2] = 0;
    }

    if(maze->getMazeArray()[xPos + 1][yPos]==1)
    {
        pathFinder[3] = 1;
    }else{
        pathFinder[3] = 0;
    }

    if(maze->getMazeArray()[xPos][yPos - 1]==1)
    {
        pathFinder[0] = 1;
    }else{
        pathFinder[0] = 0;
    }
    if(maze->getMazeArray()[xPos][yPos + 1]==1)
    {
        pathFinder[1] = 1;
    }else{
        pathFinder[1] = 0;
    }
}

void Player::movePlayer(char direction)
{
    int steps = 1;
    if(direction == 's')
    {
        while(maze->getMazeArray()[xPos][yPos+steps]!=1)
        {
            steps+=1;
            if(maze->getMazeArray()[xPos-1][yPos+steps] == 1)//|| maze->getMazeArray()[xPos+1][yPos+steps-1]==1)
            {
                break;
            }

        }
        yPos += steps-1;
        /*
        while(maze->getMazeArray()[xPos][yPos+steps]!=1) //not yet reached a wall going down
        {
            yPos += steps;
            if(maze->getMazeArray()[xPos-steps][yPos]==1 || maze->getMazeArray()[xPos+steps][yPos]==1) //there's a path from either side
            {
                checkSurrounding(xPos, yPos+steps);
                yPos += steps;
                break;
            }
            steps+=1;
        }*/
    }
    else if(direction == 'a')
    {
        while(maze->getMazeArray()[xPos-steps][yPos]!=1)
        {
            steps+=1;
        }
        xPos -= steps-1;
        /*
        while(maze->getMazeArray()[xPos-1][yPos]!=1) //not yet reached a wall going left
        {
            if(maze->getMazeArray()[xPos][yPos+1]==1 || maze->getMazeArray()[xPos][yPos-1]==1) //there's a path from either side
            {
                checkSurrounding(xPos+steps, yPos);
                steps = 0;
                break;
            }
            steps-=1;
        }*/
    }else if(direction=='d')
    {
        while(maze->getMazeArray()[xPos+steps][yPos]!=1)
        {
            steps+=1;
        }
        xPos += steps-1;
        /*
        while(maze->getMazeArray()[xPos+1][yPos]!=1) //not yet reached a wall going right
        {
            if(maze->getMazeArray()[xPos][yPos+1]==1 || maze->getMazeArray()[xPos][yPos-1]==1) //there's a path from either side
            {
                checkSurrounding(xPos+steps, yPos);
                steps = 0;
                break;
            }
            steps+=1;
        }*/
    }else if(direction=='w')
    {
        while(maze->getMazeArray()[xPos][yPos-steps]!=1)
        {
            steps+=1;
        }
        yPos -= steps-1;
        /*
        while(maze->getMazeArray()[xPos][yPos-1]!=1) //not yet reached a wall going up
        {
            if(maze->getMazeArray()[xPos-1][yPos]==1 || maze->getMazeArray()[xPos+1][yPos]==1) //there's a path from either side
            {
                checkSurrounding(xPos, yPos+steps);
                steps = 0;
                break;
            }
            steps-=1;
        }*/
    }
}

void Player::spawnPlayer(int x, int y)
{
    xPos = x;
    yPos = y;
}
