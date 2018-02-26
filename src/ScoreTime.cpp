#include <iostream>
#include "ScoreTime.h"
#include "UIHelpers.h"
#include "LevelManager.h"
#include "Maze.h"
#include <iostream>
#include <tuple>
#include <string>
#include <windows.h>
#include <mysql.h>
#include <cstdlib>
#include "LevelManager.h"
#include "Player.h"
#include "UI.h"

using namespace std;



ScoreTime::ScoreTime(LevelManager* lvlman)
{
    lvlManager = lvlman;
    //highscore starting by 20000
    hScore = 200000;
    //time starting by 0
    oldTime = 0;

    shouldDecrease = true;

    #ifdef _WIN32
    GetLocalTime(&startTime);
    #endif // _WIN32

    #ifdef __linux__
    time_t T = time(NULL);
    startTime = *localtime(&T);
    #endif // __linux__
}

string ScoreTime::getTime(){
    //this allow you to get the system time
    SYSTEMTIME tm;
    GetLocalTime(&tm);

    int startSec = (startTime.wHour * 3600) + (startTime.wMinute * 60) + startTime.wSecond;
    int tmSec = (tm.wHour * 3600) + (tm.wMinute * 60) + tm.wSecond;

    int difSec = tmSec - startSec;

    int passedHours = difSec / 3600;
    int passedMinutes = (difSec % 3600) / 60;
    int passedSeconds = ((difSec % 3600) % 60);

    //This will allow you to see the timer and also they are starting by zero and increasing by when player input something to the system.
    if(tm.wHour > 0)
        return to_string(passedHours) + ":" + to_string(passedMinutes)+ ":" + to_string(passedSeconds);

}

int ScoreTime::getTimeSeconds(){


    #ifdef _WIN32
    //this will allow you to the get the system time
    SYSTEMTIME tm;
    GetLocalTime(&tm);

    int hourSecond = (tm.wHour - startTime.wHour) * 3600;
    //this will allow the system to calculate the system time. for example a minute has 60 seconds. So this will decrease system time and start time and the value will be times by 60.
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
    //this will decrease the highscore. it will get the time in seconds function and it will decrease by old time then it will multiply by 100
    //basically what it does it will decrease the value of the highscore every second by 100 you spend in the game.
    if(shouldDecrease)
        hScore -= (getTimeSeconds() - oldTime) * 100;

    if(lvlManager->ui->inBattle)
        shouldDecrease = false;
    else
        shouldDecrease = true;


    oldTime = getTimeSeconds();

    //then this will return to the highscore
    return hScore;
}
//Saving the Highscore
int ScoreTime::savehighscore(){
    //you need this to connect to the database
    MYSQL* connection;
    //once you did connect to the database it will say saving in the database
    cout << "Saving in the database..." << endl;
    connection = mysql_init(0);
    //this will allow you to connect to the database
    mysql_real_connect(connection,"server1.jesseprescott.co.uk","jessepre","Mazeraider123?","jessepre_mazeraider",0,NULL,0);

    //we are inserting the values in the highscore so I used insert. so it will store customer id and highscore inside the highscore table.
    //We are using values to tell what we need to store in the database. basically I needed to store playerID and the hScore from the game. So I put that in.

    string data="insert into highscore(char_id, highscore, mazeid) values(" +
    to_string(lvlManager->player->pCharID) + "', '"+to_string(hScore)+"', '" + to_string(lvlManager->getMazeSeed()) + "')";


    int querystate = mysql_query(connection, data.c_str());
    //Once it successful it will say saved successfull.
    if(!querystate) {
        cout<<"Saved...\n\n" << endl;
        cout<<"ID      High Score"<<endl;

    } else {
        //if not it will say failed to save and system will pause. It will wait user to put an input
        cout<<"Failed to save " <<endl;
        cout << mysql_error(connection) << endl;
        system("pause");
    }
}
//Showing up the Highscore in the actual game
int ScoreTime::makeHighscoreTable(){

    int query;
    //You need these to connect to the database and
    MYSQL* connection;
    //these will refers to the rows and results
    MYSQL_ROW row;
    MYSQL_RES *results;


    connection = mysql_init(0);
    //This will allow you to connect to the database.
    mysql_real_connect(connection,"server1.jesseprescott.co.uk","jessepre","Mazeraider123?","jessepre_mazeraider",0,NULL,0);

    string getData = "SELECT h.highscore, pc.name FROM highscore h, PlayerChar pc "
    "WHERE h.char_id=pc.char_id AND h.mazeid=" + to_string(lvlManager->getMazeSeed()) + " ORDER BY h.highscore DESC LIMIT 10";

    //This will select whole highscore table because of the '*'
    query = mysql_query(connection, getData.c_str());
    if(!query){
        //this will allow you to show up the results
        results = mysql_store_result(connection);

        int i=0;
        //rows represent the actual able rows and we will cout them to show up in the actual game.
        while(row = mysql_fetch_row(results))
        {
            //This is the layout of the highscore system.
            cout<<i<<  ".   ||   "<<row[0]<<  "   ||   "<<row[1]<<" ||"<<endl;
            cout<<endl;
            i++;
        }
    }
    else{
        //If it get unsuccessful it will say this message.
        cout<<"Sorry Rank table maintaining stage at this moment try again later"<<endl;
        exit(0);
    }

}

void ScoreTime::addScores(int score)
{
    hScore += score;
}






