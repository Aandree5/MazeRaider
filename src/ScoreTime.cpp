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
#include "LevelManager.h"

using namespace std;



ScoreTime::ScoreTime(LevelManager* lvlman)
{
    lvlManager = lvlman;

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

string ScoreTime::getTime(){
    SYSTEMTIME tm;
    GetLocalTime(&tm);

    if(tm.wHour > 0)
        return to_string(tm.wHour - startTime.wHour) + ":" + to_string(tm.wMinute - startTime.wMinute)+ ":" + to_string(abs(tm.wSecond - startTime.wSecond));

}

int ScoreTime::getTimeSeconds(){


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
    hScore -= (getTimeSeconds() - oldTime) * 100;
    oldTime = getTimeSeconds();

    return hScore;
}
int ScoreTime::savehighscore(){

    MYSQL* connection;

    cout << "Saving in the database..." << endl;
    connection = mysql_init(0);
    mysql_real_connect(connection,"server1.jesseprescott.co.uk","jessepre","Mazeraider123?","jessepre_mazeraider",0,NULL,0);

    string data="insert into highscore(customer_id, highscore) values('" + to_string(lvlManager->getPlayerID()) + "', '"+to_string(hScore)+"')";
    int querystate = mysql_query(connection, data.c_str());

    if(!querystate) {
        cout<<"Saved...\n\n" << endl;
        cout<<"ID      High Score"<<endl;

    } else {
        cout<<"Failed to save " <<endl;
        system("pause");
    }


    delete connection;
    connection = nullptr;
}

int ScoreTime::makeHighscoreTable(){

    int query;

    MYSQL* connection;
    MYSQL_ROW row;
    MYSQL_RES *results;


    connection = mysql_init(0);
    mysql_real_connect(connection,"server1.jesseprescott.co.uk","jessepre","Mazeraider123?","jessepre_mazeraider",0,NULL,0);

    query = mysql_query(connection, "SELECT * FROM highscore");
    if(!query){
        results = mysql_store_result(connection);
        while(row = mysql_fetch_row(results))
        {
            cout<<row[2]<<  "   ||   "<<row[1]<<" ||"<<endl;
            cout<<endl;

        }
    }
    else{
        cout<<"Sorry Rank table maintaining stage at this moment try again later"<<endl;
    }

    delete connection;
    connection = nullptr;
    delete results;
    results = nullptr;

}







