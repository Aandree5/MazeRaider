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

        void nextLevel();
        void lowLevel();
        void mediumLevel();
        void highLevel();
        void loadLevel();
        void saveS();

    protected:

    private:
        int playerID;
        int mazeSeed;
        pair<int, int> mazeSize;
        int nrEnemies;
};

#endif // LEVELMANAGER_H
