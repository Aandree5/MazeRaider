#ifndef UIHELPERS_H
#define UIHELPERS_H

#include <string>
#include <iostream>

#ifdef _WIN32
#include <windows.h>
#include <stdlib.h>
#define clearScreen() system("cls")
#define mazeWall (char)219
#define mazePath (char)32
#define bsTopLeftCorner (char)218
#define bsTopRightCorner (char)191
#define bsBottomLeftCorner (char)192
#define bsBottomRightCorner (char)217
#define bsTopBottomLines (char)196
#define bsLeftRightLines (char)179
#define upHorizontal (char)193
#define downHorizontal (char)194
#define rightVertical (char)195
#define HorizontalVertical (char)197
#define leftVertical (char)180
#define attackBottom (char)223
#define attackTop (char)220
#define healSymbol (char)207
#define shieldSymbol (char)245
#define cursorPosition(h, x, y) SetConsoleCursorPosition( h, { x, y } )
#define red SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12)
#define blue SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9)
#define green SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10)
#define yellow SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14)
#define cyan SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11)
#define white SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15)
#define purple SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 13)
#define darkred SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4)
#define darkblue SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3)
#define darkgreen SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2)
#define darkpurple SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 5)
#define grey SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7)
#define healthGreen SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 34)
#define healthYellow SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 238)
#define healthRed SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 68)
#define debugBlackGreen SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 164)
#define debugBlackRed SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 192)
#endif // _WIN32

#ifdef __linux__
#include <sstream>
#include <chrono>
#include <thread>
#define Sleep(x) cout << flush; this_thread::sleep_for(chrono::milliseconds(x));
#define clearScreen() cout << "\033[2J\033[1;1H"
#define mazeWall "\u2588"
#define mazePath "\u0020"
#define bsTopLeftCorner "\u250c"
#define bsTopRightCorner "\u2510"
#define bsBottomLeftCorner "\u2514"
#define bsBottomRightCorner "\u2518"
#define bsTopBottomLines "\u2500"
#define bsLeftRightLines "\u2502"
#define upHorizontal "\u2534"
#define downHorizontal "\u252c"
#define rightVertical "\u251c"
#define HorizontalVertical "\u2524"
#define leftVertical "\u253c"
#define attackBottom "\u2580"
#define attackTop "\u2584"
#define healSymbol "\u00a4"
#define shieldSymbol "\u00a7"
#define cursorPosition(h, x, y) cout << "\033[" << y << ";" << x << "H"
#define red cout << "\033[1;31m"
#define blue cout << "\033[1;34m"
#define green cout << "\033[1;32m"
#define yellow cout << "\033[1;33m"
#define cyan cout << "\033[1;36m"
#define white cout << "\033[1;37m"
#define purple cout << "\033[1;35m"
#define darkred cout << "\033[0;31m"
#define darkblue cout << "\033[0;34m"
#define darkgreen cout << "\033[0;32m"
#define darkpurple cout << "\033[0;35m"
#define grey cout << "\033[1;37m"
#define healthGreen cout << "\033[1;32m"
#define healthYellow cout << "\033[1;33m"
#define healthRed cout << "\033[1;31m"
#endif // __linux__

using namespace std;

namespace UIHelpers
{
    // cout with colour   CHAR Overload
    void PrintC(char character, int color = 7, bool twoChar = false);
    // cout with colour   STRING Overload
    void PrintC(string character, int color = 7, bool twoChar = false);
    // change the text colour
    bool ChangeColor(int color);
};

#endif // UIHELPERS_H
