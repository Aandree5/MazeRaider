#ifndef PLAYER_H
#define PLAYER_H
#include <array>
#include <vector>
#include <cstdlib> //random generation
#include <iostream>


using namespace std;

class LevelManager;
class Enemy;
class Maze;
class ScoreTime;

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
        int pCharID = 0;
        string pName = "<player>";
        int pMesh = 0;
        int pHealth = 100;
        int pDamage = 10;
        int pArmour = 2;
        pair<string, int> pWeapon = make_pair("Sword", 10);
        int pKeys = 0;
        int pHealPower = 10;

        // Type is 0 or 1
        // Colour sheet on maizeraider folder
        int pAttackType = 0;
        int pAttackColour = 3;
        int pDefenceType = 0;
        int pDefenceColour = 3;
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
