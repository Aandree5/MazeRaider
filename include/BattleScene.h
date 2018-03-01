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
        bool canPlayerRun();

        // Set of enemy actions
        void EnemyAttack();
        void EnemyDefend();
        void EnemyHeal();
        void EnemyAction();

        // Player Enemy info
        int playerHealth;
        int playerMaxHealth;
        int enemyHealth;
        int enemyMaxHealth;

        pair<int, int> getSceneSizeWH();

        Enemy* enemy;
    protected:

    private:
        LevelManager* lvlManager;

        // Text to show and type action | 0 = attack   1 = defend    2 = heal
        array<pair<string, int>, 13> battleInfo;

        unsigned sceneWidth;
        unsigned sceneHeight;

        int pauseColour(int colour);

        //Check if player is defending
        bool isPlayerDefending;
        //Check if enemy is defending
        bool isEnemyDefending;

        // Check health color
        int HealthColor(int health, bool TBackFFront = true);

        // Add line to battleInfo - Text to show and type action | 0 = info  1 = attack   2 = defend    3 = heal
        void UpdateBattleInfo(string text, int type);

        // Play attack animation
        void PlayAttack(int atype, int colour);
        // Play defend animation
        void PlayDefend(int dtype, int colour);
        // Play heal animation
        void PlayHeal(int htype, int colour);
};
#endif // BATTLESCENE_H
