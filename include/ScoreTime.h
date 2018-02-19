#ifndef SCORETIME_H
#define SCORETIME_H
#include <array>

#ifdef __WIN32
#include <windows.h>
#endif // __WIN32

using namespace std;

class ScoreTime
{
    public:
        ScoreTime();

        int getHScore();

        int getTime();

        int savehighscore();

        void connectToDatabase();
        void makeHighscoreTable();

    protected:

    private:
        #ifdef _WIN32
            SYSTEMTIME startTime;
        #endif // _WIN32

        #ifdef __linux__
        struct  tm startTime;
        #endif // __linux__

        int oldTime;

        int hScore;
};

#endif // SCORETIME_H
