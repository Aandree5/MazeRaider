#ifndef PLAYER_H
#define PLAYER_H
#include "Maze.h"
#include "Enemy.h"
#include <array>
#include <vector>
#include <cstdlib> //random generation
#include <iostream>

using namespace std;

class LevelManager;

class Player
{
    public:
        Player(LevelManager* lvlma);
        //functions
        void spawnPlayer(int x, int y);
        void movePlayer(char direction);
        void chestEvent(void);
        void checkChest();
        void checkEnemy(int x, int y);


        int playerPoints = 0;
        int pHealth = 100;
        int pDamage = 10;
        int pArmor = 10;
        int pKeys = 0;

        //variables
        Maze* maze;
        int xPos, yPos;
    protected:

    private:
        LevelManager* lvlmanager;
        int life;
        bool carryKeys;

};

#endif // PLAYER_H
