#ifndef LEVELMANAGER_H
#define LEVELMANAGER_H

class UI;
class Maze;
class Player;
class Score;

class LevelManager
{
    public:
        LevelManager();

        UI* ui;
        Maze* maze;
        Player* player;
        Score* score;

    protected:

    private:
};

#endif // LEVELMANAGER_H
