#ifndef BATTLESCENE_H
#define BATTLESCENE_H
#include <vector>
#include <iostream>
#include <array>

#ifdef _WIN32
#define bsTopLeftCorner (char)218
#define bsTopRightCorner (char)191
#define bsBottomLeftCorner (char)192
#define bsBottomRightCorner (char)217
#define bsTopBottomLines (char)196
#define bsLeftRightLines (char)179
#endif // _WIN32

#ifdef __linux__
#define bsTopLeftCorner "\u231C"
#define bsTopRightCorner "\u231D"
#define bsBottomLeftCorner "\u231E"
#define bsBottomRightCorner "\u231F"
#define bsTopBottomLines "\2015"
#define bsLeftRightLines "\2758"
#endif // __LINUX__

using namespace std;

class LevelManager;
class Enemy;

class BattleScene
{
    public:
        BattleScene(LevelManager* lvlman, Enemy* e);

        // Call battle scene
        int BuildScene();

        // Player or Enemy attacking
        bool TPlayerFEnemy = true;

        // Used to refresh the console right after enemy attacks, and not get stuck waiting for users next move
        bool enemyJustAttacked;

        // Set of player actions
        void PlayerAttack(int num, int color, int power, int speed);
        void PlayerDefend(int num, int color, int speed);
        void PlayerHeal(int num, int color, int power, int speed);

        // Set of enemy actions
        void EnemyAttack(int num, int color, int power, int speed);
        void EnemyDefend(int num, int color, int speed);
        void EnemyHeal(int num, int color, int power, int speed);

        //TEMP
        int playerHealth = 100;
        int playerMaxHealth = 100;
        int enemyHealth = 100;
        int enemyMaxHealth = 100;
    protected:

    private:
        LevelManager* lvlManager;
        Enemy* enemy;

        // Text to show and type action | 0 = attack   1 = defend    2 = heal
        array<pair<string, int>, 13> battleInfo;

        //Check if player is defending
        bool isPlayerDefending;
        //Check if enemy is defending
        bool isEnemyDefending;

        // Check health color
        int HealthColor(int health, bool TBackFFront = true);

        // Add line to battleInfo - Text to show and type action | 0 = attack   1 = defend    2 = heal
        void UpdateBattleInfo(pair<string, int> lineToAdd);

        // Play attack animation
        void PlayAttack(int num, int color, int speed);
        // Play defend animation
        void PlayDefend(int num, int color, int speed);
        // Play heal animation
        void PlayHeal(int num, int color, int speed);

        // Meshes
        vector<vector<string>> enemyMesh = {{"                                   ",
                                             "                          .    .   ",
                                             "                           )  (    ",
                                             "     _ _ _ _ _ _ _ _ _ _ _(.--.)   ",
                                             "   {{ { { { { { { { { { { ( '_')   ",
                                             "    >>>>>>>>>>>>>>>>>>>>>>>`--'>   ",
                                             "                                   ",
                                             "                                   "}};


        vector<vector<string>> playerMesh = {{"       _O_      ",
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
                                              "      -- --     ",}};

};
#endif // BATTLESCENE_H
