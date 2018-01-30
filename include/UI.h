#ifndef UI_H
#define UI_H
#include <string>
#include "Maze.h"
#include "Player.h"

using namespace std;

class  UI
{
    public:
        UI(Maze* maze);
        // cout with colour   CHAR Overload
        void PrintC(char character, int colour);
        // cout with colour   STRING Overload
        void PrintC(string character, int colour);
        // change the text colour
        bool ChangeColour(int colour);

        // Build UI
        void ShowUI(Player* player);

    protected:

    private:

        //TEMP
        bool inBattle;

        // Printable maze, easier to print player and enemies, doesn't have to check on every loop cycle
        int** printableMaze;

        // Maze size
        int mazeWidth;
        int mazeHeight;

        // Print Maze
        void printMaze(pair<int,int> playerPos);
        // Print Timer, Scorn and Lives info
        void printStateInfo();
        // Print User Possible Options
        void printUOptions(Player* player);
        // Call battle scene
        void printBattleScene();
};

#endif // UI_H
