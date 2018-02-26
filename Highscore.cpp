#include "Highscore.h"
#include "ScoreTime.h"

void Highscore::connectToDatabase() {
    MYSQL* connection;
    cout << "Connecting to database..." << endl;
    connection = mysql_init(0);
    mysql_real_connect(connection,"server1.jesseprescott.co.uk","jessepre","Mazeraider123?","jessepre_mazeraider",0,NULL,0);
}

void Highscore::saveScore(int score, int playerID)
{
    string query="INSERT into highscore(" + hsc + ")";

}
