#include "Player.h"

// Sorry forgot about it, this one needs to me here, it is the main function of your class, the one that is called
// when we instantiate an object of the class in main.cpp
// usually where you would define the default values of the variables
Player::Player()
{
}

void Player::movePlayer(char direction)
{
    int steps = 1;
    if(direction == 's')
    {
        while(maze->getMazeArray()[xPos][yPos+steps]!=1)  //this works
        {
            if(maze->getMazeArray()[xPos][yPos+steps]==2)
            {
                //connect to database and change values when a chest is encountered
            }
            if(maze->getMazeArray()[xPos-1][yPos+steps] == 0 || maze->getMazeArray()[xPos+1][yPos+steps] == 0)
            {
                steps+=1;
                break;
            }
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
            steps+=1;
        }
        yPos -= steps-1;

    }
}

void Player::spawnPlayer(int x, int y)
{
    xPos = x;
    yPos = y;
}
