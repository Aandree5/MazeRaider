#ifndef PLAYER_H
#define PLAYER_H
#include "Maze.h"

class Player
{
    public:
        Player();
        void move(int direction);
        void spawnPlayer(int x, int y);
        Maze* maze;

        int xPos;
        int yPos;
    protected:

    private:
        int life;

        bool upM = false;
        bool downM = false;
        bool rightM = false;
        bool leftM = false;

};

#endif // PLAYER_H
