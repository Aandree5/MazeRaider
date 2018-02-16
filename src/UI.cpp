#include "UI.h"
#include "UIHelpers.h"
#include "Maze.h"
#include "Player.h"
#include "ScoreTime.h"
#include "LevelManager.h"
#include "BattleScene.h"
#include "Enemy.h"

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
        lvlManager->maze->getMazeArray()[lvlManager->enemies[i]->xPosEnemy][lvlManager->enemies[i]->yPosEnemy] = 4;

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
    cout << "Timer: " << lvlManager->scoretime->getTime() << "           Score: " << lvlManager->scoretime->getHScore() << "            Lives: 3/3" << endl << endl;
}

// Print User Possible Options
void UI::PrintUOptions()
{
    char userOption;

    if (!inBattle)
    {
        cout << endl << endl << "Choose option:    w - Up       a - Left        d - Right        s - Down" << endl;

        bool notvalid = true;
        while(notvalid)
        {
            cin >> userOption;

            if (userOption == 'b') // TEMP - TESTING
            {
                btlScene = new BattleScene(lvlManager, lvlManager->enemies[0]); // TEMP - TESTING
                notvalid = false;
            }
            else if (userOption == 'A' || userOption == 'a' || userOption == 'D' || userOption == 'd' || userOption == 'S' || userOption == 's' || userOption == 'W' || userOption == 'w')
            {
                lvlManager->player->movePlayer(userOption);
                notvalid = false;
            }
            else
                cout << " - Not a valid option... Please choose a valid option." << endl;
        }
    }
    else
    {
        cout << endl;
        cout << "Attack:    a        Defend:    d" << endl;
        cout << "  Heal:    h           Run:    r" << endl;

        bool notvalid = true;
        while(notvalid)
        {
            cin >> userOption;

// Player attacks
            if (userOption == 'A' || userOption == 'a')
            {
                btlScene->PlayerAttack(1, 10, 10);
                notvalid = false;
            }
// Player defends
            else if (userOption == 'D' || userOption == 'd')
            {
                btlScene->PlayerDefend(0, 3);
                notvalid = false;
            }
// Player heals
            else if (userOption == 'H' || userOption == 'h')
            {
                btlScene->PlayerHeal(0, 2, 10);
                notvalid = false;
            }
// Player runs
            else if (userOption == 'R' || userOption == 'r')
            {
                inBattle = false;
                delete btlScene;
                btlScene = nullptr;
                notvalid = false;
            }
            else
                cout << " - Not a valid option... Refer back to the option shown on screen please." << endl;
        }
    }
}

void UI::ShowGameOver()
{
    clearScreen();
    cout << "Game Over!";
}
