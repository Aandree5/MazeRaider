#include <iostream>
#include "UI.h"
#include <tuple>

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

    std::cout << character << character;

    // Return colour to default
    if (needsReset)
        grey();
}

// cout with colour   STRING Overload
void UI::PrintC(std::string character, int colour = 7)
{
    bool needsReset = ChangeColour(colour);

    std::cout << character << character;

    // Return colour to default
    if (needsReset)
        grey();
}

// Build UI
void  UI::ShowUI(Maze* maze)
{
    UI::printStateInfo();
    printMaze(maze);
    UI::printUOptions();
}

// Print Maze
void  UI::printMaze(Maze* maze)
{

    // getDataMWH - get height = 2
    for(int h = 0; h < std::get<2>(maze->getDataMWH()) ; h++) {
        std::cout << std::endl;

        // getDataMWH - get width = 1
        for(int w = 0; w < std::get<1>(maze->getDataMWH()) ; w++) {

            // getDataMWH - get maze = 0
            switch ( std::get<0>(maze->getDataMWH())[w][h]){
            case 0: // 0: Path
                PrintC( mazePath );
                break;
            case 1: // 1: Wall
                PrintC( mazeWall );
                break;
            case 3: // 3: Chest
                PrintC( mazeWall, 14);
                break;
            default:
                PrintC( std::get<0>(maze->getDataMWH())[w][h] );
                break;
            }
        }
    }

    std::cout << std::endl;
}

// Print Timer, Scorn and Lives info
void UI::printStateInfo()
{
    std::cout << "Timer: 0           Score: 0            Lives: 3/3" << std::endl << std::endl;
}

// Print User Possible Options
void UI::printUOptions()
{

}
