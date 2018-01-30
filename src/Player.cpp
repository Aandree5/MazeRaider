#include "Player.h"
#include <iostream>

/*



*/

// Sorry forgot about it, this one needs to me here, it is the main function of your class, the one that is called
// when we instantiate an object of the class in main.cpp
// usually where you would define the default values of the variables
Player::Player()
{
}

void Player::move(char direction)
{
    //check surroundings
    /*if(get<0>(maze->getDataMWH())[xPos - 1][yPos]=1)
        leftM = false;
    if(get<0>(maze->getDataMWH())[xPos + 1][yPos]=1)
        rightM = false;
        */
    //move the player

    std::cout << direction << std::endl;

    //give options
}




void Player::spawnPlayer(int x, int y)
{
    xPos = x;
    yPos = y;
}
