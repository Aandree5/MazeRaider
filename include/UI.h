#ifndef UI_H
#define UI_H
#include <string>
#include "Maze.h"

class  UI
{
    public:
        // cout with colour   CHAR Overload
        static void PrintC(char character, int colour);
        // cout with colour   STRING Overload
        static void PrintC(std::string character, int colour);
        // change the text colour
        static bool ChangeColour(int colour);

        // Build UI
        static void ShowUI(Maze* maze);

    protected:

    private:
        static int** m_maze;

        // Print Maze
        static void printMaze(Maze* maze);
        // Print Timer, Scorn and Lives info
        static void printStateInfo();
        // Print User Possible Options
        static void printUOptions();
};

#endif // UI_H
