#ifndef LEVELMANAGER_H
#define LEVELMANAGER_H

class UI;
class Maze;
class Player;
class ScoreTime;

class LevelManager
{
    public:
        LevelManager();

        UI* ui;
        Maze* maze;
        Player* player;
        ScoreTime* scoretime;

    protected:

    private:
};

#endif // LEVELMANAGER_H
