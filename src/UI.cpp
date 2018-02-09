#include <math.h>
#include "UI.h"
#include "Maze.h"
#include "Player.h"
#include "ScoreTime.h"
#include "LevelManager.h"

UI::UI(LevelManager* lvlman)
{
    levelManager = lvlman;
    playerOldPos = make_pair(make_pair(lvlman->player->xPos, lvlman->player->yPos),
                              lvlman->maze->getMazeArray()[lvlman->player->xPos][lvlman->player->yPos]);

    inBattle = false;
}

bool UI::ChangeColor(int color)
{
    switch (color)
    {
    case 12:
        red;
        break;
    case 9:
        blue;
        break;
    case 10:
        green;
        break;
    case 14:
        yellow;
        break;
    case 11:
        cyan;
        break;
    case 15:
        white;
        break;
    case 13:
        purple;
        break;
    case 4:
        darkred;
        break;
    case 3:
        darkblue;
        break;
    case 2:
        darkgreen;
        break;
    case 5:
        darkpurple;
        break;
    case 34:
        healthGreen;
        break;
    case 238:
        healthYellow;
        break;
    case 68:
        healthRed;
        break;
    default:
        grey;
        return false;
    }

    return true;
}

// cout with color   CHAR Overload
void UI::PrintC(char character, int color = 7, bool twoChar = false)
{
    bool needsReset = ChangeColor(color);

    if (twoChar)
        cout << character << character;
    else
        cout << character;

    // Return color to default
    if (needsReset)
        grey;
}

// cout with color   STRING Overload
void UI::PrintC(string character, int color = 7, bool twoChar = false)
{
    bool needsReset = ChangeColor(color);

    if (twoChar)
        cout << character << character;
    else
        cout << character;

    // Return color to default
    if (needsReset)
        grey;
}

// Build UI
void  UI::ShowUI()
{
    int battleState = 0; // 0 = Battle Continues  |  1 = Player Lost (GameOver)  |  2 = Enemy Killed
    while (true && battleState != 1)
    {
        clearScreen();
        battleState = 0;

        PrintStateInfo();
        if (!inBattle)
            PrintMaze();
        else
            battleState = BattleScene();

        if (battleState == 1)
            break;
        else if (battleState == 2)
            continue;

        if (playerTurn)
            PrintUOptions();
    }

    if (battleState == 1)
        ShowGameOver();
}

// Print Maze
void  UI::PrintMaze()
{
    // Get player position, 2 = Player
    if (levelManager->maze->getMazeArray()[levelManager->player->xPos][levelManager->player->yPos] != 2)
    {
        // Replace player old position and store the new "old" position to replace later
        levelManager->maze->getMazeArray()[playerOldPos.first.first][playerOldPos.first.second] = playerOldPos.second;
        playerOldPos = make_pair(make_pair(levelManager->player->xPos, levelManager->player->yPos),
                              levelManager->maze->getMazeArray()[levelManager->player->xPos][levelManager->player->yPos]);

        levelManager->maze->getMazeArray()[levelManager->player->xPos][levelManager->player->yPos] = 2;
    }

    // Print maze with objects
    for(int h = 0; h < levelManager->maze->getMazeSizeWH().second ; h++) {
        cout << endl;

        for(int w = 0; w < levelManager->maze->getMazeSizeWH().first ; w++)
            {
            switch ( levelManager->maze->getMazeArray()[w][h]){
            case 0: // 0: Path
                PrintC( mazePath, 7, true);
                break;
            case 1: // 1: Wall
                PrintC( mazeWall, 7, true );
                break;
            case 2: // 1: Wall
                PrintC( mazeWall, 11, true  );
                break;
            case 3: // 3: Chest
                PrintC( mazeWall, 14, true );
                break;
            default:
                PrintC( levelManager->maze->getMazeArray()[w][h], 7, true );
                break;
            }
        }
    }

    cout << endl;
}

// Print Timer, Scorn and Lives info
void UI::PrintStateInfo()
{
    cout << "Timer: " << levelManager->scoretime->getTime() << "           Score: " << levelManager->scoretime->getHScore() << "            Lives: 3/3" << endl << endl;
}

// Print User Possible Options
void UI::PrintUOptions()
{
    char userOption;

    if (!inBattle)
    {
        cout << endl << endl << "Choose option:    w - Up       a - Left        d - Right        s - Down" << endl;
        cin >> userOption;


        if (userOption != (char)98)
            levelManager->player->movePlayer(userOption);
        else
            inBattle = true;
    }
    else
    {
        cout << endl << "Attack:    z        Run:     r" << endl;
        cin >> userOption;

        // Player attacks
        if (userOption == (char)122)
        {
            playerTurn = false;
            TPlayerFEnemy = true;
            enemyHealth -= 10;
            PlayAttack(1, 10, 5);
        }

        // Player runs
        else if (userOption == (char)114)
        {
            playerHealth = playerMaxHealth;
            enemyHealth = enemyMaxHealth;
            inBattle = false;
        }
    }
}

int UI::BattleScene()
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
        ResetBattleScene();
        return 1;
    }
    else if (enemyHealth <= 0)
    {
       ResetBattleScene();
       return 2;
    }
    else
    {
        // Print battle scene
        for (int h = 0; h < sceneHeight; h++)
        {
            for (int w = 0; w < sceneWidth; w++)
            {
// Top left corner
                if (h == 0 && w == 0 )
                {
                    cout << (char)218;
                }

// Top right corner
                else if (h == 0 && w == sceneWidth - 1 )
                {
                    cout << (char)191;
                }

// Bottom left corner
                else if (h == sceneHeight - 1 && w == 0 )
                {
                    cout << (char)192;
                }

// Bottom right corner
                else if (h == sceneHeight - 1 && w == sceneWidth - 1 )
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

// Player Health
                else if (w >= 5 && w <= (pHealth + 5) && h == 3)
                {
                    PrintC("#", HealthColor(pHealth));
                }

// Enemy Health
                else if (w >= 68 && w <= (eHealth + 68) && h == 11)
                {
                    PrintC("#", HealthColor(eHealth));
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

    if (!playerTurn)
        EnemyAttack();

    return 0;
}

void UI::PlayAttack(int attackNr, int attackColor, int animSpeed)
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
                    PrintC(mazeWall, attackColor);
                    cursorPosition( hStdOut, xPos + 1, yPos ); // Front
                    PrintC(mazeWall, attackColor);
                    cursorPosition( hStdOut, xPos - 1, yPos ); // Back
                    PrintC(mazeWall, attackColor);
                    cursorPosition( hStdOut, xPos, yPos + 1 ); // Bottom
                    PrintC(attackBottom, attackColor);
                    cursorPosition( hStdOut, xPos + 1, yPos + 1 ); // Bottom Front
                    PrintC(attackBottom, attackColor);

                    Sleep(animSpeed);

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
                    PrintC(mazeWall, attackColor);
                    cursorPosition( hStdOut, xPos, yPos - 1 ); // Top
                    PrintC(attackTop, attackColor);
                    cursorPosition( hStdOut, xPos - 1, yPos - 1 ); // Top Front
                    PrintC(attackTop, attackColor);
                    cursorPosition( hStdOut, xPos - 1, yPos ); // Front
                    PrintC(mazeWall, attackColor);
                    cursorPosition( hStdOut, xPos + 1, yPos ); // Back
                    PrintC(mazeWall, attackColor);

                    Sleep(animSpeed);

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
                    PrintC(mazeWall, attackColor);
                    cursorPosition( hStdOut, xPos + 2, yPos - 1 ); // Front Middle
                    PrintC(mazeWall, attackColor);
                    cursorPosition( hStdOut, xPos - 2, yPos + 1 ); // Back Middle
                    PrintC(mazeWall, attackColor);
                    cursorPosition( hStdOut, xPos, yPos - 2 ); // Main Top
                    PrintC(mazeWall, attackColor);
                    cursorPosition( hStdOut, xPos + 2, yPos - 3 ); // Front Top
                    PrintC(mazeWall, attackColor);
                    cursorPosition( hStdOut, xPos - 2, yPos - 1 ); // Back Top
                    PrintC(mazeWall, attackColor);
                    cursorPosition( hStdOut, xPos, yPos + 2 ); // Main Bottom
                    PrintC(mazeWall, attackColor);
                    cursorPosition( hStdOut, xPos + 2, yPos + 1 ); // Front Bottom
                    PrintC(mazeWall, attackColor);
                    cursorPosition( hStdOut, xPos - 2, yPos + 3 ); // Back Bottom
                    PrintC(mazeWall, attackColor);

                    Sleep(animSpeed);

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
                    PrintC(mazeWall, attackColor);
                    cursorPosition( hStdOut, xPos - 2, yPos + 1 ); // Front Middle
                    PrintC(mazeWall, attackColor);
                    cursorPosition( hStdOut, xPos + 2, yPos - 1 ); // Back Middle
                    PrintC(mazeWall, attackColor);
                    cursorPosition( hStdOut, xPos, yPos - 2 ); // Main Top
                    PrintC(mazeWall, attackColor);
                    cursorPosition( hStdOut, xPos - 2, yPos - 1 ); // Front Top
                    PrintC(mazeWall, attackColor);
                    cursorPosition( hStdOut, xPos + 2, yPos - 3 ); // Back Top
                    PrintC(mazeWall, attackColor);
                    cursorPosition( hStdOut, xPos, yPos + 2 ); // Main Bottom
                    PrintC(mazeWall, attackColor);
                    cursorPosition( hStdOut, xPos - 2, yPos + 3 ); // Front Bottom
                    PrintC(mazeWall, attackColor);
                    cursorPosition( hStdOut, xPos + 2, yPos + 1 ); // Back Bottom
                    PrintC(mazeWall, attackColor);

                    Sleep(animSpeed);

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

int UI::HealthColor(int health)
{
    if (health > 10)
        return 34;
    else if (health > 5)
         return 238;
    else
         return 68;
}

void UI::ResetBattleScene()
{
    playerHealth = playerMaxHealth;
    enemyHealth = enemyMaxHealth;
    inBattle = false;
    playerTurn = true;
}

void UI::EnemyAttack()
{
    playerTurn = true;
    TPlayerFEnemy = false;
    playerHealth -= 10;
    PlayAttack(1, 10, 5);
}

void UI::ShowGameOver()
{
    clearScreen();
    cout << "Game Over!";
}
