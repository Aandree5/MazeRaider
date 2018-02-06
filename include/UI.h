#ifndef UI_H
#define UI_H
#include <string>

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
#define clearScreen() cout << "\033[2J\033[1;1H"
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

using namespace std;

class LevelManager;

class  UI
{
    public:
        UI(LevelManager* lvlman);
        // cout with colour   CHAR Overload
        void PrintC(char character, int colour);
        // cout with colour   STRING Overload
        void PrintC(string character, int colour);
        // change the text colour
        bool ChangeColour(int colour);

        // Build UI
        void ShowUI();

    protected:

    private:

        //TEMP
        bool inBattle;
        bool isPlayerAttacking = false;
        bool isEnemyAttacking = false;

        int hScore;

        // Pointer to level manager
        LevelManager* levelManager;

        // Get the "thing" in that new position so we can replace it after player move
        pair<pair<int, int>, int> playerOldPos;

        // Print Maze
        void printMaze();
        // Print Timer, Scorn and Lives info
        void printStateInfo();
        // Print User Possible Options
        void printUOptions();
        // Call battle scene
        void printBattleScene();
        // Handles player attack type
        void PlayerAttack(HANDLE hStdOut, int xPos, int yPos, int number, int animSpeed);
};

#endif // UI_H
