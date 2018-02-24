#include "Enemy.h"
#include "Maze.h"

Enemy::Enemy(Maze* m)
{
    maze = m;

    // Enemy stats
    health = 100;
    armor = 2;
    power = 10;
    healPower = 10;

    // Animation types
    attackColour = 10;
    attackType = 0;
    defenceColour = 10;
    defenceType = 0;
    healColour = 10;
    healType = 0;

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

// 0 = Up | 1 = Right | 1 = Down | 3 = Left
void Enemy::moveEnemy(int direction)
{

}

void Enemy::randomMoveEnemy()
{
    ranDecision = rand() % 2 + 1;
    if(ranDecision == 1) // random chance of moving
    {
        ranDecision = rand() % 3 + 1;
        eDirection = rand() % 4 + 1; //random direction to move
        ranVal = rand() % 20 + 1; //random steps
        if(eDirection == 1)
        {
            for(int i = 1;i < ranVal; i++)
            {
                if(maze->getMazeArray()[xPos][yPos+i]==1) // checks wall forward
                {
                    yPos+=i-1;
                    break;
                }else if((maze->getMazeArray()[xPos-1][yPos+i] == 0 || maze->getMazeArray()[xPos+1][yPos+i] == 0) && (ranDecision == 1 || ranDecision == 2)) //checks path from sides
                {
                    yPos+=i-1;
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
                }else if((maze->getMazeArray()[xPos-i][yPos+1] == 0 || maze->getMazeArray()[xPos-i][yPos-1] == 0) && (ranDecision == 1 || ranDecision == 2)) //checks path from sides
                {
                    xPos-=i-1;
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

void Enemy::checkPlayer(){};
//function runs when one of the enemies is next to a player
/*if((maze->getMazeArray()[xPos][yPos+1]==2) || (maze->getMazeArray()[xPos][yPos-1]==2) || (maze->getMazeArray()[xPos+1][yPos]==2) || (maze->getMazeArray()[xPos-1][yPos]==2))
{
    //run battle scene -
    //Andre, you can call the function that runs the battle scene here. Initiate battle scene or something

}*/

int Enemy::getHealth()
{
    return health;
}

int Enemy::getArmor()
{
    return armor;
}

int Enemy::getPower()
{
    return power;
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
