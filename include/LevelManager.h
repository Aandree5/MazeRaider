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

        int getPlayerID();
<<<<<<< HEAD
=======
        int getMazeSeed();

        void nextLevel();
        void lowLevel();
        void mediumLevel();
        void highLevel();
        void loadLevel();
        void saveS();
>>>>>>> 979a7bdd2014764ad282952f69348112ddc1675e

        bool isPaused;
        bool exitToMenu;

    protected:

    private:
        int playerID;
<<<<<<< HEAD
=======
        int mazeSeed;
        pair<int, int> mazeSize;
        int nrEnemies;
>>>>>>> 979a7bdd2014764ad282952f69348112ddc1675e
};

#endif // LEVELMANAGER_H
