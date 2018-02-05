#ifndef LEVELMANAGER_H
#define LEVELMANAGER_H
#include "UI.h"
#include "Maze.h"
#include "Player.h"

class LevelManager
{
    public:
        LevelManager();

        UI* ui;
        Maze* maze;
        Player* player;

    protected:

    private:
};

#endif // LEVELMANAGER_H
