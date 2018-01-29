#ifndef PLAYER_H
#define PLAYER_H
#include "Maze.h"

class Player
{
    public:
        void move(int direction);
        void spawnPlayer(int x, int y);
        Maze* maze;

    protected:

    private:



        int life = 9;
        int xPos = 0;
        int yPos = 0;

        bool upM = false;
        bool downM = false;
        bool rightM = false;
        bool leftM = false;

};

#endif // PLAYER_H
