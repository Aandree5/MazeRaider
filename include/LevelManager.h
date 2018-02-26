#ifndef LEVELMANAGER_H
#define LEVELMANAGER_H
#include <vector>

using namespace std;

class UI;
class Maze;
class Player;
class Enemy;
class ScoreTime;
class EnemyAI;

class LevelManager
{
    public:
        LevelManager(int pID);

        UI* ui;
        Maze* maze;
        Player* player;
        ScoreTime* scoretime;
        EnemyAI* enemyai;
        vector<Enemy*> enemies;

        int getPlayerID();
        int getMazeSeed();

    protected:

    private:
        int playerID;
        int mazeSeed;
};

#endif // LEVELMANAGER_H
