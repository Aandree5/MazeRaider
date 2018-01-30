#include <iostream>
#include <tuple>
#include "UI.h"

#ifdef _WIN32
#include <windows.h>
#include <stdlib.h>
#define clearScreen() system("cls")
#define mazeWall (char)219
#define mazePath (char)32
#define red() SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12)
#define blue() SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9)
#define green() SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10)
#define yellow() SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14)
#define cyan() SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11)
#define white() SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15)
#define purple() SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 13)
#define darkred() SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4)
#define darkblue() SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3)
#define darkgreen() SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2)
#define darkpurple() SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 5)
#define grey() SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7)
#endif // _WIN32

#ifdef __linux__
#define mazeWall "\u2588"
#define mazePath "\u0020"
#define red() cout << "\033[1;31m"
#define blue() cout << "\033[1;34m"
#define green() cout << "\033[1;32m"
#define yellow() cout << "\033[1;33m"
#define cyan() cout << "\033[1;36m"
#define white() cout << "\033[1;37m"
#define purple() cout << "\033[1;35m"
#define darkred() cout << "\033[0;31m"
#define darkblue() cout << "\033[0;34m"
#define darkgreen() cout << "\033[0;32m"
#define darkpurple() cout << "\033[0;35m"
#define grey() cout << "\033[1;37m"
#endif // __LINUX__

UI::UI(Maze* maze)
{
    printableMaze = get<0>(maze->getDataMWH());
    mazeWidth = get<1>(maze->getDataMWH());
    mazeHeight = get<2>(maze->getDataMWH());

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
void  UI::ShowUI(Player* player)
{
    clearScreen();

    UI::printStateInfo();
    if (!inBattle)
        printMaze(make_pair(player->xPos, player->yPos));
    else
        printBattleScene();

    UI::printUOptions(player);
}

// Print Maze
void  UI::printMaze(pair<int,int> playerPos)
{
    // Get player position
    printableMaze[playerPos.first][playerPos.second] = 2;

    // Print maze with objects
    for(int h = 0; h < mazeWidth ; h++) {
        cout << endl;

        for(int w = 0; w < mazeHeight ; w++)
            {
            switch ( printableMaze[w][h]){
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
                PrintC( printableMaze[w][h] );
                break;
            }
        }
    }

    cout << endl;
}

// Print Timer, Scorn and Lives info
void UI::printStateInfo()
{
    cout << "Timer: 0           Score: 0            Lives: 3/3" << endl << endl;
}

// Print User Possible Options
void UI::printUOptions(Player* player)
{
    char userOption;

    cout << endl << endl << "Choose option:    w - Up       a - Left        d - Right        s - Down" << endl;
    cout << endl << "Test battle mode:    b" << endl;
    cin >> userOption;

    if (userOption != (char)98)
        player->move(userOption);
    else
        inBattle = !inBattle;

    ShowUI(player);
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

    vector<string> playerMesh = {"              _O_                  ",
                                  R"(            /     \                )",
                                  R"(           |==/=\==|               )",
                                  "           |  O O  |               ",
                                  R"(            \  V  /                )",
                                  R"(            /`---'\                )",
                                  "            O'_:_`O                ",
                                  "             -- --                 "};

    vector<string> playerMesh2 = {"              _O_                  ",
                                  R"(            /     \                )",
                                  R"(           |==/=\==|               )",
                                  "           |  O O  |               ",
                                  R"(            \  V  /                )",
                                  R"(            /`---'\                )",
                                  "            O'_:_`O                ",
                                  "             -- --                 "};
/*
    _O_    1    _____         _<>_          ___
  /     \  1   |     |      /      \      /  _  \
 |==/=\==| 1   |[/_\]|     |==\==/==|    |  / \  |
 |  O O  | 1   / O O \     |   ><   |    |  |"|  |
  \  V  /  1  /\  -  /\  ,-\   ()   /-.   \  X  /
  /`---'\  1   /`---'\   V( `-====-' )V   /`---'\
  O'_:_`O  1   O'M|M`O   (_____:|_____)   O'_|_`O
   -- --   1    -- --      ----  ----      -- --
*/

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
            else if (h >= (sceneHeight / 2) - 1 && h < sceneHeight && w > 5 && w <= 30) // Place to draw player
            {
                if (playerCounter < playerMesh2.size())
                {
                    cout << playerMesh[playerCounter];
                    playerCounter++;
                    w += 34;
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
}
