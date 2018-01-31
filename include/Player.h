#ifndef PLAYER_H
#define PLAYER_H
#include "Maze.h"
#include <tuple>
#include <array>
#include <vector>
using namespace std;

class Player
{
    public:
        Player();
        //functions
        void spawnPlayer(int x, int y);
        void checkSurrounding(int x, int y);
        void movePlayer(char direction);

        //variables
        vector<int> pathFinder;
        /*  pathFinder[0] = up
            pathFinder[1] = down
            pathFinder[2] = left
            pathFinder[3] = right
        */


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
