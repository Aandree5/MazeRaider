#include "UI.h"
#include "UIHelpers.h"
#include "Maze.h"
#include "Player.h"
#include "ScoreTime.h"
#include "LevelManager.h"
#include "BattleScene.h"
#include "Enemy.h"
#include "EnemyAI.h"

using namespace UIHelpers;

UI::UI(LevelManager* lvlman)
{
    lvlManager = lvlman;

    inBattle = false;
    btlScene = nullptr;
}

// Build UI
void  UI::ShowUI()
{
    int battleState = 0; // 0 = Battle Continues  |  1 = Player Lost (GameOver)  |  2 = Enemy Killed
    while (battleState != 1)
    {
        clearScreen();
        battleState = 0;

        PrintStateInfo();
        if (!inBattle)
            PrintMaze();
        else
            battleState = btlScene->BuildScene();

// 1 = Player Lost (GameOver)
        if (battleState == 1)
        {
            delete btlScene;
            btlScene = nullptr;
            break;
        }
// 2 = Enemy Killed
        else if (battleState == 2)
        {
            delete btlScene;
            btlScene = nullptr;
            continue;
        }

        if (!inBattle || (!btlScene->enemyJustAttacked && btlScene != nullptr && btlScene->TPlayerFEnemy))
            PrintUOptions();
    }

    if (battleState == 1)
        ShowGameOver();
}

// Print Maze
void  UI::PrintMaze()
{
    // Get player position, 2 = Player
    lvlManager->maze->getMazeArray()[lvlManager->player->xPos][lvlManager->player->yPos] = 2;

    // Get enemy positions, 4 = Enemy
    for(int i = 0 ; i < lvlManager->enemies.size(); i++)
        lvlManager->maze->getMazeArray()[lvlManager->enemies[i]->xPos][lvlManager->enemies[i]->yPos] = 4;

    // Print maze with objects
    for(int h = 0; h < lvlManager->maze->getMazeSizeWH().second ; h++) {
        cout << endl;

        for(int w = 0; w < lvlManager->maze->getMazeSizeWH().first ; w++)
            {
            switch ( lvlManager->maze->getMazeArray()[w][h]){
            case 0: // 0: Path
                PrintC( mazePath, 7, true);
                break;
            case 1: // 1: Wall
                PrintC( mazeWall, 7, true );
                break;
            case 2: // 2: Player
                PrintC( mazeWall, 11, true  );
                lvlManager->maze->getMazeArray()[w][h] = 0;
                break;
            case 3: // 3: Chest
                PrintC( mazeWall, 14, true );
                break;
            case 4: // 4: Enemy
                PrintC( mazeWall, 2, true );
                lvlManager->maze->getMazeArray()[w][h] = 0;
                break;
            case 5: // 5: Exit
                PrintC( mazeWall, 15, true );
                break;
            default:
                PrintC( lvlManager->maze->getMazeArray()[w][h], 7, true );
                break;
            }
        }
    }

    cout << endl;
}

// Print Timer, Scorn and Lives info
void UI::PrintStateInfo()
{
    cout << endl;
    PrintC("        Time: ");
    PrintC(to_string(lvlManager->scoretime->getTime()), 15);
    PrintC("        Score: ");
    PrintC(to_string(lvlManager->scoretime->getHScore()), 15);
    PrintC("        Lives: ");
    PrintC("3", 15);
    cout << endl;
}

// Print User Possible Options
void UI::PrintUOptions()
{
    char userOption;

    if (!inBattle)
    {
        // Draw maze bottom info
        cout << endl;
        PrintC("          ");
        PrintC(downHorizontal);
// Health
        PrintC("                      ");
        PrintC(bsLeftRightLines, 15);
        PrintC("   Health: ");
        PrintC(to_string(lvlManager->player->pHealth), 15);
        cout << endl;

        PrintC("          W          ", 15);
// Armour
        PrintC("            ");
        PrintC(bsLeftRightLines, 15);
        PrintC("    Armour: ");
        PrintC(to_string(lvlManager->player->pArmor), 15);
        cout << endl;

        PrintC("      ");
        PrintC(rightVertical);
        PrintC(" A ", 15);
        PrintC(HorizontalVertical);
        PrintC(" D ", 15);
        PrintC(leftVertical);
// Damage
        PrintC("                  ");
        PrintC(bsLeftRightLines, 15);
        PrintC("   Damage: ");
        PrintC(to_string(lvlManager->player->pDamage + lvlManager->player->pWeapon.second), 2);
        PrintC("/ ");
        PrintC(to_string(lvlManager->player->pDamage), 15);
        cout << endl;

        PrintC("          S          ", 15);
// Weapon
        PrintC("            ");
        PrintC(bsLeftRightLines, 15);
        PrintC("   Weapon: ");
        PrintC(lvlManager->player->pWeapon.first, 15);
        cout << endl;

        PrintC("          ");
        PrintC(upHorizontal);

// Keys
        PrintC("                      ");
        PrintC(bsLeftRightLines, 15);
        PrintC("     Keys: ");
        PrintC("0", 15);
        cout << endl;

// Enemy count
        PrintC("                                 ");
        PrintC(bsLeftRightLines, 15);
        PrintC("  Enemies: ");
        PrintC(to_string(lvlManager->enemies.size()), 15);

        cout << endl << endl;

        bool notvalid = true;
        while(notvalid)
        {
            PrintC("Choose option: ");
            cin >> userOption;

            if (userOption == 'b') // TEMP - TESTING
            {
                btlScene = new BattleScene(lvlManager, lvlManager->enemies[0]); // TEMP - TESTING
                notvalid = false;
            }
            else if (userOption == 'A' || userOption == 'a' || userOption == 'D' || userOption == 'd' || userOption == 'S' || userOption == 's' || userOption == 'W' || userOption == 'w')
            {
                lvlManager->player->movePlayer(userOption);
                for(Enemy* e : lvlManager->enemies)
                    lvlManager->enemyai->getNextPosition(e);

                notvalid = false;
            }
            else
            {
                PrintC(" - Not a valid option... Please choose a valid option.");
                cout << endl;
            }
        }
    }
    else
    {
        cout << endl;

// Player, Enemy - Name
        PrintC("                                                 ");
        PrintC(bsLeftRightLines, 15);
        PrintC("   ");
        string n = "<player>";
        PrintC(n, 8);
        for(int i = 0; i < 28 - n.size(); i++)
            PrintC(" ");
        PrintC(bsLeftRightLines, 15);
        PrintC("   ");
        PrintC(btlScene->enemy->getName(), 8);
        cout << endl;

// Player, Enemy - Health
        PrintC("                                                 ");
        PrintC(bsLeftRightLines, 15);
        PrintC("   ");
        PrintC("Health: ");
        string h = to_string(lvlManager->player->pHealth);
        PrintC(to_string(lvlManager->player->pHealth), 15);
        for(int i = 0; i < 20 - h.size(); i++)
            PrintC(" ");
        PrintC(bsLeftRightLines, 15);
        PrintC("   ");
        PrintC("Health: ");
        PrintC(to_string(btlScene->enemy->getHealth()), 15);
        cout << endl;

        PrintC("        Attack: ");
        PrintC("A", 15);
        PrintC("    ");
        PrintC(bsLeftRightLines, 15);
        PrintC("     Run: ");
        PrintC("R", 15);

// Player, Enemy - Armour
        PrintC("                ");
        PrintC(bsLeftRightLines, 15);
        PrintC("   ");
        PrintC("Armour: ");
        string a = to_string(lvlManager->player->pArmor);
        PrintC(to_string(lvlManager->player->pArmor), 15);
        for(int i = 0; i < 20 - a.size(); i++)
            PrintC(" ");
        PrintC(bsLeftRightLines, 15);
        PrintC("   ");
        PrintC("Armour: ");
        PrintC(to_string(btlScene->enemy->getArmour()), 15);

        cout << endl;
        PrintC("        Defend: ");
        PrintC("D", 15);
        PrintC("    ");
        PrintC(bsLeftRightLines, 15);
        PrintC("    Heal: ");
        PrintC("H", 15);

// Player, Enemy - Damage
        PrintC("                ");
        PrintC(bsLeftRightLines, 15);
        PrintC("   ");
        PrintC("Damage: ");
        string d = to_string(lvlManager->player->pDamage + lvlManager->player->pWeapon.second) + "/ " + to_string(lvlManager->player->pDamage);
        PrintC(to_string(lvlManager->player->pDamage + lvlManager->player->pWeapon.second), 2);
        PrintC("/ ");
        PrintC(to_string(lvlManager->player->pDamage), 15);
        for(int i = 0; i < 20 - d.size(); i++)
            PrintC(" ");
        PrintC(bsLeftRightLines, 15);
        PrintC("   ");
        PrintC("Damage: ");
        PrintC(to_string(btlScene->enemy->getAttackPower() + btlScene->enemy->getWeapon().second), 2);
        PrintC("/ ");
        PrintC(to_string(btlScene->enemy->getAttackPower()), 15);
        cout << endl;

// Player, Enemy - Weapon
        PrintC("                                                 ");
        PrintC(bsLeftRightLines, 15);
        PrintC("   ");
        PrintC("Weapon: ");
        string w = lvlManager->player->pWeapon.first;
        PrintC(lvlManager->player->pWeapon.first, 15);
        for(int i = 0; i < 20 - w.size(); i++)
            PrintC(" ");
        PrintC(bsLeftRightLines, 15);
        PrintC("   ");
        PrintC("Weapon: ");
        PrintC(btlScene->enemy->getWeapon().first, 15);
        cout << endl << endl;

        bool notvalid = true;
        while(notvalid)
        {
            PrintC("Choose option: ");
            cin >> userOption;

// Player attacks
            if (userOption == 'A' || userOption == 'a')
            {
                btlScene->PlayerAttack();
                notvalid = false;
            }
// Player defends
            else if (userOption == 'D' || userOption == 'd')
            {
                btlScene->PlayerDefend();
                notvalid = false;
            }
// Player heals
            else if (userOption == 'H' || userOption == 'h')
            {
                btlScene->PlayerHeal();
                notvalid = false;
            }
// Player runs
            else if (userOption == 'R' || userOption == 'r')
            {
                bool canRun = btlScene->canPlayerRun();
                if(canRun)
                {
                    inBattle = false;
                    delete btlScene;
                    btlScene = nullptr;
                }
                notvalid = false;
            }
            else
            {
                PrintC(" - Not a valid option... Please choose a valid option.");
                cout << endl;
            }
        }
    }
}

void UI::ShowGameOver()
{
    clearScreen();
    PrintC("Game Over!");
}
