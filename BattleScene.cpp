#include <math.h>
#include <algorithm>
#include "BattleScene.h"
#include "UIHelpers.h"
#include "UI.h"
#include "LevelManager.h"
#include "Enemy.h"
#include "Player.h"

using namespace UIHelpers;

BattleScene::BattleScene(LevelManager* lvlman, Enemy* e)
{
    lvlManager = lvlman;
    enemy = e;

    playerHealth = lvlManager->player->pHealth;
    playerMaxHealth = playerHealth;
    enemyHealth = enemy->getHealth();
    enemyMaxHealth = enemyHealth;

    lvlman->ui->inBattle = true;
    TPlayerFEnemy =  true;
    isPlayerDefending = false;
    isEnemyDefending = false;
    enemyJustAttacked = false;

    battleInfo[battleInfo.size() - 1] = make_pair(enemy->getName() + " encountered.", 0);
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

    // Reset enemy just attacked variable to continue to user turn
    enemyJustAttacked = false;

    if (playerHealth <= 0)
    {
        lvlManager->ui->inBattle = false;
        return 1;
    }
    else if (eHealth <= 0)
    {
        lvlManager->ui->inBattle = false;

        // Delete enemy from vector
        auto it = find(lvlManager->enemies.begin(), lvlManager->enemies.end(), enemy);
        if (it != lvlManager->enemies.end())
            lvlManager->enemies.erase(it);

        // Delete enemy from memory
        delete enemy;
        enemy = nullptr;
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
                    PrintC(bsTopLeftCorner);
                }

// Top right corner
                else if ((h == 0 && w == sceneWidth - 1) || (h == 2 && w == 26) || (h == 10 && w == 89))
                {
                    PrintC(bsTopRightCorner);
                }

// Bottom left corner
                else if ((h == sceneHeight - 1 && w == 0) || (h == 4 && w == 4) || (h == 12 && w == 67))
                {
                    PrintC(bsBottomLeftCorner);
                }

// Bottom right corner
                else if ((h == sceneHeight - 1 && w == sceneWidth - 1) || (h == 4 && w == 26) || (h == 12 && w == 89))
                {
                    PrintC(bsBottomRightCorner);
                }

// Top and bottom lines
                else if (h == 0 || h == sceneHeight - 1)
                {
                    PrintC(bsTopBottomLines);
                }

// Left and right lines and battle info lines
                else if (w == 0 || w == sceneWidth - 1)
                {
                    PrintC(bsLeftRightLines);

                    if (w == sceneWidth - 1 && h > 0 && h <= sceneHeight + 3 && battleInfo[h - 1].first != "")
                    {
                        if(h == 13)
                        {
                            PrintC(" ");
                            PrintC(bsLeftRightLines, 15);
                            PrintC(" ");
                            switch (battleInfo[h - 1].second)
                            {
                            case 0:
                                PrintC(battleInfo[h - 1].first, 15);
                                break;
                            case 1:
                                PrintC(battleInfo[h - 1].first, 12);
                                break;
                            case 2:
                                PrintC(battleInfo[h - 1].first, 11);
                                break;
                            case 3:
                                PrintC(battleInfo[h - 1].first, 10);
                                break;
                            default:
                                PrintC(battleInfo[h - 1].first, 15);
                                break;
                            }
                        }
                        else
                        {
                            PrintC(" ");
                            PrintC(bsLeftRightLines, 8);
                            PrintC(" ");
                            switch (battleInfo[h - 1].second)
                            {
                            case 0:
                                PrintC(battleInfo[h - 1].first, 8);
                                break;
                            case 1:
                                PrintC(battleInfo[h - 1].first, 4);
                                break;
                            case 2:
                                PrintC(battleInfo[h - 1].first, 3);
                                break;
                            case 3:
                                PrintC(battleInfo[h - 1].first, 2);
                                break;
                            default:
                                PrintC(battleInfo[h - 1].first, 8);
                                break;
                            }
                        }
                    }
                }

// Player name
                else if (w == 5 && h == 1)
                {
                    string name = lvlManager->player->pName;
                    PrintC(name, lvlManager->player->pAttackColour);

                    w += name.size() - 1;
                }

// Enemy name
                else if (w == 68 && h == 9)
                {
                    string name = enemy->getName();
                    PrintC(name, enemy->getAttackColour());

                    w += name.size() - 1;
                }

// Player Health bar
                else if (w >= 5 && w <= (pHealth + 5) && h == 3)
                {
                    PrintC(mazeWall, HealthColor(pHealth));
                }

// Enemy Health bar
                else if (w >= 68 && w <= (eHealth + 68) && h == 11)
                {
                    PrintC(mazeWall, HealthColor(eHealth));
                }

// Player Health values
                else if (w == 5 && h == 5)
                {
                    string pValue = to_string(playerHealth) + "/" + to_string(playerMaxHealth);
                    PrintC(to_string(playerHealth), HealthColor(pHealth, false));
                    PrintC("/" + to_string(playerMaxHealth));
                    w += pValue.size() - 1;
                }

// Enemy Health values
                else if (w == 68 && h == 13)
                {
                    string eValue = to_string(enemyHealth) + "/" + to_string(enemyMaxHealth);
                    PrintC(to_string(enemyHealth), HealthColor(eHealth, false));
                    PrintC("/" + to_string(enemyMaxHealth));
                    w += eValue.size() - 1;
                }

// Draw player shield
                else if(w == 27 && h == 3 && isPlayerDefending)
                {
                    PrintC(shieldSymbol, 11);
                }

// Draw enemy shield
                else if(w == 66 && h == 11 && isEnemyDefending)
                {
                    PrintC(shieldSymbol, 11);
                }

// Draw player
                else if (h >= (sceneHeight / 2) - 1 && h < sceneHeight && w > 5 && w <= (playerWidth + 5))
                {
                    if (h - ((sceneHeight / 2) - 1) < lvlManager->ui->playerMesh[lvlManager->player->pMesh].size())
                    {
                        cout << lvlManager->ui->playerMesh[lvlManager->player->pMesh][h - ((sceneHeight / 2) - 1)];
                        playerCounter++;
                        w += playerWidth - 1;
                    }
                }

// Draw enemy
                else if (h > 0 && h <= sceneHeight / 2 && w >= sceneWidth - (enemyWidth + 5) && w < sceneWidth - 5)
                {
                    if (h - 1 < lvlManager->ui->enemyMesh[enemy->getMesh()].size())
                    {
                        cout << lvlManager->ui->enemyMesh[enemy->getMesh()][h - 1];
                        enemyCounter++;
                        w += enemyWidth - 1;
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
        EnemyAction();

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

// Add line to battleInfo - Text to show and type action | 0 = attack   1 = defend    2 = heal
void BattleScene::UpdateBattleInfo(string text, int type)
{
    bool needReplace = true;

    for(int i = 0; i < battleInfo.size(); i++)
    {
        if( i + 1 < battleInfo.size())
            battleInfo[i] = battleInfo[i + 1];
        else
            battleInfo[i] = make_pair(text, type);
    }
}


void BattleScene::PlayAttack(int atype, int colour)
{
    #ifdef _WIN32
        HANDLE hStdOut = GetStdHandle( STD_OUTPUT_HANDLE );
        CONSOLE_SCREEN_BUFFER_INFO cbsi;
        GetConsoleScreenBufferInfo(hStdOut, &cbsi);
        COORD originalPos = cbsi.dwCursorPosition;
    #endif // _WIN32

    #ifdef __linux__
        int hStdOut;
        cout << "\033[s";
    #endif // __linux__

    switch (atype)
    {
        case 0:
            if (TPlayerFEnemy)
            {
                int xPos = 22;
                int yPos = 12;

                for (int i = 0; i <= 38; i++)
                {
                    cursorPosition( hStdOut, xPos, yPos ); // Main
                    PrintC(mazeWall, colour);
                    cursorPosition( hStdOut, xPos + 1, yPos ); // Front
                    PrintC(mazeWall, colour);
                    cursorPosition( hStdOut, xPos - 1, yPos ); // Back
                    PrintC(mazeWall, colour);
                    cursorPosition( hStdOut, xPos, yPos + 1 ); // Bottom
                    PrintC(attackBottom, colour);
                    cursorPosition( hStdOut, xPos + 1, yPos + 1 ); // Bottom Front
                    PrintC(attackBottom, colour);

                    Sleep(attackAnimSpeed);

                    cursorPosition( hStdOut, xPos, yPos ); // Main
                    PrintC(mazePath);
                    cursorPosition( hStdOut, xPos + 1, yPos ); // Front
                    PrintC(mazePath);
                    cursorPosition( hStdOut, xPos - 1, yPos ); // Back
                    PrintC(mazePath);
                    cursorPosition( hStdOut, xPos, yPos + 1 ); // Bottom
                    PrintC(mazePath);
                    cursorPosition( hStdOut, xPos + 1, yPos + 1 ); // Bottom Front
                    PrintC(mazePath);

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
                    PrintC(mazeWall, colour);
                    cursorPosition( hStdOut, xPos, yPos - 1 ); // Top
                    PrintC(attackTop, colour);
                    cursorPosition( hStdOut, xPos - 1, yPos - 1 ); // Top Front
                    PrintC(attackTop, colour);
                    cursorPosition( hStdOut, xPos - 1, yPos ); // Front
                    PrintC(mazeWall, colour);
                    cursorPosition( hStdOut, xPos + 1, yPos ); // Back
                    PrintC(mazeWall, colour);

                    Sleep(attackAnimSpeed);

                    cursorPosition( hStdOut, xPos, yPos ); // Main
                    PrintC(mazePath);
                    cursorPosition( hStdOut, xPos, yPos - 1 ); // Bottom
                    PrintC(mazePath);
                    cursorPosition( hStdOut, xPos - 1, yPos - 1 ); // Bottom Front
                    PrintC(mazePath);
                    cursorPosition( hStdOut, xPos - 1, yPos ); // Front
                    PrintC(mazePath);
                    cursorPosition( hStdOut, xPos + 1, yPos ); // Back
                    PrintC(mazePath);

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
                    PrintC(mazeWall, colour);
                    cursorPosition( hStdOut, xPos + 2, yPos - 1 ); // Front Middle
                    PrintC(mazeWall, colour);
                    cursorPosition( hStdOut, xPos - 2, yPos + 1 ); // Back Middle
                    PrintC(mazeWall, colour);
                    cursorPosition( hStdOut, xPos, yPos - 2 ); // Main Top
                    PrintC(mazeWall, colour);
                    cursorPosition( hStdOut, xPos + 2, yPos - 3 ); // Front Top
                    PrintC(mazeWall, colour);
                    cursorPosition( hStdOut, xPos - 2, yPos - 1 ); // Back Top
                    PrintC(mazeWall, colour);
                    cursorPosition( hStdOut, xPos, yPos + 2 ); // Main Bottom
                    PrintC(mazeWall, colour);
                    cursorPosition( hStdOut, xPos + 2, yPos + 1 ); // Front Bottom
                    PrintC(mazeWall, colour);
                    cursorPosition( hStdOut, xPos - 2, yPos + 3 ); // Back Bottom
                    PrintC(mazeWall, colour);

                    Sleep(attackAnimSpeed);

                    cursorPosition( hStdOut, xPos, yPos ); // Main Middle
                    PrintC(mazePath);
                    cursorPosition( hStdOut, xPos + 2, yPos - 1 ); // Front Middle
                    PrintC(mazePath);
                    cursorPosition( hStdOut, xPos - 2, yPos + 1 ); // Back Middle
                    PrintC(mazePath);
                    cursorPosition( hStdOut, xPos, yPos - 2 ); // Main Top
                    PrintC(mazePath);
                    cursorPosition( hStdOut, xPos + 2, yPos - 3 ); // Front Top
                    PrintC(mazePath);
                    cursorPosition( hStdOut, xPos - 2, yPos - 1 ); // Back Top
                    PrintC(mazePath);
                    cursorPosition( hStdOut, xPos, yPos + 2); // Main Bottom
                    PrintC(mazePath);
                    cursorPosition( hStdOut, xPos + 2, yPos + 1 ); // Front Bottom
                    PrintC(mazePath);
                    cursorPosition( hStdOut, xPos - 2, yPos + 3 ); // Back Bottom
                    PrintC(mazePath);

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
                    PrintC(mazeWall, colour);
                    cursorPosition( hStdOut, xPos - 2, yPos + 1 ); // Front Middle
                    PrintC(mazeWall, colour);
                    cursorPosition( hStdOut, xPos + 2, yPos - 1 ); // Back Middle
                    PrintC(mazeWall, colour);
                    cursorPosition( hStdOut, xPos, yPos - 2 ); // Main Top
                    PrintC(mazeWall, colour);
                    cursorPosition( hStdOut, xPos - 2, yPos - 1 ); // Front Top
                    PrintC(mazeWall, colour);
                    cursorPosition( hStdOut, xPos + 2, yPos - 3 ); // Back Top
                    PrintC(mazeWall, colour);
                    cursorPosition( hStdOut, xPos, yPos + 2 ); // Main Bottom
                    PrintC(mazeWall, colour);
                    cursorPosition( hStdOut, xPos - 2, yPos + 3 ); // Front Bottom
                    PrintC(mazeWall, colour);
                    cursorPosition( hStdOut, xPos + 2, yPos + 1 ); // Back Bottom
                    PrintC(mazeWall, colour);

                    Sleep(attackAnimSpeed);

                    cursorPosition( hStdOut, xPos, yPos ); // Main Middle
                    PrintC(mazePath);
                    cursorPosition( hStdOut, xPos - 2, yPos + 1 ); // Front Middle
                    PrintC(mazePath);
                    cursorPosition( hStdOut, xPos + 2, yPos - 1 ); // Back Middle
                    PrintC(mazePath);
                    cursorPosition( hStdOut, xPos, yPos - 2 ); // Main Top
                    PrintC(mazePath);
                    cursorPosition( hStdOut, xPos - 2, yPos - 1 ); // Front Top
                    PrintC(mazePath);
                    cursorPosition( hStdOut, xPos + 2, yPos - 3 ); // Back Top
                    PrintC(mazePath);
                    cursorPosition( hStdOut, xPos, yPos + 2 ); // Main Bottom
                    PrintC(mazePath);
                    cursorPosition( hStdOut, xPos - 2, yPos + 3 ); // Front Bottom
                    PrintC(mazePath);
                    cursorPosition( hStdOut, xPos + 2, yPos + 1 ); // Back Bottom
                    PrintC(mazePath);

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

void BattleScene::PlayDefend(int dtype, int colour)
{
    #ifdef _WIN32
        HANDLE hStdOut = GetStdHandle( STD_OUTPUT_HANDLE );
        CONSOLE_SCREEN_BUFFER_INFO cbsi;
        GetConsoleScreenBufferInfo(hStdOut, &cbsi);
        COORD originalPos = cbsi.dwCursorPosition;
    #endif // _WIN32

    #ifdef __linux__
        int hStdOut;
        cout << "\033[s";
    #endif // __linux__

    switch (dtype)
    {
        case 0:
            if (TPlayerFEnemy)
            {
                int xPos = 23;
                int yPos = 15;

                for (int x = 4; x >= 0; x-=2)
                {
                    for (int y = 0; y < 7 - x; y++)
                    {
                        cursorPosition( hStdOut, xPos + x, yPos - y );
                        PrintC(mazeWall, colour);
                        Sleep(defenceHealAnimSpeed / 2);
                    }
                    Sleep(defenceHealAnimSpeed);
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
                        PrintC(mazeWall, colour);
                        Sleep(defenceHealAnimSpeed / 2);
                    }
                    Sleep(defenceHealAnimSpeed);
                }
            }
            break;
        case 1:
            if (TPlayerFEnemy)
            {
                int xPos = 22;
                int yPos = 11;

                for (int x = 0; x <= 4; x+=2)
                {
                    for (int y = 0; y < 1 + x; y++)
                    {
                        if (y % 2 == 0)
                            cursorPosition(hStdOut, xPos + x, yPos + y);
                        else
                            cursorPosition(hStdOut, xPos + x, yPos - y - 1);

                        PrintC(mazeWall, colour);
                        Sleep(defenceHealAnimSpeed / 2);
                    }
                    Sleep(defenceHealAnimSpeed);
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

                        PrintC(mazeWall, colour);
                        Sleep(defenceHealAnimSpeed / 2);
                    }
                    Sleep(defenceHealAnimSpeed);
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

void BattleScene::PlayHeal(int htype, int colour)
{
    #ifdef _WIN32
        HANDLE hStdOut = GetStdHandle( STD_OUTPUT_HANDLE );
        CONSOLE_SCREEN_BUFFER_INFO cbsi;
        GetConsoleScreenBufferInfo(hStdOut, &cbsi);
        COORD originalPos = cbsi.dwCursorPosition;
    #endif // _WIN32

    #ifdef __linux__
        int hStdOut;
        cout << "\033[s";
    #endif // __linux__

    switch (htype)
    {
        case 0:
            if (TPlayerFEnemy)
            {
                int xPos = 23;
                int yPos = 14;

                for (int x = 4; x >= 0; x-=2)
                {
                    for (int y = 0; y < 6 - x; y++)
                    {
                        cursorPosition(hStdOut, xPos + x, yPos - y);
                        PrintC(healSymbol, colour);
                        cursorPosition(hStdOut, xPos + 2 + x, yPos - y + 1);
                        PrintC(healSymbol, colour);
                        Sleep(defenceHealAnimSpeed / 2);
                    }

                    Sleep(defenceHealAnimSpeed);

                    for (int y = 0; y < 6 - x; y++)
                    {
                        cursorPosition(hStdOut, xPos + x, yPos - y);
                        PrintC(mazePath);
                        cursorPosition(hStdOut, xPos + 2 + x, yPos - y + 1);
                        PrintC(mazePath);
                        Sleep(defenceHealAnimSpeed / 2);
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
                        PrintC(healSymbol, colour);
                        cursorPosition(hStdOut, xPos - 2 - x, yPos - y + 1);
                        PrintC(healSymbol, colour);
                        Sleep(defenceHealAnimSpeed / 2);
                    }

                    Sleep(defenceHealAnimSpeed);

                    for (int y = 0; y < 7 - x; y++)
                    {
                        cursorPosition(hStdOut, xPos - x, yPos - y);
                        PrintC(mazePath);
                        cursorPosition(hStdOut, xPos - 2 - x, yPos - y + 1);
                        PrintC(mazePath);
                        Sleep(defenceHealAnimSpeed / 2);
                    }
                }
            }
            break;
        case 1:
            if (TPlayerFEnemy)
            {
                int xPos = 23;
                int yPos = 14;

                for (int x = 4; x >= 0; x-=2)
                {
                    for (int y = 0; y < 5; y++)
                    {
                        cursorPosition(hStdOut, xPos + x, yPos - y - 1);
                        PrintC(healSymbol, colour);
                        cursorPosition(hStdOut, xPos - 2 + x, yPos - y );
                        PrintC(healSymbol, colour);
                        cursorPosition(hStdOut, xPos + 2 + x, yPos - y + 1);
                        PrintC(healSymbol, colour);

                        Sleep(defenceHealAnimSpeed);

                        cursorPosition(hStdOut, xPos + x, yPos - y - 1);
                        PrintC(mazePath);
                        cursorPosition(hStdOut, xPos - 2 + x, yPos - y );
                        PrintC(mazePath);
                        cursorPosition(hStdOut, xPos + 2 + x, yPos - y + 1);
                        PrintC(mazePath);
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
                        PrintC(healSymbol, colour);
                        cursorPosition(hStdOut, xPos - 2 - x, yPos - y );
                        PrintC(healSymbol, colour);
                        cursorPosition(hStdOut, xPos + 2 - x, yPos - y + 1);
                        PrintC(healSymbol, colour);

                        Sleep(defenceHealAnimSpeed);

                        cursorPosition(hStdOut, xPos - x, yPos - y - 1);
                        PrintC(mazePath);
                        cursorPosition(hStdOut, xPos - 2 - x, yPos - y );
                        PrintC(mazePath);
                        cursorPosition(hStdOut, xPos + 2 - x, yPos - y + 1);
                        PrintC(mazePath);
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


void BattleScene::PlayerAttack()
{
    int tempHealth = enemyHealth;

    PlayAttack(lvlManager->player->pAttackType, lvlManager->player->pAttackColour);

    if (!isEnemyDefending)
    {
        int damageToDeal = 0;

        if((lvlManager->player->pDamage + lvlManager->player->pWeapon.second) > enemy->getArmour())
            damageToDeal = (lvlManager->player->pDamage + lvlManager->player->pWeapon.second) - enemy->getArmour();


        if(enemyHealth - damageToDeal >= 0)
            enemyHealth -= damageToDeal;
        else
            enemyHealth = 0;
    }

    tempHealth = tempHealth - enemyHealth;
    UpdateBattleInfo(lvlManager->player->pName + " dealt " + to_string(tempHealth) + " damage", 1);

    isEnemyDefending = false;
    TPlayerFEnemy = false;
}

void BattleScene::PlayerDefend()
{
    PlayDefend(lvlManager->player->pDefenceType, lvlManager->player->pDefenceColour);

    UpdateBattleInfo(lvlManager->player->pName + " is defending", 2);

    isPlayerDefending = true;
    isEnemyDefending = false;
    TPlayerFEnemy = false;
}

void BattleScene::PlayerHeal()
{
    int tempHealth = playerHealth;

    PlayHeal(lvlManager->player->pHealType, lvlManager->player->pHealColour);

    if (playerHealth + lvlManager->player->pHealPower <= playerMaxHealth)
        playerHealth += lvlManager->player->pHealPower;
    else
        playerHealth = playerMaxHealth;

    tempHealth = playerHealth - tempHealth;
    UpdateBattleInfo(lvlManager->player->pName + " healed by " + to_string(tempHealth), 3);

    isEnemyDefending = false;
    TPlayerFEnemy = false;
}

bool BattleScene::canPlayerRun()
{
    // Change of letting the player run
    int changeLimit = 95; // 15%
    int chance = rand() % 101; // From 0 - 100 (0% - 100%)

    if(enemy->getAttackPower() > lvlManager->player->pDamage)
    {
        chance = rand() % 101 - (enemy->getAttackPower() - lvlManager->player->pDamage);
    }

    if (chance <= changeLimit)
    {
        UpdateBattleInfo(lvlManager->player->pName + " ran from battle.", 0);

        // Delete enemy from vector
        auto it = find(lvlManager->enemies.begin(), lvlManager->enemies.end(), enemy);
        if (it != lvlManager->enemies.end())
            lvlManager->enemies.erase(it);

        // Delete enemy from memory
        delete enemy;
        enemy = nullptr;

        lvlManager->enemies.emplace_back(new Enemy(lvlManager->maze));
        return true;
    }
    else
    {
        UpdateBattleInfo(enemy->getName() + " stopped " + lvlManager->player->pName + " from running.", 0);
        isEnemyDefending = false;
        TPlayerFEnemy = false;
        return false;
    }
}


void BattleScene::EnemyAttack()
{
    int tempHealth = playerHealth;

    PlayAttack(enemy->getAttackType(), enemy->getAttackColour());

    if (!isPlayerDefending)
    {
        int damageToDeal = 0;

        if(enemy->getAttackPower() > lvlManager->player->pArmour)
            damageToDeal = (enemy->getAttackPower() + enemy->getWeapon().second) - lvlManager->player->pArmour;

        if(enemyHealth - damageToDeal >= 0)
            playerHealth -= damageToDeal;
        else
            playerHealth = 0;
    }

        tempHealth = tempHealth - playerHealth;
        UpdateBattleInfo(enemy->getName() + " dealt " + to_string(tempHealth) + " damage", 1);

    isPlayerDefending = false;
    TPlayerFEnemy = true;
    enemyJustAttacked = true;
}

void BattleScene::EnemyDefend()
{
    PlayDefend(enemy->getDefenceType(), enemy->getDefenceColour());

    UpdateBattleInfo(enemy->getName() + " is defending", 2);

    isEnemyDefending = true;
    isPlayerDefending = false;
    TPlayerFEnemy = true;
    enemyJustAttacked = true;
}

void BattleScene::EnemyHeal()
{
    int tempHealth = enemyHealth;

    PlayHeal(enemy->getHealType(), enemy->getHealColour());

    if (enemyHealth + enemy->getHealPower() <= enemyMaxHealth)
        enemyHealth += enemy->getHealPower();
    else
        enemyHealth = enemyMaxHealth;

    tempHealth = enemyHealth - tempHealth;
    UpdateBattleInfo(enemy->getName() + " healed by " + to_string(tempHealth), 3);

    isPlayerDefending = false;
    TPlayerFEnemy = true;
    enemyJustAttacked = true;
}

void BattleScene::EnemyAction()
{
    // Change of enemy action
    int attackChance = 60; // 0 - 60 (0% - 60%)    -> 60%
    int defenceChance = 80; // 61 - 80 (60% - 80%) -> 20%
    int healChance = 100; // 81 - 100 (80% - 100%)  -> 20%
    int chance = rand() % 101; // From 0 - 100 (0% - 100%)

    if (chance <= attackChance)
        EnemyAttack();
    else if (chance <= defenceChance)
        EnemyDefend();
    else if (chance <= healChance)
        EnemyHeal();
}
