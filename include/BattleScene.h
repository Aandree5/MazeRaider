#ifndef BATTLESCENE_H
#define BATTLESCENE_H
#include <vector>
#include <iostream>

using namespace std;

class LevelManager;

class BattleScene
{
    public:
        BattleScene(LevelManager* lvlman);

        // Call battle scene
        int BuildScene();

        // Player or Enemy attacking
        bool TPlayerFEnemy = true;



        void PlayerAttack(int num, int color, int power, int speed);
        void PlayerDefend(int num, int color, int speed);
        void PlayerHeal(int num, int color, int power, int speed);

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

        bool isPlayerDefending;
        bool isEnemyDefending;

        // Check health color
        int HealthColor(int health, bool TBackFFront = true);

        // Handles player attack type
        void PlayAttack(int num, int color, int speed);
        // Handles player attack type
        void PlayDefend(int num, int color, int speed);
        // Handles player attack type
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
