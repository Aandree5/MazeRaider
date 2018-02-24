#ifndef BATTLESCENE_H
#define BATTLESCENE_H
#include <vector>
#include <iostream>
#include <array>

#define attackAnimSpeed 10
#define defenceHealAnimSpeed 150

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
        void PlayerAttack();
        void PlayerDefend();
        void PlayerHeal();

        // Set of enemy actions
        void EnemyAttack();
        void EnemyDefend();
        void EnemyHeal();

        //TEMP
        int playerHealth;
        int playerMaxHealth;
        int enemyHealth;
        int enemyMaxHealth;
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
        void PlayAttack(int atype, int colour);
        // Play defend animation
        void PlayDefend(int dtype, int colour);
        // Play heal animation
        void PlayHeal(int htype, int colour);

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
