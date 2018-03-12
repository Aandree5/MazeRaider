#include "Enemy.h"
#include "Maze.h"
#ifdef _WIN32
#include <windows.h>
#endif // _WIN32
#include <mysql.h>
#include <sstream>
#include "UIHelpers.h"
#include "ScoreTime.h"

using namespace UIHelpers;

Enemy::Enemy(shared_ptr<LevelManager> l)
{
    lvlManager = l;

    statsFromDatabase();
    //system("pause");

    //spawn enemy
    int x,y;

    while(true)
    {
        x = rand() % (l->maze->getMazeSizeWH().first - 6) + 5;
        y = rand() % (l->maze->getMazeSizeWH().second - 2) + 1;

        // Only spawn in places where player can stop
        if(l->maze->getMazeArray()[x][y]==0 && !(l->maze->getMazeArray()[x + 1][y] == 1 && l->maze->getMazeArray()[x - 1][y] == 1 &&
                                           l->maze->getMazeArray()[x][y + 1] == 0 && l->maze->getMazeArray()[x][y - 1] == 0) &&
                                         !(l->maze->getMazeArray()[x + 1][y] == 0 && l->maze->getMazeArray()[x - 1][y] == 0 &&
                                           l->maze->getMazeArray()[x][y + 1] == 1 && l->maze->getMazeArray()[x][y - 1] == 1))
        {
            break;
        }
    }

    xPos = x;
    yPos = y;
    followingPlayer = false;
}
Enemy::~Enemy()
{
    //gain points from defeating an enemy
    int scoreAdded;
    scoreAdded = rand() % 100 + 1;

    //add the added score to the main score
    if(lvlManager.lock()->exitToMenu == false){
        lvlManager.lock()->scoretime->addScores(scoreAdded);
    }
}

void Enemy::randomMoveEnemy()
{
    if(shared_ptr<LevelManager> l = lvlManager.lock())
    {
          ranDecision = rand() % 2 + 1;
    if(ranDecision == 1) // random chance of moving
    {
        ranDecision = rand() % 3 + 1;
        eDirection = rand() % 4 + 1; //random direction to move
        ranVal = rand() % 20 + 1; //random steps
        /*Direction
        1 = down
        2 = left
        3 = up
        4 = right
        */
        if(eDirection == 1)
        {
            for(int i = 1;i < ranVal; i++)
            {
                if(l->maze->getMazeArray()[xPos][yPos+i]==1) // checks wall forward
                {
                    yPos+=i-1;
                    break;
                }
                else if((l->maze->getMazeArray()[xPos-1][yPos+i] == 0 || l->maze->getMazeArray()[xPos+1][yPos+i] == 0) && (ranDecision == 1 || ranDecision == 2)) //checks path from sides
                {
                    yPos+=i;
                    break;
                }
                else if(l->maze->getMazeArray()[xPos][yPos+i]==2) // checks player forward
                {
                    yPos+=i-1;
                    break;
                }
            }
        }
        else if(eDirection == 2)
        {
            for(int i = 1;i < ranVal; i++)
            {
                if(l->maze->getMazeArray()[xPos-i][yPos]==1) // checks wall forwards
                {
                    xPos-=i-1;
                    break;
                }
                else if((l->maze->getMazeArray()[xPos-i][yPos+1] == 0 || l->maze->getMazeArray()[xPos-i][yPos-1] == 0) && (ranDecision == 1 || ranDecision == 2)) //checks path from sides
                {
                    xPos-=i;
                    break;
                }
                else if(l->maze->getMazeArray()[xPos-i][yPos]==2) // checks player forward
                {
                    yPos+=i-1;
                    break;
                }
            }
        }
        else if(eDirection == 3)
        {
            for(int i = 1;i < ranVal; i++)
            {
                if(l->maze->getMazeArray()[xPos+i][yPos]==1) // checks wall forwards
                {
                    xPos+=i-1;
                    break;
                }else if((l->maze->getMazeArray()[xPos+i][yPos+1] == 0 || l->maze->getMazeArray()[xPos+i][yPos-1] == 0) && (ranDecision == 1 || ranDecision == 2)) //checks path from sides
                {
                    xPos+=i-1;
                    break;
                }
                else if(l->maze->getMazeArray()[xPos+i][yPos]==2) // checks player forward
                {
                    yPos+=i-1;
                    break;
                }
            }
        }
        else if(eDirection == 4)
        {
            for(int i = 1;i < ranVal; i++)
            {
                if(l->maze->getMazeArray()[xPos][yPos-i]==1) // checks wall forward
                {
                    yPos-=i-1;
                    break;
                }else if((l->maze->getMazeArray()[xPos-1][yPos-i] == 0 || l->maze->getMazeArray()[xPos+1][yPos-i] == 0) && (ranDecision == 1 || ranDecision == 2)) //checks path from sides
                {
                    yPos-=i-1;
                    break;
                }
                else if(l->maze->getMazeArray()[xPos][yPos-i]==2) // checks player forward
                {
                    yPos+=i-1;
                    break;
                }
            }
        }
    }
    }
}



void Enemy::checkPlayer(){}
//function runs when one of the enemies is next to a player
/*if((maze->getMazeArray()[xPos][yPos+1]==2) || (maze->getMazeArray()[xPos][yPos-1]==2) || (maze->getMazeArray()[xPos+1][yPos]==2) || (maze->getMazeArray()[xPos-1][yPos]==2))
{
    //run battle scene -
    //Andre, you can call the function that runs the battle scene here. Initiate battle scene or something
}*/

void Enemy::statsFromDatabase()
{
    MYSQL* connection;
    connection = mysql_init(0);

    mysql_real_connect(connection, "server1.jesseprescott.co.uk", "jessepre", "Mazeraider123?", "MazeRaider_DB", 0, NULL, 0);
    if(!connection)
    {
        cout << "Failed to connect to the database." << endl;
        exit(0);
    }

    string query = "SELECT e.name, e.mesh, e.health, e.armour, e.attackPower, w.weaponName, w.weaponPower, e.healPower, "
    "w.attackType, w.attackColour, e.defenceType, e.defenceColour, e.healType, e.healColour "
    "FROM Enemy e, Weapon w WHERE e.weaponID = w.weaponID "
    "ORDER BY RAND() LIMIT 1";

    if (mysql_query(connection, query.c_str()))
        cout << mysql_error(connection) << endl;

    MYSQL_RES* result = mysql_store_result(connection);
    MYSQL_ROW row = mysql_fetch_row(result);

    name = row[0];
    mesh = atoi(row[1]);
    health = atoi(row[2]);
    armour = atoi(row[3]);
    attackPower = atoi(row[4]);
    weapon.first = row[5];
    weapon.second = atoi(row[6]);
    healPower = atoi(row[7]);
    attackType = atoi(row[8]);
    attackColour = atoi(row[9]);
    defenceType = atoi(row[10]);
    defenceColour = atoi(row[11]);
    healType = atoi(row[12]);
    healColour = atoi(row[13]);

    /* close connection */
    mysql_free_result(result);
    mysql_close(connection);
}

string Enemy::getName()
{
    return name;
}

int Enemy::getMesh()
{
    return mesh;
}

int Enemy::getHealth()
{
    return health;
}

int Enemy::getArmour()
{
    return armour;
}

int Enemy::getAttackPower()
{
    return attackPower;
}

pair<string, int> Enemy::getWeapon()
{
    return weapon;
}

int Enemy::getHealPower()
{
    return healPower;
}
// Animation types
int Enemy::getAttackColour()
{
    return attackColour;
}

int Enemy::getAttackType()
{
    return attackType;
}

int Enemy::getDefenceColour()
{
    return defenceColour;
}

int Enemy::getDefenceType()
{
    return defenceType;
}

int Enemy::getHealColour()
{
    return healColour;
}

int Enemy::getHealType()
{
    return healType;
}
