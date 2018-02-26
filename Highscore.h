#include "UIHelpers.h"
#include "LevelManager.h"
#include <iostream>
#include <tuple>
#include <string>
#include <windows.h>
#include <mysql.h>
#include <cstdlib>

using namespace std;

class Highscore
{
    public:

        void connectToDatabase();

        void Highscore::saveScore(int score, int playerID);

    protected:

    private:
};
