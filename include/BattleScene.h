#ifndef BATTLESCENE_H
#define BATTLESCENE_H
#include <vector>
#include <iostream>
#include <array>

#define attackAnimSpeed 10
#define defencehealAnimSpeed 150

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
        void PlayerAttack(int num, int color, int power, int speed = attackAnimSpeed);
        void PlayerDefend(int num, int color, int speed = defencehealAnimSpeed);
        void PlayerHeal(int num, int color, int power, int speed = defencehealAnimSpeed);

        // Set of enemy actions
        void EnemyAttack(int num, int color, int power, int speed = attackAnimSpeed);
        void EnemyDefend(int num, int color, int speed = defencehealAnimSpeed);
        void EnemyHeal(int num, int color, int power, int speed = defencehealAnimSpeed);

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
