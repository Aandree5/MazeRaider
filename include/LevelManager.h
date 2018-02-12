#ifndef LEVELMANAGER_H
#define LEVELMANAGER_H

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
        Enemy* enemy;

    protected:

    private:
};

#endif // LEVELMANAGER_H
