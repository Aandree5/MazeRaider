#include "Enemy.h"
#include "Maze.h"
#include <windows.h>
#include <mysql.h>
#include <sstream>
Enemy::Enemy(Maze* m)
{
    maze = m;

    statsFromDatabase();
    //system("pause");

    //spawn enemy
    int x,y;

    while(true)
    {
        x = rand() % (maze->getMazeSizeWH().first - 6) + 5;
        y = rand() % (maze->getMazeSizeWH().second - 2) + 1;

        // Only spawn in places where player can stop
        if(maze->getMazeArray()[x][y]==0 && !(maze->getMazeArray()[x + 1][y] == 1 && maze->getMazeArray()[x - 1][y] == 1 &&
                                             maze->getMazeArray()[x][y + 1] == 0 && maze->getMazeArray()[x][y - 1] == 0) &&
                                            !(maze->getMazeArray()[x + 1][y] == 0 && maze->getMazeArray()[x - 1][y] == 0 &&
                                             maze->getMazeArray()[x][y + 1] == 1 && maze->getMazeArray()[x][y - 1] == 1))
        {
            break;
        }
    }

    xPos = x;
    yPos = y;
}
Enemy::~Enemy()
{
    //gain points from defeating an enemy
    int scoreAdded;
    scoreAdded = rand() % 100 + 1;
}

void Enemy::randomMoveEnemy()
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
                if(maze->getMazeArray()[xPos][yPos+i]==1) // checks wall forward
                {
                    yPos+=i-1;
                    break;
                }
                else if((maze->getMazeArray()[xPos-1][yPos+i] == 0 || maze->getMazeArray()[xPos+1][yPos+i] == 0) && (ranDecision == 1 || ranDecision == 2)) //checks path from sides
                {
                    yPos+=i;
                    break;
                }
                else if(maze->getMazeArray()[xPos][yPos+i]==2) // checks player forward
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
                if(maze->getMazeArray()[xPos-i][yPos]==1) // checks wall forwards
                {
                    xPos-=i-1;
                    break;
                }
                else if((maze->getMazeArray()[xPos-i][yPos+1] == 0 || maze->getMazeArray()[xPos-i][yPos-1] == 0) && (ranDecision == 1 || ranDecision == 2)) //checks path from sides
                {
                    xPos-=i;
                    break;
                }
                else if(maze->getMazeArray()[xPos-i][yPos]==2) // checks player forward
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
                if(maze->getMazeArray()[xPos+i][yPos]==1) // checks wall forwards
                {
                    xPos+=i-1;
                    break;
                }else if((maze->getMazeArray()[xPos+i][yPos+1] == 0 || maze->getMazeArray()[xPos+i][yPos-1] == 0) && (ranDecision == 1 || ranDecision == 2)) //checks path from sides
                {
                    xPos+=i-1;
                    break;
                }
                else if(maze->getMazeArray()[xPos+i][yPos]==2) // checks player forward
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
                if(maze->getMazeArray()[xPos][yPos-i]==1) // checks wall forward
                {
                    yPos-=i-1;
                    break;
                }else if((maze->getMazeArray()[xPos-1][yPos-i] == 0 || maze->getMazeArray()[xPos+1][yPos-i] == 0) && (ranDecision == 1 || ranDecision == 2)) //checks path from sides
                {
                    yPos-=i-1;
                    break;
                }
                else if(maze->getMazeArray()[xPos][yPos-i]==2) // checks player forward
                {
                    yPos+=i-1;
                    break;
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

    mysql_real_connect(connection, "server1.jesseprescott.co.uk", "jessepre", "Mazeraider123?", "jessepre_mazeraider", 0, NULL, 0);
    if(!connection)
    {
        cout << "Failed to connect to the database." << endl;
        exit(0);
    }

    string query = "SELECT e.name, e.mesh, e.health, e.armour, e.attack_power, w.weapon_name, w.weapon_power, e.heal_power, w.attack_type,"
    " w.attack_colour, e.defence_type, e.defence_colour, e.heal_type, e.heal_colour "
    "FROM Enemy e, Weapon w WHERE e.weapon_id = w.weapon_id "
    "ORDER BY RAND() LIMIT 1;";

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
    defenceColour = atoi(row[1]);
    healType = atoi(row[12]);
    healColour = atoi(row[13]);
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
