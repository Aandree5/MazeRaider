#include <iostream>
#include "UI.h"
#include "Maze.h"
#include "Player.h"
#include "Score.h"
#include "LevelManager.h"

UI::UI(LevelManager* lvlman)
{
    levelManager = lvlman;
    hScore = lvlman->score->getHScore();
    playerOldPos = make_pair(make_pair(lvlman->player->xPos, lvlman->player->yPos),
                              lvlman->maze->getMazeArray()[lvlman->player->xPos][lvlman->player->yPos]);

    inBattle = false;
}

bool UI::ChangeColour(int colour)
{
    switch (colour)
    {
    case 12:
        red();
        break;
    case 9:
        blue();
        break;
    case 10:
        green();
        break;
    case 14:
        yellow();
        break;
    case 11:
        cyan();
        break;
    case 15:
        white();
        break;
    case 13:
        purple();
        break;
    case 4:
        darkred();
        break;
    case 3:
        darkblue();
        break;
    case 2:
        darkgreen();
        break;
    case 5:
        darkpurple();
        break;
    default:
        grey();
        return false;
        break;
    }

    return true;
}

// cout with colour   CHAR Overload
void UI::PrintC(char character, int colour = 7)
{
    bool needsReset = ChangeColour(colour);

    cout << character << character;

    // Return colour to default
    if (needsReset)
        grey();
}

// cout with colour   STRING Overload
void UI::PrintC(string character, int colour = 7)
{
    bool needsReset = ChangeColour(colour);

    cout << character << character;

    // Return colour to default
    if (needsReset)
        grey();
}

// Build UI
void  UI::ShowUI()
{
    while (true)
    {
        clearScreen();

        UI::printStateInfo();
        if (!inBattle)
            printMaze();
        else
            printBattleScene();

        UI::printUOptions();
    }
}

// Print Maze
void  UI::printMaze()
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
                PrintC( mazePath );
                break;
            case 1: // 1: Wall
                PrintC( mazeWall );
                break;
            case 2: // 1: Wall
                PrintC( mazeWall, 11 );
                break;
            case 3: // 3: Chest
                PrintC( mazeWall, 14);
                break;
            default:
                PrintC( levelManager->maze->getMazeArray()[w][h] );
                break;
            }
        }
    }

    cout << endl;
}

// Print Timer, Scorn and Lives info
void UI::printStateInfo()
{
    cout << "Timer: 0           Score: " << hScore << "            Lives: 3/3" << endl << endl;
}

// Print User Possible Options
void UI::printUOptions()
{
    char userOption;

    cout << endl << endl << "Choose option:    w - Up       a - Left        d - Right        s - Down" << endl;
    cout << endl << "Test battle mode:    b          Player Attack:    z        Enemy Attack:    x" << endl;
    cin >> userOption;

    if (userOption != (char)98)
        levelManager->player->movePlayer(userOption);
    else
        inBattle = !inBattle;

    if (userOption == (char)122)
        isPlayerAttacking = !isPlayerAttacking;
    if (userOption == (char)120)
        isEnemyAttacking = !isEnemyAttacking;
}

void UI::printBattleScene()
{
    int sceneWidth = 100;
    int sceneHeight = 15;
    int playerCounter = 0;
    int enemyCounter = 0;

    vector<string> enemyMesh = {"                                   ",
                                "                          .    .   ",
                                "                           )  (    ",
                                "     _ _ _ _ _ _ _ _ _ _ _(.--.)   ",
                                "   {{ { { { { { { { { { { ( '_')   ",
                                "    >>>>>>>>>>>>>>>>>>>>>>>`--'>   ",
                                "                                   ",
                                "                                   "};


    vector<string> playerMesh = {"       _O_      ",
                               R"(     /     \    )",
                               R"(    |==/=\==|   )",
                                 "    |  O O  |   ",
                               R"(     \  V  /    )",
                               R"(     /`---'\    )",
                                 "     O'_:_`O    ",
                                 "      -- --     "};

    vector<string> playerMesh2 = {"             _____                 ",
                                  "            |     |                ",
                                  R"(            |[/_\]|                )",
                                  R"(            / O O \                )",
                                  R"(           /\  -  /\               )",
                                  R"(            /`---'\                )",
                                  "            O'M|M`O                ",
                                  "             -- --                 "};

    vector<string> playerMesh3 = {"      _<>_      ",
                                R"(    /      \    )",
                                R"(   |==\==/==|   )",
                                  "   |   ><   |   ",
                                R"( ,-\   ()   /-. )",
                                  " V( `-====-' )V ",
                                  " (_____:|_____) ",
                                  "   ----  ----   "};

    vector<string> playerMesh4 = {"               ___                 ",
                                  R"(             /  _  \               )",
                                  R"(            |  / \  |              )",
                                  "            |  |*|  |              ",
                                  R"(             \  X  /               )",
                                  R"(             /`---'\               )",
                                  "             O'_|_`O               ",
                                  "              -- --                ",};

    for (int h = 0; h < sceneHeight; h++)
    {
        for (int w = 0; w < sceneWidth; w++)
        {
            if (h == 0 && w == 0 ) // Top left corner
                cout << (char)218;
            else if (h == 0 && w == sceneWidth - 1 ) // Top right corner
                cout << (char)191;
            else if (h == sceneHeight - 1 && w == 0 ) // Bottom left corner
                cout << (char)192;
            else if (h == sceneHeight - 1 && w == sceneWidth - 1 ) // Bottom right corner
                cout << (char)217;
            else if (h == 0 || h == sceneHeight - 1) // Top and bottom lines
                cout << (char)196;
            else if (w == 0 || w == sceneWidth - 1) // Left and right lines
                cout << (char)179;
            else if (h >= (sceneHeight / 2) - 1 && h < sceneHeight && w > 5 && w <= 21) // Place to draw player
            {
                if (playerCounter < playerMesh2.size())
                {
                    cout << playerMesh[playerCounter];
                    playerCounter++;
                    w += 15;
                }
            }
            else if (h > 0 && h <= sceneHeight / 2 && w >= sceneWidth - 40 && w < sceneWidth - 5) // Place to draw enemy
            {
                if (enemyCounter < enemyMesh.size())
                {
                    cout << enemyMesh[enemyCounter];
                    enemyCounter++;
                    w += 34;
                }
            }
            else // Empty space -> TO DO
                cout << (char)32;
        }
        cout << endl;
    }

    if (isPlayerAttacking){

            SHORT xPos = 22;
            SHORT yPos = 13;
            HANDLE hStdOut = GetStdHandle( STD_OUTPUT_HANDLE );
            CONSOLE_SCREEN_BUFFER_INFO cbsi;
            GetConsoleScreenBufferInfo(hStdOut, &cbsi);
            COORD originalPos = cbsi.dwCursorPosition;
            COORD pos = { xPos, yPos };

            green();

            for (int i = 0; i <= 38; i++)
            {
                PlayerAttack(hStdOut, xPos, yPos, 0, 1);

                xPos++;
                if (i % 7 == 0)
                    yPos--;
                }

            grey();

            SetConsoleCursorPosition( hStdOut, originalPos );
        }
}

void UI::PlayerAttack(HANDLE hStdOut, int xPos, int yPos, int number, int animSpeed)
{
    switch (number)
    {
        case 0:
            SetConsoleCursorPosition( hStdOut, { xPos, yPos } ); // Main
            cout << mazeWall;
            SetConsoleCursorPosition( hStdOut, { xPos+1, yPos } ); // Front
            cout << mazeWall;
            SetConsoleCursorPosition( hStdOut, { xPos-1, yPos } ); // Back
            cout << mazeWall;
            SetConsoleCursorPosition( hStdOut, { xPos, yPos+1 } ); // Bottom
            cout << (char)223;
            SetConsoleCursorPosition( hStdOut, { xPos+1, yPos+1 } ); // Bottom Front
            cout << (char)223;

            Sleep(animSpeed);

            SetConsoleCursorPosition( hStdOut, { xPos, yPos } ); // Main
            cout << " ";
            SetConsoleCursorPosition( hStdOut, { xPos+1, yPos } ); // Front
            cout << " ";
            SetConsoleCursorPosition( hStdOut, { xPos-1, yPos } ); // Back
            cout << " ";
            SetConsoleCursorPosition( hStdOut, { xPos, yPos+1 } ); // Bottom
            cout << " ";
            SetConsoleCursorPosition( hStdOut, { xPos+1, yPos+1 } ); // Bottom Front
            cout << " ";
            break;
    }



}
