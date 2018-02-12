#include <math.h>
#include "BattleScene.h"
#include "UI.h"
#include "LevelManager.h"

BattleScene::BattleScene(LevelManager* lvlman)
{
    lvlManager = lvlman;

    lvlman->ui->inBattle = true;
    TPlayerFEnemy =  true;
}

int BattleScene::BuildScene()
{
    int sceneWidth = 100;
    int sceneHeight = 15;
    int playerCounter = 0;
    int enemyCounter = 0;
    int playerWidth = 16;
    int enemyWidth = 35;

    // Health to draw - 20 is the maximum character for health
    int pHealth = (int)round((playerHealth * 20) / playerMaxHealth);
    int eHealth = (int)round((enemyHealth * 20) / enemyMaxHealth);

    if (playerHealth <= 0)
    {
        lvlManager->ui->inBattle = false;
        return 1;
    }
    else if (enemyHealth <= 0)
    {
        lvlManager->ui->inBattle = false;
        return 2;
    }
    else
    {
        // Print battle scene
        for (int h = 0; h < sceneHeight; h++)
        {
            for (int w = 0; w < sceneWidth; w++)
            {
// Top left corner battle scene, and healths
                if ((h == 0 && w == 0)  || (h == 2 && w == 4) || (h == 10 && w == 67))
                {
                    cout << (char)218;
                }

// Top right corner
                else if ((h == 0 && w == sceneWidth - 1) || (h == 2 && w == 26) || (h == 10 && w == 89))
                {
                    cout << (char)191;
                }

// Bottom left corner
                else if ((h == sceneHeight - 1 && w == 0) || (h == 4 && w == 4) || (h == 12 && w == 67))
                {
                    cout << (char)192;
                }

// Bottom right corner
                else if ((h == sceneHeight - 1 && w == sceneWidth - 1) || (h == 4 && w == 26) || (h == 12 && w == 89))
                {
                    cout << (char)217;
                }

// Top and bottom lines
                else if (h == 0 || h == sceneHeight - 1)
                {
                    cout << (char)196;
                }

// Left and right lines
                else if (w == 0 || w == sceneWidth - 1)
                {
                    cout << (char)179;
                }

// Player Health bar
                else if (w >= 5 && w <= (pHealth + 5) && h == 3)
                {
                    lvlManager->ui->PrintC("#", HealthColor(pHealth));
                }

// Enemy Health bar
                else if (w >= 68 && w <= (eHealth + 68) && h == 11)
                {
                    lvlManager->ui->PrintC("#", HealthColor(eHealth));
                }

// Player Health values
                else if (w == 5 && h == 5)
                {
                    string pValue = to_string(playerHealth) + "/" + to_string(playerMaxHealth);
                    lvlManager->ui->PrintC(to_string(playerHealth), HealthColor(pHealth, false));
                    lvlManager->ui->PrintC("/" + to_string(playerMaxHealth));
                    w += pValue.size() - 1;
                }

// Enemy Health values
                else if (w == 68 && h == 13)
                {
                    string eValue = to_string(enemyHealth) + "/" + to_string(enemyMaxHealth);
                    lvlManager->ui->PrintC(to_string(enemyHealth), HealthColor(eHealth, false));
                    lvlManager->ui->PrintC("/" + to_string(enemyMaxHealth));
                    w += eValue.size() - 1;
                }

// Place to draw player
                else if (h >= (sceneHeight / 2) - 1 && h < sceneHeight && w > 5 && w <= (playerWidth + 5))
                {
                    if (playerCounter < playerMesh[1].size())
                    {
                        cout << playerMesh[1][playerCounter];
                        playerCounter++;
                        w += 15;
                    }
                }

// Place to draw enemy
                else if (h > 0 && h <= sceneHeight / 2 && w >= sceneWidth - (enemyWidth + 5) && w < sceneWidth - 5)
                {
                    if (enemyCounter < enemyMesh[0].size())
                    {
                        cout << enemyMesh[0][enemyCounter];
                        enemyCounter++;
                        w += 34;
                    }
                }

// Empty space
                else
                    cout << (char)32;
            }
            cout << endl;
        }
    }

    if (!TPlayerFEnemy)
        EnemyAttack(0, 10, 10, 10);

    return 0;
}

int BattleScene::HealthColor(int health, bool TBackFFront)
{
    if(TBackFFront)
    {
        if (health > 10)
            return 34;
        else if (health > 5)
            return 238;
        else
            return 68;
    }
    else
    {
        if (health > 10)
            return 7;
        else if (health > 5)
            return 14;
        else
            return 4;
    }
}

void BattleScene::PlayAttack(int attackNr, int attackColor, int animSpeed)
{
    #ifdef _WIN32
        HANDLE hStdOut = GetStdHandle( STD_OUTPUT_HANDLE );
        CONSOLE_SCREEN_BUFFER_INFO cbsi;
        GetConsoleScreenBufferInfo(hStdOut, &cbsi);
        COORD originalPos = cbsi.dwCursorPosition;
    #endif // _WIN32

    #ifdef __linux__
        cout << "\033[s";
    #endif // __linux__

    switch (attackNr)
    {
        case 0:
            if (TPlayerFEnemy)
            {
                int xPos = 22;
                int yPos = 12;

                for (int i = 0; i <= 38; i++)
                {
                    cursorPosition( hStdOut, xPos, yPos ); // Main
                    lvlManager->ui->PrintC(mazeWall, attackColor);
                    cursorPosition( hStdOut, xPos + 1, yPos ); // Front
                    lvlManager->ui->PrintC(mazeWall, attackColor);
                    cursorPosition( hStdOut, xPos - 1, yPos ); // Back
                    lvlManager->ui->PrintC(mazeWall, attackColor);
                    cursorPosition( hStdOut, xPos, yPos + 1 ); // Bottom
                    lvlManager->ui->PrintC(attackBottom, attackColor);
                    cursorPosition( hStdOut, xPos + 1, yPos + 1 ); // Bottom Front
                    lvlManager->ui->PrintC(attackBottom, attackColor);

                    Sleep(animSpeed);

                    cursorPosition( hStdOut, xPos, yPos ); // Main
                    lvlManager->ui->PrintC(mazePath);
                    cursorPosition( hStdOut, xPos + 1, yPos ); // Front
                    lvlManager->ui->PrintC(mazePath);
                    cursorPosition( hStdOut, xPos - 1, yPos ); // Back
                    lvlManager->ui->PrintC(mazePath);
                    cursorPosition( hStdOut, xPos, yPos + 1 ); // Bottom
                    lvlManager->ui->PrintC(mazePath);
                    cursorPosition( hStdOut, xPos + 1, yPos + 1 ); // Bottom Front
                    lvlManager->ui->PrintC(mazePath);

                    xPos++;
                    if (i % 7 == 0)
                        yPos--;
                }
            }
            else
            {
                int xPos = 60;
                int yPos = 7;

                for (int i = 38; i >= 0; i--)
                {
                    cursorPosition( hStdOut, xPos, yPos ); // Main
                    lvlManager->ui->PrintC(mazeWall, attackColor);
                    cursorPosition( hStdOut, xPos, yPos - 1 ); // Top
                    lvlManager->ui->PrintC(attackTop, attackColor);
                    cursorPosition( hStdOut, xPos - 1, yPos - 1 ); // Top Front
                    lvlManager->ui->PrintC(attackTop, attackColor);
                    cursorPosition( hStdOut, xPos - 1, yPos ); // Front
                    lvlManager->ui->PrintC(mazeWall, attackColor);
                    cursorPosition( hStdOut, xPos + 1, yPos ); // Back
                    lvlManager->ui->PrintC(mazeWall, attackColor);

                    Sleep(animSpeed);

                    cursorPosition( hStdOut, xPos, yPos ); // Main
                    lvlManager->ui->PrintC(mazePath);
                    cursorPosition( hStdOut, xPos, yPos - 1 ); // Bottom
                    lvlManager->ui->PrintC(mazePath);
                    cursorPosition( hStdOut, xPos - 1, yPos - 1 ); // Bottom Front
                    lvlManager->ui->PrintC(mazePath);
                    cursorPosition( hStdOut, xPos - 1, yPos ); // Front
                    lvlManager->ui->PrintC(mazePath);
                    cursorPosition( hStdOut, xPos + 1, yPos ); // Back
                    lvlManager->ui->PrintC(mazePath);

                    xPos--;
                    if (i % 7 == 0)
                        yPos++;
                }
            }
            break;
        case 1:
            if (TPlayerFEnemy)
            {
                int xPos = 22;
                int yPos = 12;

                for (int i = 0; i <= 38; i++)
                {
                    cursorPosition( hStdOut, xPos, yPos ); // Main Middle
                    lvlManager->ui->PrintC(mazeWall, attackColor);
                    cursorPosition( hStdOut, xPos + 2, yPos - 1 ); // Front Middle
                    lvlManager->ui->PrintC(mazeWall, attackColor);
                    cursorPosition( hStdOut, xPos - 2, yPos + 1 ); // Back Middle
                    lvlManager->ui->PrintC(mazeWall, attackColor);
                    cursorPosition( hStdOut, xPos, yPos - 2 ); // Main Top
                    lvlManager->ui->PrintC(mazeWall, attackColor);
                    cursorPosition( hStdOut, xPos + 2, yPos - 3 ); // Front Top
                    lvlManager->ui->PrintC(mazeWall, attackColor);
                    cursorPosition( hStdOut, xPos - 2, yPos - 1 ); // Back Top
                    lvlManager->ui->PrintC(mazeWall, attackColor);
                    cursorPosition( hStdOut, xPos, yPos + 2 ); // Main Bottom
                    lvlManager->ui->PrintC(mazeWall, attackColor);
                    cursorPosition( hStdOut, xPos + 2, yPos + 1 ); // Front Bottom
                    lvlManager->ui->PrintC(mazeWall, attackColor);
                    cursorPosition( hStdOut, xPos - 2, yPos + 3 ); // Back Bottom
                    lvlManager->ui->PrintC(mazeWall, attackColor);

                    Sleep(animSpeed);

                    cursorPosition( hStdOut, xPos, yPos ); // Main Middle
                    lvlManager->ui->PrintC(mazePath);
                    cursorPosition( hStdOut, xPos + 2, yPos - 1 ); // Front Middle
                    lvlManager->ui->PrintC(mazePath);
                    cursorPosition( hStdOut, xPos - 2, yPos + 1 ); // Back Middle
                    lvlManager->ui->PrintC(mazePath);
                    cursorPosition( hStdOut, xPos, yPos - 2 ); // Main Top
                    lvlManager->ui->PrintC(mazePath);
                    cursorPosition( hStdOut, xPos + 2, yPos - 3 ); // Front Top
                    lvlManager->ui->PrintC(mazePath);
                    cursorPosition( hStdOut, xPos - 2, yPos - 1 ); // Back Top
                    lvlManager->ui->PrintC(mazePath);
                    cursorPosition( hStdOut, xPos, yPos + 2); // Main Bottom
                    lvlManager->ui->PrintC(mazePath);
                    cursorPosition( hStdOut, xPos + 2, yPos + 1 ); // Front Bottom
                    lvlManager->ui->PrintC(mazePath);
                    cursorPosition( hStdOut, xPos - 2, yPos + 3 ); // Back Bottom
                    lvlManager->ui->PrintC(mazePath);

                    xPos++;
                    if (i % 7 == 0)
                        yPos--;
                }
            }
            else
            {
                int xPos = 60;
                int yPos = 7;

                for (int i = 38; i >= 0; i--)
                {
                    cursorPosition( hStdOut, xPos, yPos ); // Main Middle
                    lvlManager->ui->PrintC(mazeWall, attackColor);
                    cursorPosition( hStdOut, xPos - 2, yPos + 1 ); // Front Middle
                    lvlManager->ui->PrintC(mazeWall, attackColor);
                    cursorPosition( hStdOut, xPos + 2, yPos - 1 ); // Back Middle
                    lvlManager->ui->PrintC(mazeWall, attackColor);
                    cursorPosition( hStdOut, xPos, yPos - 2 ); // Main Top
                    lvlManager->ui->PrintC(mazeWall, attackColor);
                    cursorPosition( hStdOut, xPos - 2, yPos - 1 ); // Front Top
                    lvlManager->ui->PrintC(mazeWall, attackColor);
                    cursorPosition( hStdOut, xPos + 2, yPos - 3 ); // Back Top
                    lvlManager->ui->PrintC(mazeWall, attackColor);
                    cursorPosition( hStdOut, xPos, yPos + 2 ); // Main Bottom
                    lvlManager->ui->PrintC(mazeWall, attackColor);
                    cursorPosition( hStdOut, xPos - 2, yPos + 3 ); // Front Bottom
                    lvlManager->ui->PrintC(mazeWall, attackColor);
                    cursorPosition( hStdOut, xPos + 2, yPos + 1 ); // Back Bottom
                    lvlManager->ui->PrintC(mazeWall, attackColor);

                    Sleep(animSpeed);

                    cursorPosition( hStdOut, xPos, yPos ); // Main Middle
                    lvlManager->ui->PrintC(mazePath);
                    cursorPosition( hStdOut, xPos - 2, yPos + 1 ); // Front Middle
                    lvlManager->ui->PrintC(mazePath);
                    cursorPosition( hStdOut, xPos + 2, yPos - 1 ); // Back Middle
                    lvlManager->ui->PrintC(mazePath);
                    cursorPosition( hStdOut, xPos, yPos - 2 ); // Main Top
                    lvlManager->ui->PrintC(mazePath);
                    cursorPosition( hStdOut, xPos - 2, yPos - 1 ); // Front Top
                    lvlManager->ui->PrintC(mazePath);
                    cursorPosition( hStdOut, xPos + 2, yPos - 3 ); // Back Top
                    lvlManager->ui->PrintC(mazePath);
                    cursorPosition( hStdOut, xPos, yPos + 2 ); // Main Bottom
                    lvlManager->ui->PrintC(mazePath);
                    cursorPosition( hStdOut, xPos - 2, yPos + 3 ); // Front Bottom
                    lvlManager->ui->PrintC(mazePath);
                    cursorPosition( hStdOut, xPos + 2, yPos + 1 ); // Back Bottom
                    lvlManager->ui->PrintC(mazePath);

                    xPos--;
                    if (i % 7 == 0)
                        yPos++;
                }
            }
            break;
    }


    #ifdef _WIN32
        SetConsoleCursorPosition( hStdOut, originalPos );
    #endif // _WIN32

    #ifdef __linux__
        cout << "\033[u";
    #endif // __linux__
}

void BattleScene::PlayDefend(int defendNr, int defendColor, int animSpeed)
{
    #ifdef _WIN32
        HANDLE hStdOut = GetStdHandle( STD_OUTPUT_HANDLE );
        CONSOLE_SCREEN_BUFFER_INFO cbsi;
        GetConsoleScreenBufferInfo(hStdOut, &cbsi);
        COORD originalPos = cbsi.dwCursorPosition;
    #endif // _WIN32

    #ifdef __linux__
        cout << "\033[s";
    #endif // __linux__

    switch (defendNr)
    {
        case 0:
            if (TPlayerFEnemy)
            {
                int xPos = 23;
                int yPos = 14;

                for (int x = 4; x >= 0; x-=2)
                {
                    for (int y = 0; y < 7 - x; y++)
                    {
                        cursorPosition( hStdOut, xPos + x, yPos - y );
                        lvlManager->ui->PrintC(mazeWall, defendColor);
                        Sleep(animSpeed / 2);
                    }
                    Sleep(animSpeed);
                }
            }
            else
            {
                int xPos = 60;
                int yPos = 9;

                for (int x = 4; x >= 0; x-=2)
                {
                    for (int y = 0; y < 7 - x; y++)
                    {
                        cursorPosition( hStdOut, xPos - x, yPos - y );
                        lvlManager->ui->PrintC(mazeWall, defendColor);
                        Sleep(animSpeed / 2);
                    }
                    Sleep(animSpeed);
                }
            }
            break;
        case 1:
            if (TPlayerFEnemy)
            {
                int xPos = 22;
                int yPos = 10;

                for (int x = 0; x <= 4; x+=2)
                {
                    for (int y = 0; y < 1 + x; y++)
                    {
                        if (y % 2 == 0)
                            cursorPosition( hStdOut, xPos + x, yPos + y );
                        else
                            cursorPosition( hStdOut, xPos + x, yPos - y );

                        lvlManager->ui->PrintC(mazeWall, defendColor);
                        Sleep(animSpeed / 2);
                    }
                    Sleep(animSpeed);
                }
            }
            else
            {
                int xPos = 60;
                int yPos = 9;

                for (int x = 0; x <= 4; x+=2)
                {
                    for (int y = 0; y < 1 + x; y++)
                    {
                        if (y % 2 == 0)
                            cursorPosition( hStdOut, xPos - x, yPos - y );
                        else
                            cursorPosition( hStdOut, xPos - x, yPos + y );

                        lvlManager->ui->PrintC(mazeWall, defendColor);
                        Sleep(animSpeed / 2);
                    }
                    Sleep(animSpeed);
                }
            }
            break;
    }


    #ifdef _WIN32
        SetConsoleCursorPosition( hStdOut, originalPos );
    #endif // _WIN32

    #ifdef __linux__
        cout << "\033[u";
    #endif // __linux__
}

void BattleScene::PlayHeal(int healNr, int healColor, int animSpeed)
{
    #ifdef _WIN32
        HANDLE hStdOut = GetStdHandle( STD_OUTPUT_HANDLE );
        CONSOLE_SCREEN_BUFFER_INFO cbsi;
        GetConsoleScreenBufferInfo(hStdOut, &cbsi);
        COORD originalPos = cbsi.dwCursorPosition;
    #endif // _WIN32

    #ifdef __linux__
        cout << "\033[s";
    #endif // __linux__

    switch (healNr)
    {
        case 0:
            if (TPlayerFEnemy)
            {
                int xPos = 22;
                int yPos = 12;

                for (int i = 0; i <= 38; i++)
                {

                    /* HERE */

                    xPos++;
                    if (i % 7 == 0)
                        yPos--;
                }
            }
            else
            {
                int xPos = 60;
                int yPos = 7;

                for (int i = 38; i >= 0; i--)
                {
                    /* HERE */

                    xPos--;
                    if (i % 7 == 0)
                        yPos++;
                }
            }
            break;
        case 1:
            if (TPlayerFEnemy)
            {
                int xPos = 22;
                int yPos = 12;

                for (int i = 0; i <= 38; i++)
                {
                    /* HERE */

                    xPos++;
                    if (i % 7 == 0)
                        yPos--;
                }
            }
            else
            {
                int xPos = 60;
                int yPos = 7;

                for (int i = 38; i >= 0; i--)
                {
                    /* HERE */

                    xPos--;
                    if (i % 7 == 0)
                        yPos++;
                }
            }
            break;
    }


    #ifdef _WIN32
        SetConsoleCursorPosition( hStdOut, originalPos );
    #endif // _WIN32

    #ifdef __linux__
        cout << "\033[u";
    #endif // __linux__
}

void BattleScene::PlayerAttack(int num, int color, int power, int speed)
{
    PlayAttack(num, color, speed);
    enemyHealth -= power;
    TPlayerFEnemy = false;
}

void BattleScene::PlayerDefend(int num, int color, int speed)
{
    PlayDefend(num, color, speed);
    TPlayerFEnemy = false;
}

void BattleScene::PlayerHeal(int num, int color, int power, int speed)
{
    PlayAttack(num, color, speed);
    playerHealth += power;
    TPlayerFEnemy = false;
}

void BattleScene::EnemyAttack(int num, int color, int power, int speed)
{
    PlayAttack(num, color, speed);
    playerHealth -= power;
    TPlayerFEnemy = true;
}

void BattleScene::EnemyDefend(int num, int color, int speed)
{
    PlayDefend(num, color, speed);
    TPlayerFEnemy = true;
}

void BattleScene::EnemyHeal(int num, int color, int power, int speed)
{
    PlayAttack(num, color, speed);
    enemyHealth += power;
    TPlayerFEnemy = true;
}
