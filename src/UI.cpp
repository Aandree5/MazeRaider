#include "UI.h"
#include "Maze.h"
#include "Player.h"
#include "ScoreTime.h"
#include "LevelManager.h"
#include "BattleScene.h"
#include "Enemy.h"
#include "EnemyAI.h"
#include <cstring>

using namespace UIHelpers;

UI::UI(shared_ptr<LevelManager> lvlman)
{
    lvlManager = lvlman;

    inBattle = false;

    mazeInfo[mazeInfo.size() - 1] = make_pair("You just want to leave!", MessageType::General);
}

// Build UI
void  UI::ShowUI()
{
    int battleState = 0; // 0 = Battle Continues  |  1 = Player Lost (GameOver)  |  2 = Enemy Killed
    while (battleState != 1 && !lvlManager.lock()->exitToMenu)
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
            break;
    // 2 = Enemy Killed
        else if (battleState == 2)
        {
            if(lvlManager.lock()->enemies.size() > 0)
                UpdateMessageInfo(mazeInfo, "You defeated the enemy!", MessageType::Victory);
            else
                UpdateMessageInfo(mazeInfo, "You defeated all enemies!!", MessageType::Victory);

            continue;
        }

        if (!inBattle || (!btlScene->enemyJustAttacked && btlScene->TPlayerFEnemy))
            PrintUOptions();
    }

    if (battleState == 1)
        ShowGameOver();
}

// Print Maze
void  UI::PrintMaze()
{
    if(shared_ptr<LevelManager> lvlman = lvlManager.lock())
    {
        lvlman->changeMusic(LevelManager::Music::Map);

        // Get enemy positions, 4 = Enemy
        for(unsigned i = 0 ; i < lvlman->enemies.size(); i++)
            lvlman->maze->getMazeArray()[lvlman->enemies[i]->xPos][lvlman->enemies[i]->yPos] = 4;

        // Get player position, 2 = Player
        lvlman->maze->getMazeArray()[lvlman->player->xPos][lvlman->player->yPos] = 2;

        // Print maze with objects
        for(unsigned h = 0; h < lvlman->maze->getMazeSizeWH().second ; h++) {
            cout << endl;

            for(unsigned w = 0; w < lvlman->maze->getMazeSizeWH().first ; w++)
                {
                switch ( lvlman->maze->getMazeArray()[w][h]){
                case 0: // 0: Path
                    PrintC( mazePath, 7, true);
                    break;
                case 1: // 1: Wall
                    if(w == 0 || h == 0 || w == lvlman->maze->getMazeSizeWH().first - 1
                       || h == lvlman->maze->getMazeSizeWH().second - 1)
                        PrintC(mazeWall, 7, true);
                    else
                        PrintC(mazeWall, 7, true, true );

                    break;
                case 2: // 2: Player
                    PrintC(mazePlayer, 185, true);
                    lvlman->maze->getMazeArray()[w][h] = 0;
                    break;
                case 3: // 3: Chest
                    PrintC(mazeChest, 232, true);
                    break;
                case 4: // 4: Enemy
                    PrintC(mazeEnemy, 196, true);
                    lvlman->maze->getMazeArray()[w][h] = 0;
                    break;
                case 5: // 5: Exit
                    PrintC(mazePath, true);
                    break;
                default:
                    PrintC(to_string(lvlman->maze->getMazeArray()[w][h]), 7, true);
                    break;
                }
            }
        }

        cout << endl;
    }
}

// Print Timer, Scorn and Lives info
void UI::PrintStateInfo()
{
    if(shared_ptr<LevelManager> lvlman = lvlManager.lock())
    {
        cout << endl;
        PrintC("  (P)", 15);
        PrintC(" Pause Menu");
        PrintC("     Time: ");
        PrintC(lvlman->scoretime->getTime(), 15);
        PrintC("        Score: ");
        PrintC(to_string(lvlman->scoretime->getHScore()), 15);
        PrintC("        Lives: ");
        PrintC("3", 15);
        if(lvlman->isMuted)
            PrintC("      Sound Muted", 15);
        cout << endl;
    }
}

// Print User Possible Options
void UI::PrintUOptions()
{
    if(shared_ptr<LevelManager> lvlman = lvlManager.lock())
    {

        char userOption;

        if (!inBattle)
        {
    // Character name
            PrintC("                                 ");
            PrintC(playerMesh[lvlman->player->pMesh][0]);
            cout << endl;
            PrintC("                                 ");
            PrintC(playerMesh[lvlman->player->pMesh][1]);
            PrintC(bsLeftRightLines, 15);
            PrintC("      ");
            PrintC(lvlman->player->pName, lvlman->player->pAttackColour);

            cout << endl;
            PrintC("          ");
            PrintC(downHorizontal);
    // Health
            PrintC("                      ");
            PrintC(playerMesh[lvlman->player->pMesh][2]);
            PrintC(bsLeftRightLines, 15);
            PrintC("   Health: ");
            PrintC(to_string(lvlman->player->pHealth), 15);
            cout << endl;

            PrintC("          W          ", 15);
    // Armour
            PrintC("            ");
            PrintC(playerMesh[lvlman->player->pMesh][3]);
            PrintC(bsLeftRightLines, 15);
            PrintC("    Armour: ");
            PrintC(to_string(lvlman->player->pArmour), 15);
            cout << endl;

            PrintC("      ");
            PrintC(rightVertical);
            PrintC(" A ", 15);
            PrintC(HorizontalVertical);
            PrintC(" D ", 15);
            PrintC(leftVertical);
    // Damage
            PrintC("                  ");
            PrintC(playerMesh[lvlman->player->pMesh][4]);
            PrintC(bsLeftRightLines, 15);
            PrintC("   Damage: ");
            PrintC(to_string(lvlman->player->pDamage + lvlman->player->pWeapon.second), 15);
            PrintC("/ ");
            PrintC(to_string(lvlman->player->pDamage));
            cout << endl;

            PrintC("          S          ", 15);
    // Weapon
            PrintC("            ");
            PrintC(playerMesh[lvlman->player->pMesh][5]);
            PrintC(bsLeftRightLines, 15);
            PrintC("   Weapon: ");
            PrintC(lvlman->player->pWeapon.first, 15);
            cout << endl;
            PrintC("          ");
            PrintC(upHorizontal);

    // Keys
            PrintC("                      ");
            PrintC(playerMesh[lvlman->player->pMesh][6]);
            PrintC(bsLeftRightLines, 15);
            PrintC("     Keys: ");
            PrintC("0", 15);
            cout << endl;

    // Enemy count
            PrintC("                                 ");
            PrintC(playerMesh[lvlman->player->pMesh][7]);
            PrintC(bsLeftRightLines, 15);
            PrintC("  Enemies: ");
            PrintC(to_string(lvlman->enemies.size()), 15);

            cout << endl;
            PrintC(bsTopLeftCorner, 8);
            for(int i = 0; i < 70; i++)
                PrintC(bsTopBottomLines, 8);
            cout << endl;

            for(int i = 0; i < mazeInfo.size(); i++)
            {
                if(i == mazeInfo.size() - 1)
                {
                    PrintC(bsLeftRightLines, 15);
                    PrintC(" ");
                    switch(mazeInfo[i].second)
                    {
                    case MessageType::PickUp:
                        PrintC(" " + mazeInfo[i].first, 14);
                        break;
                    case MessageType::Enemy:
                        PrintC(" " + mazeInfo[i].first, 12);
                        break;
                    case MessageType::General:
                        PrintC(" " + mazeInfo[i].first, 15);
                        break;
                    case MessageType::Victory:
                        PrintC(" " + mazeInfo[i].first, 10);
                        break;
                    }

                }
                else
                {
                    PrintC(bsLeftRightLines, 8);
                    PrintC(" ");
                    switch(mazeInfo[i].second)
                    {
                    case MessageType::PickUp:
                        PrintC(" " + mazeInfo[i].first, 6);
                        break;
                    case MessageType::Enemy:
                        PrintC(" " + mazeInfo[i].first, 4);
                        break;
                    case MessageType::General:
                        PrintC(" " + mazeInfo[i].first, 8);
                        break;
                    case MessageType::Victory:
                        PrintC(" " + mazeInfo[i].first, 2);
                        break;
                    }
                }

                cout << endl;
            }

            if(lvlman->isPaused)
            {
                int mazeW = lvlman->maze->getMazeSizeWH().first * 2;
                int mazeH = lvlman->maze->getMazeSizeWH().second;

                BuildPause(lvlman, mazeW - (mazeW / 2), (mazeH - (mazeH / 2)) + 3);
            }
            else
            {
                cout << endl;
                userOption = requestFromUser<char>(lvlman);

                if (lvlman->isPaused)
                    return;

                //quit the game
                if (userOption == 'e'){
                    lvlman->scoretime->savehighscore();
                    lvlman->scoretime->makeHighscoreTable();
                }

                if (userOption == 'b') // TEMP - TESTING
                {
                    StartBattleScene(lvlman->enemies[0]); // TEMP - TESTING
                }
                else if(tolower(userOption) == 'a' || tolower(userOption) == 'd' || tolower(userOption) == 's' || tolower(userOption) == 'w')
                {
                    lvlman->player->movePlayer(userOption);
                    if(inBattle)
                        return;

                    bool enemyFollowing = false;
                    for(shared_ptr<Enemy> e : lvlman->enemies)
                    {
                        lvlman->enemyai->getNextPosition(e);
                        if(e->followingPlayer)
                            enemyFollowing = true;
                    }

                    string m = "Nice, the enemy has lost you!";
                    if(mazeInfo[mazeInfo.size() - 1].first != m)
                        if(!enemyFollowing)
                            UpdateMessageInfo(mazeInfo, m, MessageType::General);

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
            if(shared_ptr<Enemy> bScE = btlScene->enemy.lock())
            {
                 cout << endl;

        // Player, Enemy - Name
                PrintC("                                                 ");
                PrintC(bsLeftRightLines, 15);
                PrintC("   ");
                string n = lvlman->player->pName;
                PrintC(n, 8);
                for(unsigned i = 0; i < 33 - n.size(); i++)
                    PrintC(" ");
                PrintC(bsLeftRightLines, 15);
                PrintC("   ");
                PrintC(bScE->getName(), 8);
                cout << endl;

        // Player, Enemy - Health
                PrintC("                                                 ");
                PrintC(bsLeftRightLines, 15);
                PrintC("   ");
                PrintC("Health: ");
                string h = to_string(lvlman->player->pHealth);
                PrintC(to_string(lvlman->player->pHealth), 15);
                for(unsigned i = 0; i < 25 - h.size(); i++)
                    PrintC(" ");
                PrintC(bsLeftRightLines, 15);
                PrintC("   ");
                PrintC("Health: ");
                PrintC(to_string(bScE->getHealth()), 15);
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
                string a = to_string(lvlman->player->pArmour);
                PrintC(to_string(lvlman->player->pArmour), 15);
                for(unsigned i = 0; i < 25 - a.size(); i++)
                    PrintC(" ");
                PrintC(bsLeftRightLines, 15);
                PrintC("   ");
                PrintC("Armour: ");
                PrintC(to_string(bScE->getArmour()), 15);

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
                string d = to_string(lvlman->player->pDamage + lvlman->player->pWeapon.second) + "/ " +
                to_string(lvlman->player->pDamage);
                PrintC(to_string(lvlman->player->pDamage + lvlman->player->pWeapon.second), 15);
                PrintC("/ ");
                PrintC(to_string(lvlman->player->pDamage));
                for(unsigned i = 0; i < 25 - d.size(); i++)
                    PrintC(" ");
                PrintC(bsLeftRightLines, 15);
                PrintC("   ");
                PrintC("Damage: ");
                PrintC(to_string(bScE->getAttackPower() + bScE->getWeapon().second), 15);
                PrintC("/ ");
                PrintC(to_string(bScE->getAttackPower()));
                cout << endl;

        // Player, Enemy - Weapon
                PrintC("                                                 ");
                PrintC(bsLeftRightLines, 15);
                PrintC("   ");
                PrintC("Weapon: ");
                string w = lvlman->player->pWeapon.first;
                PrintC(lvlman->player->pWeapon.first, 15);
                for(unsigned i = 0; i < 25 - w.size(); i++)
                    PrintC(" ");
                PrintC(bsLeftRightLines, 15);
                PrintC("   ");
                PrintC("Weapon: ");
                PrintC(bScE->getWeapon().first, 15);
                cout << endl << endl;


                if(lvlman->isPaused)
                {
                    int sceneW = btlScene->getSceneSizeWH().first;
                    int sceneH = btlScene->getSceneSizeWH().second;

                    BuildPause(lvlman, sceneW - (sceneW / 2), (sceneH - (sceneH / 2)) + 3);
                }
                else
                {
                    userOption = requestFromUser<char>(lvlman);

                    if (lvlman->isPaused)
                        return;


        // Player attacks
                    if (tolower(userOption) == 'a')
                    {
                        btlScene->PlayerAttack();
                    }
        // Player defends
                    else if (tolower(userOption) == 'd')
                    {
                        btlScene->PlayerDefend();
                    }

        // Player heals
                    else if (tolower(userOption) == 'h')
                    {
                        btlScene->PlayerHeal();
                    }
        // Player runs
                    else if (tolower(userOption) == 'r')
                    {
                        if(btlScene->canPlayerRun())
                            inBattle = false;
                    }
                }
            }
        }
    }
}

void UI::ShowGameOver()
{
    lvlManager.lock()->playEffect(LevelManager::Effect::LevelLost);
    clearScreen();
    PrintC("Game Over!");

}

void UI::StartBattleScene(shared_ptr<Enemy> enemy)
{
    if(!inBattle)
        btlScene = make_unique<BattleScene>(lvlManager.lock(), enemy);
}

// Overload for UIHelpers PrintC function for pausing game
void UI::PrintC(char character, int colour, bool twoChar, bool hideWhenPaused)
{
    if(shared_ptr<LevelManager> lvlman = lvlManager.lock())
    {
        if(lvlman->isPaused && !hideWhenPaused)
            colour = 8;
        else if (lvlman->isPaused)
            colour = 0;

        UIHelpers::PrintC(character, colour, twoChar);
    }
}

// Overload for UIHelpers PrintC function for pausing game
void UI::PrintC(string character, int colour, bool twoChar, bool hideWhenPaused)
{
    if(shared_ptr<LevelManager> lvlman = lvlManager.lock())
    {
        if(lvlman->isPaused && !hideWhenPaused)
            colour = 8;
        else if (lvlman->isPaused)
            colour = 0;

        UIHelpers::PrintC(character, colour, twoChar);
    }
}

void UI::ShowNextLevel()
{
    if(shared_ptr<LevelManager> lvlman = lvlManager.lock())
    {
        lvlman->playEffect(LevelManager::Effect::LevelPassed);
        clearScreen();

       lvlman->scoretime->savehighscore();
       lvlman->scoretime->makeHighscoreTable();

       cout << endl;

        PrintC("You've finished your level. Choose the difficulty for the next level OR computer can choose for you");
        cout << endl;

        PrintC("        Low: ");
        PrintC("L", 15);
        PrintC("    ");
        PrintC(bsLeftRightLines, 15);
        PrintC("    Medium: ");
        PrintC("M", 15);
        PrintC("    ");
        PrintC(bsLeftRightLines, 15);
        PrintC("    Hard: ");
        PrintC("H", 15);
        PrintC("    ");
        PrintC(bsLeftRightLines, 15);
        PrintC("    Computer : ");
        PrintC("C", 15);
        PrintC("    ");
        char userOption;
        cout << endl;
        bool notvalid = true;
        while(notvalid)
        {
            userOption = requestFromUser<char>();

    // Player choose low difficulty .
            if (tolower(userOption) == 'l' )
            {
                lvlman->lowLevel();
                notvalid = false;
            }
    // Player choose medium difficulty .
            else if (tolower(userOption) == 'm')
            {
                lvlman->mediumLevel();
                notvalid = false;
            }
    // Player choose high difficulty .
            else if (tolower(userOption) == 'h')
            {
                lvlman->highLevel();
                notvalid = false;
            }
    // Player lets the computer to choose the difficulty
            else if (tolower(userOption) == 'c')
            {
                lvlman->nextLevel();
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
