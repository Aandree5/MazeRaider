#ifndef UI_H
#define UI_H
#include <vector>



using namespace std;

class LevelManager;
class BattleScene;

class  UI
{
    public:
        UI(LevelManager* lvlman);

        // Build UI
        void ShowUI();


        // Check if it's in battle
        bool inBattle;

        BattleScene* btlScene;

    protected:

    private:

        // Pointer to level manager
        LevelManager* lvlManager;

        // Print Maze
        void PrintMaze();
        // Print Timer, Scorn and Lives info
        void PrintStateInfo();
        // Print User Possible Options
        void PrintUOptions();
        // Screen for gameover
        void ShowGameOver();

};

#endif // UI_H
