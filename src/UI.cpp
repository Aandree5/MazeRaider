#include <iostream>
#include "UI.h"
#include <tuple>

#ifdef _WIN32
#include <windows.h>
#include <stdlib.h>
#define clearScreen() system("cls")
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

// cout with colour
void UI::PrintC(char character, bool endLine = false, int colour = 7)
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
        break;
    }

    if (endLine)
    {
        std::cout << character << character << std::endl;
    }
    else
    {
        std::cout << character << character;
    }

    // Return colour to default
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
            case 0: // 0: Path > 32
                //std::cout << (char)32 << (char)32;
                PrintC( (char)32 );
                break;
            case 1: // 1: Wall > 219
                PrintC( (char)219 );
                break;
            case 3: // 3: Chest > 219 Yellow
                PrintC( (char)219, false, 14);
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
