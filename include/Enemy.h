#ifndef ENEMY_H
#define ENEMY_H
#include "Maze.h"
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
        void moveEnemy(void);



        //variables
        Maze* maze;
        int xPosEnemy, yPosEnemy;


    protected:

    private:
        int eDirection, ranVal, ranDecision;
};

#endif // ENEMY_H
