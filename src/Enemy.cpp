#include "Enemy.h"

/*Enemy::Enemy()
{
}
*/
void Enemy::moveEnemy(void)
{
    ranDecision = rand() % 5 + 1;
    if(ranDecision == 1) // random chance of moving
    {
        eDirection = rand() % 4 + 1; //random direction to move
        ranVal = rand() % 20 + 1; //random steps
        if(eDirection == 1)
        {
            for(int i = 1;i < ranVal; i++)
            {
                if(maze->getMazeArray()[xPosEnemy][yPosEnemy+i]==1) // checks wall forward
                {
                    yPosEnemy+=i-1;
                    break;
                }else if((maze->getMazeArray()[xPosEnemy-1][yPosEnemy+i] == 0 || maze->getMazeArray()[xPosEnemy+1][yPosEnemy+i] == 0) && (ranDecision == 1 || ranDecision == 2)) //checks path from sides
                {
                    yPosEnemy+=i-1;
                    break;
                }
            }
        }
        else if(eDirection == 2)
        {
            for(int i = 1;i < ranVal; i++)
            {
                if(maze->getMazeArray()[xPosEnemy-i][yPosEnemy]==1) // checks wall forwards
                {
                    xPosEnemy-=i-1;
                    break;
                }else if((maze->getMazeArray()[xPosEnemy-i][yPosEnemy+1] == 0 || maze->getMazeArray()[xPosEnemy-i][yPosEnemy-1] == 0) && (ranDecision == 1 || ranDecision == 2)) //checks path from sides
                {
                    xPosEnemy-=i-1;
                    break;
                }
            }
        }
        else if(eDirection == 3)
        {
            for(int i = 1;i < ranVal; i++)
            {
                if(maze->getMazeArray()[xPosEnemy+i][yPosEnemy]==1) // checks wall forwards
                {
                    xPosEnemy+=i-1;
                    break;
                }else if((maze->getMazeArray()[xPosEnemy+i][yPosEnemy+1] == 0 || maze->getMazeArray()[xPosEnemy+i][yPosEnemy-1] == 0) && (ranDecision == 1 || ranDecision == 2)) //checks path from sides
                {
                    xPosEnemy+=i-1;
                    break;
                }
            }
        }
        else if(eDirection == 4)
        {
            for(int i = 1;i < ranVal; i++)
            {
                if(maze->getMazeArray()[xPosEnemy][yPosEnemy-i]==1) // checks wall forward
                {
                    yPosEnemy-=i-1;
                    break;
                }else if((maze->getMazeArray()[xPosEnemy-1][yPosEnemy-i] == 0 || maze->getMazeArray()[xPosEnemy+1][yPosEnemy-i] == 0) && (ranDecision == 1 || ranDecision == 2)) //checks path from sides
                {
                    yPosEnemy-=i-1;
                    break;
                }
            }
        }
    }
}
