#ifndef BATTLESCENE_H
#define BATTLESCENE_H
#include "UIHelpers.h"
#include <vector>
#include <iostream>
#include <array>
#include <memory>

#define attackAnimSpeed 10
#define defenceHealAnimSpeed 150

using namespace std;
using namespace UIHelpers;

class LevelManager;
class Enemy;

class BattleScene
{
    public:
        BattleScene(shared_ptr<LevelManager> lvlman, shared_ptr<Enemy> e);

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

        weak_ptr<Enemy> enemy;
    protected:

    private:
        weak_ptr<LevelManager> lvlManager;

        // Text to show and type action | 0 = attack   1 = defend    2 = heal
        array<pair<string, MessageType>, 13> battleInfo;

        unsigned sceneWidth;
        unsigned sceneHeight;

        int pauseColour(int colour);

        //Check if player is defending
        bool isPlayerDefending;
        //Check if enemy is defending
        bool isEnemyDefending;

        // Check health color
        int HealthColor(int health, bool TBackFFront = true);

        // Play attack animation
        void PlayAttack(int atype, int colour);
        // Play defend animation
        void PlayDefend(int dtype, int colour);
        // Play heal animation
        void PlayHeal(int htype, int colour);
};
#endif // BATTLESCENE_H
