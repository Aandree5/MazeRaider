#ifndef ENEMY_H
#define ENEMY_H
#include "ScoreTime.h"
#include <array>
#include <vector>
#include <cstdlib> //random generation
#include <iostream>
#include <memory>

using namespace std;

class Maze;
class LevelManager;

class Enemy
{
    public:
        Enemy(shared_ptr<Maze> m);
        ~Enemy();

        //functions
        void randomMoveEnemy();
        void checkPlayer();

        // Enemy stats
        string getName();
        int getMesh();
        int getHealth();
        int getArmour();
        int getAttackPower();
        pair<string, int> getWeapon();
        int getHealPower();

        // Animation types
        int getAttackColour();
        int getAttackType();
        int getDefenceColour();
        int getDefenceType();
        int getHealColour();
        int getHealType();


        //variables
        weak_ptr<Maze> maze;
        int xPos, yPos;

        bool followingPlayer;

    protected:

    private:
        void statsFromDatabase();

        // Moving variables
        int eDirection, ranVal, ranDecision;

        // Enemy stats
        string name;
        pair<string, int> weapon;
        int mesh, health, armour, attackPower, healPower;

        // Animation types
        int attackColour, attackType, defenceColour, defenceType, healColour, healType;
};

#endif // ENEMY_H
