#ifndef PLAYER_H
#define PLAYER_H
#include "Maze.h"
#include <array>
#include <vector>
#include <cstdlib> //random generation
#include <iostream>

using namespace std;

class Player
{
    public:
        Player();
        //functions
        void spawnPlayer(int x, int y);
        void movePlayer(char direction);
        void chestEvent(void);
        /*
        void enemyEvent();
        */

        //variables
        Maze* maze;
        int xPos, yPos, pPoints, pHealth, pArmor, pDamage, pKeys;
    protected:

    private:
        int life;
        bool carryKeys;

};

#endif // PLAYER_H
