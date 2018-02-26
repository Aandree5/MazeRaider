#ifndef SCORETIME_H
#define SCORETIME_H
#include <array>

#ifdef __WIN32
#include <windows.h>
#endif // __WIN32

using namespace std;

class LevelManager;

class ScoreTime
{
    public:
        ScoreTime(LevelManager* lvlman);

        int getHScore();

        string getTime();

        int getTimeSeconds();

        int savehighscore();

        int query();

        void connectToDatabase();
        int makeHighscoreTable();

        int hScore;

        void addScores(int score);

    protected:

    private:
        LevelManager* lvlManager;

        #ifdef _WIN32
            SYSTEMTIME startTime;
        #endif // _WIN32

        #ifdef __linux__
        struct  tm startTime;
        #endif // __linux__

        int oldTime;

        bool shouldDecrease;
};

#endif // SCORETIME_H
