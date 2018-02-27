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
        //This will get the highscore
        int getHScore();

        int getTime();

        int savehighscore();

        void connectToDatabase();
        void makeHighscoreTable();

        //this will get the timer
        string getTime();
        //this will allow get time in seconds
        int getTimeSeconds();
        //this function allow to save the game
        int savehighscore();
        //this will allow the user to get the data as a string and show up on the screen
        int query();
        //connect to the database
        void connectToDatabase();
        //this will allow user to make the highscore
        int makeHighscoreTable();
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
        //I am using this to use oldtime
        int oldTime;
        //this will allow to get the score
        int hScore;
        //this will allow to decrease the score by time
        bool shouldDecrease;
};

#endif // SCORETIME_H
