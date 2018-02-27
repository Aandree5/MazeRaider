#ifndef LEVELMANAGER_H
#define LEVELMANAGER_H
#include <vector>
#include <memory>

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

        UI *ui;
        Maze *maze;
        Player *player;
        ScoreTime *scoretime;
        EnemyAI *enemyai;
        vector<Enemy*> enemies;

        int getPlayerID();

        bool isPaused;
        bool exitToMenu;

        void nextLevel();
        void lowLevel();
        void mediumLevel();
        void highLevel();

    protected:

    private:

        pair<int, int> mazeSize;
        int nrEnemies;

        int playerID;

        void loadLevel();
};

#endif // LEVELMANAGER_H
