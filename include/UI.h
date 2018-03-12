#ifndef UI_H
#define UI_H
#include "UIHelpers.h"
#include <vector>
#include <array>
#include <map>
#ifdef _WIN32
#include <windows.h>
#endif // _WIN32
#include <mysql.h>
#include <memory>



using namespace std;
using namespace UIHelpers;

class LevelManager;
class BattleScene;
class Enemy;
class ScoreTime;

class  UI
{
    public:
        UI(shared_ptr<LevelManager> lvlman);

        // Build UI
        void ShowUI();
        //Show player character selection screen
        void ShowSelectionScreen();
        void ShowNextLevel();

        // Check if it's in battle
        bool inBattle;

        unique_ptr<BattleScene> btlScene;
        void StartBattleScene(shared_ptr<Enemy> enemy);

        array<pair<string, UIHelpers::MessageType>, 3> mazeInfo;

         // Meshes
        vector<array<string, 8>> enemyMesh = {{"                                   ",
                                               "                          .    .   ",
                                               "                           )  (    ",
                                               "     _ _ _ _ _ _ _ _ _ _ _(.--.)   ",
                                               "   {{ { { { { { { { { { { ( '_')   ",
                                               "    >>>>>>>>>>>>>>>>>>>>>>>`--'>   ",
                                               "                                   ",
                                               "                                   "},

                                              {"                                   ",
                                             R"(              _.---._    /\\       )",
                                             R"(           ./'       "--`\//       )",
                                             R"(         ./              o \       )",
                                             R"(        /./\  )______   \__ \      )",
                                             R"(       ./  / /\ \   | \ \  \ \     )",
                                             R"(          / /  \ \  | |\ \  \7     )",
                                               "                                   "},

                                              {"                                   ",
                                             R"(            (o)--(o)               )",
                                             R"(           /.______.\              )",
                                             R"(           \________/              )",
                                             R"(          ./        \.             )",
                                             R"(         ( .        , )            )",
                                             R"(          \ \_\\//_/ /             )",
                                             R"(           ~~  ~~  ~~              )"},

                                              {"                                   ",
                                             R"(                    .-._           )",
                                             R"(                   {_}^ )o         )",
                                             R"(          {\________//~`           )",
                                             R"(           (         )             )",
                                             R"(           /||~~~~~||\             )",
                                             R"(          |_\\_    \\_\            )",
                                             R"(          "' ""'    ""'"'          )"}};

        vector<array<string, 8>> playerMesh = {{"       _O_      ",
                                              R"(     /     \    )",
                                              R"(    |==/=\==|   )",
                                                "    |  O O  |   ",
                                              R"(     \  V  /    )",
                                              R"(     /`---'\    )",
                                                "     O'_:_`O    ",
                                                "      -- --     "},

                                               {"      _____     ",
                                                "     |     |    ",
                                              R"(     |[/_\]|    )",
                                              R"(     / O O \    )",
                                              R"(    /\  -  /\   )",
                                              R"(     /`---'\    )",
                                                "     O'M|M`O    ",
                                                "      -- --     "},

                                               {"      _<>_      ",
                                              R"(    /      \    )",
                                              R"(   |==\==/==|   )",
                                                "   |   ><   |   ",
                                              R"( ,-\   ()   /-. )",
                                                " V( `-====-' )V ",
                                                " (_____:|_____) ",
                                                "   ----  ----   "},

                                               {"       ___      ",
                                              R"(     /  _  \    )",
                                              R"(    |  / \  |   )",
                                                "    |  |*|  |   ",
                                              R"(     \  X  /    )",
                                              R"(     /`---'\    )",
                                                "     O'_|_`O    ",
                                                "      -- --     "}};

    protected:

    private:
        // Pointer to level manager
        weak_ptr<LevelManager> lvlManager;

        // Overload for UIHelpers PrintC function for pausing game
        void PrintC(char character, int colour = 7, bool twoChar = false, bool hideWhenPaused = false);
        void PrintC(string character, int colour = 7, bool twoChar = false, bool hideWhenPaused = false);

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
