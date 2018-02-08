#include <iostream>
#include <windows.h>
#include "ScoreTime.h"

using namespace std;



ScoreTime::ScoreTime()
{
    hScore = 200000;
    oldTime = 0;
    GetLocalTime(&startTime);
}

int ScoreTime::getTime(){

    SYSTEMTIME a;
    GetLocalTime(&a);

    int hourSecond = (a.wHour - startTime.wHour) * 60 * 60;
    int minSecond = (a.wMinute - startTime.wMinute) * 60;

    return hourSecond + minSecond + (a.wSecond - startTime.wSecond);
}

int ScoreTime::getHScore()
{
    hScore -= (getTime() - oldTime) * 100;
    oldTime = getTime();

    return hScore;
}


