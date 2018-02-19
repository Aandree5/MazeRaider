#include <iostream>
#include "ScoreTime.h"
#include "UIHelpers.h"
#include "LevelManager.h"
#include <iostream>
#include <tuple>
#include <string>
#include <windows.h>
#include <mysql.h>
#include <cstdlib>

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
int ScoreTime::savehighscore(){

    MYSQL* connection;

    cout << "Connecting to database..." << endl;
    connection = mysql_init(0);
    mysql_real_connect(connection,"server1.jesseprescott.co.uk","jessepre","Mazeraider123?","jessepre_mazeraider",0,NULL,0);

    string data="insert into highscore(highscore) values('"+to_string(hScore)+"')";
    const char* q = data.c_str();
    int qstate = mysql_query(connection,q);

    if(!qstate) {
        cout<<"Registration successful" << endl;
        system("pause");
    } else {
        cout<<"Failed to register, error: " << mysql_error(connection) << endl;
        system("pause");
    }
}

/*int ScoreTime::makeHighscoreTable()
{
    //get the top 10 scores from the high score table and store the names and scores in to an array
    string query="select MAX(highscore) from information where username='"+username+"' and password='"+password+"';";




}*/



