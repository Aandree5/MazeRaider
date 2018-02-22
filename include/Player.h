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
        void movePlayer(char direction);
        void chestEvent(void);
        void checkChest();
        void checkEnemy(int x, int y);


        int playerPoints = 0;
        int pHealth = 100;
        int pDamage = 10;
        int pArmor = 2;
        pair<string, int> pWeapon = make_pair("Sword", 10);
        int pKeys = 0;
        int pHealPower = 10;

        // Type is 0 or 1
        // Colour sheet on maizeraider folder
        int pAttackType = 0;
        int pAttackColour = 10;
        int pDefendType = 0;
        int pDefendColour = 3;
        int pHealType = 0;
        int pHealColour = 2;

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
