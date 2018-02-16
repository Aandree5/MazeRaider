#include <iostream>
#include "ScoreTime.h"

using namespace std;



ScoreTime::ScoreTime()
{
    hScore = 200000;
    oldTime = 0;

    #ifdef _WIN32
    GetLocalTime(&startTime);
    #endif // _WIN32

    #ifdef __linux__
    time_t T = time(NULL);
    startTime = *localtime(&T);
    #endif // __linux__
}

int ScoreTime::getTime(){


    #ifdef _WIN32
    SYSTEMTIME tm;
    GetLocalTime(&tm);

    int hourSecond = (tm.wHour - startTime.wHour) * 60 * 60;
    int minSecond = (tm.wMinute - startTime.wMinute) * 60;

    return hourSecond + minSecond + (tm.wSecond - startTime.wSecond);
    #endif // _WIN32

    #ifdef __linux__
    time_t T = time(NULL);
    struct  tm tm = *localtime(&T);

    int hourSecond = (tm.tm_hour - startTime.tm_hour) * 60 * 60;
    int minSecond = (tm.tm_min - startTime.tm_min) * 60;

    return hourSecond + minSecond + (tm.tm_sec - startTime.tm_sec);
    #endif // __linux__
}

int ScoreTime::getHScore()
{
    hScore -= (getTime() - oldTime) * 100;
    oldTime = getTime();

    return hScore;
}


