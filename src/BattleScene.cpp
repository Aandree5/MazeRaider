#include <math.h>
#include "BattleScene.h"
#include "UI.h"
#include "LevelManager.h"

BattleScene::BattleScene(LevelManager* lvlman)
{
    lvlManager = lvlman;

    lvlman->ui->inBattle = true;
    TPlayerFEnemy =  true;
    isPlayerDefending = false;
    isEnemyDefending = false;
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
                    lvlManager->ui->PrintC(mazeWall, HealthColor(pHealth));
                }

// Enemy Health bar
                else if (w >= 68 && w <= (eHealth + 68) && h == 11)
                {
                    lvlManager->ui->PrintC(mazeWall, HealthColor(eHealth));
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

// Draw player shield
                else if(w == 27 && h == 3 && isPlayerDefending)
                {
                    lvlManager->ui->PrintC(shield, 11);
                }

// Draw enemy shield
                else if(w == 66 && h == 11 && isEnemyDefending)
                {
                    lvlManager->ui->PrintC(shield, 11);
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

void BattleScene::UpdateHealth()
{
    HANDLE hStdOut = GetStdHandle( STD_OUTPUT_HANDLE );
    CONSOLE_SCREEN_BUFFER_INFO cbsi;
    GetConsoleScreenBufferInfo(hStdOut, &cbsi);
    COORD originalPos = cbsi.dwCursorPosition;

    vector<int> x = {5, 5, 68, 68};
    vector<int> y = {5, 7, 13, 15};

    // Health to draw - 20 is the maximum character for health
    int pHealth = (int)round((playerHealth * 20) / playerMaxHealth);
    int eHealth = (int)round((enemyHealth * 20) / enemyMaxHealth);

    for(int p = 0; p < x.size();p++)
    {
        if(p % 2 == 0)
        {
            for(int i = 0; i <=20;i++)
            {
                cursorPosition( hStdOut, x[p] + i, y[p] );
                if (i > pHealth)
                    lvlManager->ui->PrintC(mazePath);
                else
                    lvlManager->ui->PrintC(mazeWall, HealthColor(pHealth));
            }
        }
        else
        {
            for(int i = 0; i <=20;i++)
            {
                cursorPosition( hStdOut, x[p] + i, y[p] );
                lvlManager->ui->PrintC(mazePath);
            }

            cursorPosition( hStdOut, x[p], y[p] );
            lvlManager->ui->PrintC(to_string(playerHealth), HealthColor(pHealth, false));
            lvlManager->ui->PrintC("/" + to_string(playerMaxHealth));
        }
    }

    cursorPosition( hStdOut, originalPos.X, originalPos.Y );
}


void BattleScene::PlayAttack(int num, int color, int speed)
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

    switch (num)
    {
        case 0:
            if (TPlayerFEnemy)
            {
                int xPos = 22;
                int yPos = 12;

                for (int i = 0; i <= 38; i++)
                {
                    cursorPosition( hStdOut, xPos, yPos ); // Main
                    lvlManager->ui->PrintC(mazeWall, color);
                    cursorPosition( hStdOut, xPos + 1, yPos ); // Front
                    lvlManager->ui->PrintC(mazeWall, color);
                    cursorPosition( hStdOut, xPos - 1, yPos ); // Back
                    lvlManager->ui->PrintC(mazeWall, color);
                    cursorPosition( hStdOut, xPos, yPos + 1 ); // Bottom
                    lvlManager->ui->PrintC(attackBottom, color);
                    cursorPosition( hStdOut, xPos + 1, yPos + 1 ); // Bottom Front
                    lvlManager->ui->PrintC(attackBottom, color);

                    Sleep(speed);

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
                    lvlManager->ui->PrintC(mazeWall, color);
                    cursorPosition( hStdOut, xPos, yPos - 1 ); // Top
                    lvlManager->ui->PrintC(attackTop, color);
                    cursorPosition( hStdOut, xPos - 1, yPos - 1 ); // Top Front
                    lvlManager->ui->PrintC(attackTop, color);
                    cursorPosition( hStdOut, xPos - 1, yPos ); // Front
                    lvlManager->ui->PrintC(mazeWall, color);
                    cursorPosition( hStdOut, xPos + 1, yPos ); // Back
                    lvlManager->ui->PrintC(mazeWall, color);

                    Sleep(speed);

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
                    lvlManager->ui->PrintC(mazeWall, color);
                    cursorPosition( hStdOut, xPos + 2, yPos - 1 ); // Front Middle
                    lvlManager->ui->PrintC(mazeWall, color);
                    cursorPosition( hStdOut, xPos - 2, yPos + 1 ); // Back Middle
                    lvlManager->ui->PrintC(mazeWall, color);
                    cursorPosition( hStdOut, xPos, yPos - 2 ); // Main Top
                    lvlManager->ui->PrintC(mazeWall, color);
                    cursorPosition( hStdOut, xPos + 2, yPos - 3 ); // Front Top
                    lvlManager->ui->PrintC(mazeWall, color);
                    cursorPosition( hStdOut, xPos - 2, yPos - 1 ); // Back Top
                    lvlManager->ui->PrintC(mazeWall, color);
                    cursorPosition( hStdOut, xPos, yPos + 2 ); // Main Bottom
                    lvlManager->ui->PrintC(mazeWall, color);
                    cursorPosition( hStdOut, xPos + 2, yPos + 1 ); // Front Bottom
                    lvlManager->ui->PrintC(mazeWall, color);
                    cursorPosition( hStdOut, xPos - 2, yPos + 3 ); // Back Bottom
                    lvlManager->ui->PrintC(mazeWall, color);

                    Sleep(speed);

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
                    lvlManager->ui->PrintC(mazeWall, color);
                    cursorPosition( hStdOut, xPos - 2, yPos + 1 ); // Front Middle
                    lvlManager->ui->PrintC(mazeWall, color);
                    cursorPosition( hStdOut, xPos + 2, yPos - 1 ); // Back Middle
                    lvlManager->ui->PrintC(mazeWall, color);
                    cursorPosition( hStdOut, xPos, yPos - 2 ); // Main Top
                    lvlManager->ui->PrintC(mazeWall, color);
                    cursorPosition( hStdOut, xPos - 2, yPos - 1 ); // Front Top
                    lvlManager->ui->PrintC(mazeWall, color);
                    cursorPosition( hStdOut, xPos + 2, yPos - 3 ); // Back Top
                    lvlManager->ui->PrintC(mazeWall, color);
                    cursorPosition( hStdOut, xPos, yPos + 2 ); // Main Bottom
                    lvlManager->ui->PrintC(mazeWall, color);
                    cursorPosition( hStdOut, xPos - 2, yPos + 3 ); // Front Bottom
                    lvlManager->ui->PrintC(mazeWall, color);
                    cursorPosition( hStdOut, xPos + 2, yPos + 1 ); // Back Bottom
                    lvlManager->ui->PrintC(mazeWall, color);

                    Sleep(speed);

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

void BattleScene::PlayDefend(int num, int color, int speed)
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

    switch (num)
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
                        lvlManager->ui->PrintC(mazeWall, color);
                        Sleep(speed / 2);
                    }
                    Sleep(speed);
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
                        lvlManager->ui->PrintC(mazeWall, color);
                        Sleep(speed / 2);
                    }
                    Sleep(speed);
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

                        lvlManager->ui->PrintC(mazeWall, color);
                        Sleep(speed / 2);
                    }
                    Sleep(speed);
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

                        lvlManager->ui->PrintC(mazeWall, color);
                        Sleep(speed / 2);
                    }
                    Sleep(speed);
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

void BattleScene::PlayHeal(int num, int color, int speed)
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

    switch (num)
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
                        cursorPosition(hStdOut, xPos + x, yPos - y);
                        lvlManager->ui->PrintC(heal, color);
                        cursorPosition(hStdOut, xPos + 2 + x, yPos - y + 1);
                        lvlManager->ui->PrintC(heal, color);
                        Sleep(speed / 2);
                    }

                    Sleep(speed);

                    for (int y = 0; y < 7 - x; y++)
                    {
                        cursorPosition(hStdOut, xPos + x, yPos - y);
                        lvlManager->ui->PrintC(mazePath);
                        cursorPosition(hStdOut, xPos + 2 + x, yPos - y + 1);
                        lvlManager->ui->PrintC(mazePath);
                        Sleep(speed / 2);
                    }
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
                        cursorPosition(hStdOut, xPos - x, yPos - y);
                        lvlManager->ui->PrintC(heal, color);
                        cursorPosition(hStdOut, xPos - 2 - x, yPos - y + 1);
                        lvlManager->ui->PrintC(heal, color);
                        Sleep(speed / 2);
                    }

                    Sleep(speed);

                    for (int y = 0; y < 7 - x; y++)
                    {
                        cursorPosition(hStdOut, xPos - x, yPos - y);
                        lvlManager->ui->PrintC(mazePath);
                        cursorPosition(hStdOut, xPos - 2 - x, yPos - y + 1);
                        lvlManager->ui->PrintC(mazePath);
                        Sleep(speed / 2);
                    }
                }
            }
            break;
        case 1:
            if (TPlayerFEnemy)
            {
                int xPos = 22;
                int yPos = 12;

                for (int x = 4; x >= 0; x-=2)
                {
                    for (int y = 0; y < 3; y++)
                    {
                        cursorPosition(hStdOut, xPos + x, yPos - y - 1);
                        lvlManager->ui->PrintC(heal, color);
                        cursorPosition(hStdOut, xPos - 2 + x, yPos - y );
                        lvlManager->ui->PrintC(heal, color);
                        cursorPosition(hStdOut, xPos + 2 + x, yPos - y + 1);
                        lvlManager->ui->PrintC(heal, color);

                        Sleep(speed);

                        cursorPosition(hStdOut, xPos + x, yPos - y - 1);
                        lvlManager->ui->PrintC(heal);
                        cursorPosition(hStdOut, xPos - 2 + x, yPos - y );
                        lvlManager->ui->PrintC(heal);
                        cursorPosition(hStdOut, xPos + 2 + x, yPos - y + 1);
                        lvlManager->ui->PrintC(heal);
                    }
                }
            }
            else
            {
                int xPos = 59;
                int yPos = 7;

                for (int x = 4; x >= 0; x-=2)
                {
                    for (int y = 0; y < 3; y++)
                    {
                        cursorPosition(hStdOut, xPos - x, yPos - y - 1);
                        lvlManager->ui->PrintC(heal, color);
                        cursorPosition(hStdOut, xPos - 2 - x, yPos - y );
                        lvlManager->ui->PrintC(heal, color);
                        cursorPosition(hStdOut, xPos + 2 - x, yPos - y + 1);
                        lvlManager->ui->PrintC(heal, color);

                        Sleep(speed);

                        cursorPosition(hStdOut, xPos - x, yPos - y - 1);
                        lvlManager->ui->PrintC(mazePath);
                        cursorPosition(hStdOut, xPos - 2 - x, yPos - y );
                        lvlManager->ui->PrintC(mazePath);
                        cursorPosition(hStdOut, xPos + 2 - x, yPos - y + 1);
                        lvlManager->ui->PrintC(mazePath);
                    }
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
    if (!isEnemyDefending)
        enemyHealth -= power;
    TPlayerFEnemy = false;
    UpdateHealth();
}

void BattleScene::PlayerDefend(int num, int color, int speed)
{
    PlayDefend(num, color, speed);
    isPlayerDefending = true;
    TPlayerFEnemy = false;
    UpdateHealth();
}

void BattleScene::PlayerHeal(int num, int color, int power, int speed)
{
    PlayHeal(num, color, speed);
    if (playerHealth + power <= playerMaxHealth)
        playerHealth += power;
    else
        playerHealth = playerMaxHealth;
    TPlayerFEnemy = false;
    UpdateHealth();
}


void BattleScene::EnemyAttack(int num, int color, int power, int speed)
{
    PlayAttack(num, color, speed);
    if (!isPlayerDefending)
        playerHealth -= power;
    else
        isPlayerDefending = false;

    TPlayerFEnemy = true;
    UpdateHealth();
}

void BattleScene::EnemyDefend(int num, int color, int speed)
{
    PlayDefend(num, color, speed);
    isPlayerDefending = false;
    TPlayerFEnemy = true;
    UpdateHealth();
}

void BattleScene::EnemyHeal(int num, int color, int power, int speed)
{
    PlayAttack(num, color, speed);
    if (enemyHealth + power <= enemyMaxHealth)
        enemyHealth += power;
    else
        enemyHealth = enemyMaxHealth;
    isPlayerDefending = false;
    TPlayerFEnemy = true;
    UpdateHealth();
}
