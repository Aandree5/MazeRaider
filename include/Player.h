#ifndef PLAYER_H
#define PLAYER_H
#include "Maze.h"
#include <array>
#include <vector>
#include <cstdlib> //random generation
using namespace std;

class Player
{
    public:
        Player();
        //functions
        void spawnPlayer(int x, int y);
        void movePlayer(char direction);
        void checkSurrounding(int x, int y);
        void chestEvent();

        //variables
        Maze* maze;
        int xPos;
        int yPos;
    protected:

    private:
        int life;

};

#endif // PLAYER_H
