#ifndef ENEMY_H
#define ENEMY_H
#include <array>
#include <vector>
#include <cstdlib> //random generation
#include <iostream>

using namespace std;

class Maze;

class Enemy
{
    public:
        Enemy(Maze* m);

        //functions
        void randomMoveEnemy();
        // 0 = Up | 1 = Right | 1 = Down | 3 = Left
        void moveEnemy(int direction);

        // Enemy stats
        int getHealth();
        int getArmor();
        int getPower();
        int getHealPower();

        // Animation types
        int getAttackColour();
        int getAttackType();
        int getDefenceColour();
        int getDefenceType();
        int getHealColour();
        int getHealType();


        //variables
        Maze* maze;
        int xPos, yPos;


    protected:

    private:
        // Moving variables
        int eDirection, ranVal, ranDecision;

        // Enemy stats
        int health, armor, power, healPower;

        // Animation types
        int attackColour, attackType, defenceColour, defenceType, healColour, healType;
};

#endif // ENEMY_H
