#ifndef PLAYER_H
#define PLAYER_H
#include "Maze.h"
#include <tuple>
#include <array>
#include <vector>

class Player
{
    public:
        Player();
        //functions
        void spawnPlayer(int x, int y);
        void checkSurrounding(int x, int y);
        void movePlayer(int direction);
        /*  down = 2
            left = 4
            right = 6
            up = 8
        */



        //variables
        vector<int> pathFinder;


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
