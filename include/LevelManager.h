#ifndef LEVELMANAGER_H
#define LEVELMANAGER_H
#include <vector>

using namespace std;

class UI;
class Maze;
class Player;
class Enemy;
class ScoreTime;

class LevelManager
{
    public:
        LevelManager();

        UI* ui;
        Maze* maze;
        Player* player;
        ScoreTime* scoretime;
        vector<Enemy*> enemies;

    protected:

    private:
};

#endif // LEVELMANAGER_H
