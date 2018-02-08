#ifndef SCORETIME_H
#define SCORETIME_H
#include <array>

using namespace std;

class ScoreTime
{
    public:
        ScoreTime();

        int getHScore();

        int getTime();

    protected:

    private:
        SYSTEMTIME startTime;

        int oldTime;

        int hScore;
};

#endif // SCORETIME_H
