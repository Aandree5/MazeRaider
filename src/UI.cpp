#include "UI.h"
#include "UIHelpers.h"
#include "Maze.h"
#include "Player.h"
#include "ScoreTime.h"
#include "LevelManager.h"
#include "BattleScene.h"
#include "Enemy.h"
#include "EnemyAI.h"
#include <cstring>

using namespace UIHelpers;

UI::UI(LevelManager* lvlman)
{
    lvlManager = lvlman;

    inBattle = false;
    btlScene = nullptr;
}

//Show player character selection screen
void UI::ShowSelectionScreen()
{
    bool selected = false;


    MYSQL *connection;
    connection = mysql_init(0);
    MYSQL_RES *result;

    mysql_real_connect(connection, "server1.jesseprescott.co.uk", "jessepre", "Mazeraider123?", "jessepre_mazeraider", 0, NULL, 0);
    if(!connection)
    {
        cout << "Failed to connect to the database." << endl;
        exit(0);
    }

    while(!selected)
    {
        clearScreen();
        cout << endl;
        PrintC("   ___  _                                                                  _                               _              ");
        cout << endl;
        PrintC(R"(  / __\| |__    ___    ___   ___   ___   _   _   ___   _   _  _ __    ___ | |__    __ _  _ __  __ _   ___ | |_  ___  _ __ )");
        cout << endl;
        PrintC(R"( / /   | '_ \  / _ \  / _ \ / __| / _ \ | | | | / _ \ | | | || '__|  / __|| '_ \  / _` || '__|/ _` | / __|| __|/ _ \| '__|)");
        cout << endl;
        PrintC(R"(/ /___ | | | || (_) || (_) |\__ \|  __/ | |_| || (_) || |_| || |    | (__ | | | || (_| || |  | (_| || (__ | |_|  __/| |  )");
        cout << endl;
        PrintC(R"(\____/ |_| |_| \___/  \___/ |___/ \___|  \__, | \___/  \__,_||_|     \___||_| |_| \__,_||_|   \__,_| \___| \__|\___||_|  )");
        cout << endl;
        PrintC(R"(                                         |___/                                                                           )");
        cout << endl;

        cout << endl << endl;

        string query = "SELECT pc.char_id, pc.name, pc.mesh, pc.health, pc.armour, pc.attack_power, w.weapon_id, "
        "w.weapon_name, w.weapon_power, w.attack_type, w.attack_colour, pc.heal_power, pc.defence_type, pc.defence_colour, pc.heal_type, pc.heal_colour "
        "FROM information i, PlayerChar pc, Weapon w WHERE i.customer_id = " + to_string(lvlManager->getPlayerID()) +
        " AND i.customer_id = pc.player_id AND pc.weapon_id = w.weapon_id "
        "ORDER BY pc.health DESC";

        if (mysql_query(connection, query.c_str()))
            cout << mysql_error(connection) << endl;

        result = mysql_store_result(connection);
        MYSQL_ROW row;

        map<int, map<string, int>> charOptions; // i count - Stats
        map<int, string> charNames; // Char id - Name
        map<int, pair<string, int>> charWeapons; // Weapon id - [Weapon name - Weapon power]
        array<string, 12> meshOptions; // 0 - 7 = Mesh | 8 = White Space | 9 = Name | 10 = Health | 11 = Weapon
        int charsPerLine = 4;
        int c = 0;
        int i = 1;
        while((row = mysql_fetch_row(result)) != NULL)
        {

// Print array to screen
            if(c >= charsPerLine)
                selCharPrintOptions(meshOptions, c);

//Mesh
            for(int line = 0; line < playerMesh[atoi(row[2])].size(); line++)
            {
                meshOptions[line] += "      " + playerMesh[atoi(row[2])][line] + "      ";
                meshOptions[line] += bsLeftRightLines;
            }


// White space between char info
            if(c >= 1)
                selCharWhiteSpaceDivider(meshOptions, c);

// Name
            meshOptions[9] += "   " + to_string(i) + ". " + row[1];

// Health
            meshOptions[10] += "   Health: " + to_string(atoi(row[3]));

// Weapon
            meshOptions[11] += "   ";
            meshOptions[11] += row[7];

            charNames[atoi(row[0])] = row[1];

            charOptions[i]["id"] = atoi(row[0]);
            charOptions[i]["mesh"] = atoi(row[2]);
            charOptions[i]["health"] = atoi(row[3]);
            charOptions[i]["armour"] = atoi(row[4]);
            charOptions[i]["attack_power"] = atoi(row[5]);
            charOptions[i]["weapon_id"] = atoi(row[6]);
            charOptions[i]["attack_type"] = atoi(row[9]);
            charOptions[i]["attack_colour"] = atoi(row[10]);
            charOptions[i]["heal_power"] = atoi(row[11]);
            charOptions[i]["defence_type"] = atoi(row[12]);
            charOptions[i]["defence_colour"] = atoi(row[13]);
            charOptions[i]["heal_type"] = atoi(row[14]);
            charOptions[i]["heal_colour"] = atoi(row[15]);

            if(charWeapons.find(atoi(row[6])) == charWeapons.end())
                charWeapons[atoi(row[6])] = make_pair(row[7], atoi(row[8]));

            c++;
            i++;
        }

// If there is still something to print on the array
        if(meshOptions[0] != "")
            selCharPrintOptions(meshOptions, c);


        int selection;
        while(true)
        {
            cout << endl;
            PrintC(to_string(i) + ". Create new character");
            cout << endl;
            PrintC(to_string(i + 1) + ". Delete character");
            cout << endl << endl;
            PrintC("Choose option: ");
            cin >> selection;

            if(selection <= 0 || selection >= i + 2)
            {
                cout << endl;
                PrintC("Please select a valid option.", 4);

            }
            else if(selection == i) // Create character
            {
                selCharCreateNew(connection);
                break;
            }
            else if(selection == i + 1) // Delete character
            {
                int c;
                cout << endl;
                PrintC("Select character: ");
                cin >> c;

                if(c <= 0 || c > i)
                {
                    cout << endl;
                    PrintC("Please select a valid character.", 4);
                    continue;
                }

                selCharDelete(connection, charOptions[c]["id"], charNames[charOptions[c]["id"]]);
                break;
            }
            else
            {
                lvlManager->player->pCharID = charOptions[selection]["id"];
                lvlManager->player->pName = charNames[charOptions[selection]["id"]];
                lvlManager->player->pMesh = charOptions[selection]["mesh"];
                lvlManager->player->pHealth = charOptions[selection]["health"];
                lvlManager->player->pDamage = charOptions[selection]["attack_power"];
                lvlManager->player->pArmour = charOptions[selection]["armour"];
                lvlManager->player->pWeapon = charWeapons[charOptions[selection]["weapon_id"]];
                lvlManager->player->pHealPower = charOptions[selection]["heal_power"];
                lvlManager->player->pAttackType = charOptions[selection]["attack_type"];
                lvlManager->player->pAttackColour = charOptions[selection]["attack_colour"];
                lvlManager->player->pDefenceType = charOptions[selection]["defence_type"];
                lvlManager->player->pDefenceColour = charOptions[selection]["defence_colour"];
                lvlManager->player->pHealType = charOptions[selection]["heal_type"];
                lvlManager->player->pHealColour = charOptions[selection]["heal_colour"];

                selected = true;
                break;
            }
        }
    }

}

// Print array to screen
void UI::selCharPrintOptions(array<string, 12> &mOptions, int &c)
{
    selCharWhiteSpaceDivider(mOptions, c);

    for(int l = 0; l < mOptions.size(); l++)
    {
        if(l >= mOptions.size() - 2)
            PrintC(mOptions[l], 8);
        else
            PrintC(mOptions[l]);

        cout << endl;
        mOptions[l] = "";
    }

    cout << endl << endl;
    c = 0;
}

// White space between char info
void UI::selCharWhiteSpaceDivider(array<string, 12> &mOptions, int c)
{
    int s = ((28 * c) - mOptions[9].size() + c) - 1;
    for(int w = 0; w < s; w++)
        mOptions[9] += " ";

    s = ((28 * c) - mOptions[10].size() + c) - 1;
    for(int w = 0; w < s; w++)
        mOptions[10] += " ";

    s = ((28 * c) - mOptions[11].size() + c) - 1;
    for(int w = 0; w < s; w++)
        mOptions[11] += " ";

    mOptions[9] += bsLeftRightLines;
    mOptions[10] += bsLeftRightLines;
    mOptions[11] += bsLeftRightLines;

}

// Screen to create character
void UI::selCharCreateNew(MYSQL *connection)
{
    clearScreen();

    string query = "SELECT weapon_id, weapon_name, weapon_power FROM Weapon ORDER BY RAND() LIMIT 1";

    if (mysql_query(connection, query.c_str()))
        cout << mysql_error(connection) << endl;

    MYSQL_RES *result = mysql_store_result(connection);
    MYSQL_ROW row = mysql_fetch_row(result);

    // Randomize stats
    string name;
    int mesh;
    int health = rand() % 200 + 90;      // 90 - 200
    int armour = rand() % 10;            // 0 - 9
    int attack_power = rand() % 30 + 10; // 10 - 29
    int weapon_id = atoi(row[0]);
    int heal_power = rand() % 20;        // 0 - 19
    int defenceType = rand() % 2;        // 0 - 1
    int defenceColour = rand() % 16 + 1; // 1 - 15
    int healType = rand() % 2;           // 0 - 1
    int healColour = rand() % 16 + 1;    // 1 - 15

    // Show random stats
    cout << endl;
    PrintC("   -----------------------");
    cout << endl;

    PrintC("   Health: ", 8);
    PrintC(to_string(health), 15);
    cout << endl;
    PrintC("   Armour: ", 8);
    PrintC(to_string(armour), 15);
    cout << endl;
    PrintC("   Damage: ", 8);
    PrintC(to_string(attack_power + atoi(row[2])), 15);
    PrintC("/ " + to_string(attack_power), 8);
    cout << endl;
    PrintC("   Weapon: ", 8);
    PrintC(row[1], 15);
    cout << endl;
    PrintC("   Heal Power: ", 8);
    PrintC(to_string(heal_power), 15);

    cout << endl;
    PrintC("   -----------------------");
    cout << endl << endl;

    // Show meshes
    for(int i = 0; i < 8; i++) // Lines to print
    {
        for(int a = 0; a < playerMesh.size(); a++) // Number character mesh
            PrintC("   " + playerMesh[a][i] + "       ");

        cout << endl;
    }

    // Show choice numbers
    for(int i = 1; i <= playerMesh.size(); i++)
    {
        string number = "  " + to_string(i) + ". ";
        PrintC(number);
        for(int w = 0; w <= (25 - number.size()); w++)
            PrintC(" ");
    }
    cout << endl;

    while(true)
    {
        PrintC("Choose character: ");
        cin >> mesh;
        cout << endl;
        if(mesh > 0 && mesh <= playerMesh.size())
            break;

        PrintC("Please choose a valid character.", 4);
        cout << endl;
    }

    PrintC("Character name: ");
    cin >> name;
    cout << endl;

    string createQuery = "INSERT INTO PlayerChar(player_id, name, mesh, health, armour, attack_power, "
    "weapon_id, heal_power, defence_type, defence_colour, heal_type, heal_colour) "
    "VALUES (" + to_string(lvlManager->getPlayerID()) +", '" + name + "', " + to_string(mesh - 1) + ", " + to_string(health) +
    ", " + to_string(armour) + ", " + to_string(attack_power) + ", " + to_string(weapon_id) + ", " + to_string(heal_power) +
    ", " + to_string(defenceType) + ", " + to_string(defenceColour) + ", " + to_string(healType) + ", " +
    to_string(healColour) +");";

    if (mysql_query(connection, createQuery.c_str()))
        cout << mysql_error(connection) << endl;
    else
        PrintC(name + " created.");

    Sleep(1000);
}

// Delete character
void UI::selCharDelete(MYSQL *connection, int charID, string name)
{
    string deleteQuery = "DELETE FROM PlayerChar WHERE char_id = " + to_string(charID);
    string safety;

    PrintC("ARE YOU 100% SURE YOU WANT TO DELETE -> " + name + " [y/n]: ");
    cin >> safety;
    cout << endl;

    if(toLower(safety) != "y" && toLower(safety) != "yes")
    {
        PrintC("Good you thought twice :)");
        Sleep(1000);
        return;
    }

    PrintC("It's sad to see " + name + " go... :(", 15);
    cout << endl;

    if (mysql_query(connection, deleteQuery.c_str()))
        cout << mysql_error(connection) << endl;
    else
        PrintC(name + " deleted.");

    Sleep(1000);
}


// Build UI
void  UI::ShowUI()
{
    int battleState = 0; // 0 = Battle Continues  |  1 = Player Lost (GameOver)  |  2 = Enemy Killed
    while (battleState != 1 && !lvlManager->exitToMenu)
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
    for(unsigned i = 0 ; i < lvlManager->enemies.size(); i++)
        lvlManager->maze->getMazeArray()[lvlManager->enemies[i]->xPos][lvlManager->enemies[i]->yPos] = 4;

    // Print maze with objects
    for(unsigned h = 0; h < lvlManager->maze->getMazeSizeWH().second ; h++) {
        cout << endl;

        for(unsigned w = 0; w < lvlManager->maze->getMazeSizeWH().first ; w++)
            {
            switch ( lvlManager->maze->getMazeArray()[w][h]){
            case 0: // 0: Path
                PrintC( mazePath, 7, true);
                break;
            case 1: // 1: Wall
                if(w == 0 || h == 0 || w == lvlManager->maze->getMazeSizeWH().first - 1
                   || h == lvlManager->maze->getMazeSizeWH().second - 1)
                    PrintC(mazeWall, 7, true);
                else
                    PrintC(mazeWall, 7, true, true );

                break;
            case 2: // 2: Player
                PrintC(mazeWall, 11, true);
                lvlManager->maze->getMazeArray()[w][h] = 0;
                break;
            case 3: // 3: Chest
                PrintC(mazeWall, 14, true);
                break;
            case 4: // 4: Enemy
                PrintC(mazeWall, 2, true);
                lvlManager->maze->getMazeArray()[w][h] = 0;
                break;
            case 5: // 5: Exit
                PrintC(mazeWall, 15, true);
                break;
            default:
                PrintC(lvlManager->maze->getMazeArray()[w][h], 7, true);
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
    PrintC((lvlManager->scoretime->getTime()), 15);
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
// Character name
        PrintC("                                 ");
        PrintC(playerMesh[lvlManager->player->pMesh][0]);
        cout << endl;
        PrintC("                                 ");
        PrintC(playerMesh[lvlManager->player->pMesh][1]);
        PrintC(bsLeftRightLines, 15);
        PrintC("      ");
        PrintC(lvlManager->player->pName, lvlManager->player->pAttackColour);

        cout << endl;
        PrintC("          ");
        PrintC(downHorizontal);
// Health
        PrintC("                      ");
        PrintC(playerMesh[lvlManager->player->pMesh][2]);
        PrintC(bsLeftRightLines, 15);
        PrintC("   Health: ");
        PrintC(to_string(lvlManager->player->pHealth), 15);
        cout << endl;

        PrintC("          W          ", 15);
// Armour
        PrintC("            ");
        PrintC(playerMesh[lvlManager->player->pMesh][3]);
        PrintC(bsLeftRightLines, 15);
        PrintC("    Armour: ");
        PrintC(to_string(lvlManager->player->pArmour), 15);
        cout << endl;

        PrintC("      ");
        PrintC(rightVertical);
        PrintC(" A ", 15);
        PrintC(HorizontalVertical);
        PrintC(" D ", 15);
        PrintC(leftVertical);
// Damage
        PrintC("                  ");
        PrintC(playerMesh[lvlManager->player->pMesh][4]);
        PrintC(bsLeftRightLines, 15);
        PrintC("   Damage: ");
        PrintC(to_string(lvlManager->player->pDamage + lvlManager->player->pWeapon.second), 15);
        PrintC("/ ");
        PrintC(to_string(lvlManager->player->pDamage));
        cout << endl;

        PrintC("          S          ", 15);
// Weapon
        PrintC("            ");
        PrintC(playerMesh[lvlManager->player->pMesh][5]);
        PrintC(bsLeftRightLines, 15);
        PrintC("   Weapon: ");
        PrintC(lvlManager->player->pWeapon.first, 15);
        cout << endl;
        PrintC("          ");
        PrintC(upHorizontal);

// Keys
        PrintC("                      ");
        PrintC(playerMesh[lvlManager->player->pMesh][6]);
        PrintC(bsLeftRightLines, 15);
        PrintC("     Keys: ");
        PrintC("0", 15);
        cout << endl;

// Enemy count
        PrintC("                                 ");
        PrintC(playerMesh[lvlManager->player->pMesh][7]);
        PrintC(bsLeftRightLines, 15);
        PrintC("  Enemies: ");
        PrintC(to_string(lvlManager->enemies.size()), 15);

        cout << endl;

        if(lvlManager->isPaused)
        {
            int mazeW = lvlManager->maze->getMazeSizeWH().first * 2;
            int mazeH = lvlManager->maze->getMazeSizeWH().second;

            buildPause(lvlManager, mazeW - (mazeW / 2), (mazeH - (mazeH / 2)) + 3);
        }
        else
        {
            userOption = requestFromUser<char>(lvlManager);

            if (lvlManager->isPaused)
                return;

            //quit the game
            if (userOption == 'e'){
                lvlManager->scoretime->savehighscore();
                lvlManager->scoretime->makeHighscoreTable();
            }

            if (userOption == 'b') // TEMP - TESTING
            {
                btlScene = new BattleScene(lvlManager, lvlManager->enemies[0]); // TEMP - TESTING
            }
            else if(tolower(userOption) == 'a' || tolower(userOption) == 'd' || tolower(userOption) == 's' || tolower(userOption) == 'w')
            {
                lvlManager->player->movePlayer(userOption);
                if(lvlManager->enemies.size())
                    for(Enemy* e : lvlManager->enemies)
                        lvlManager->enemyai->getNextPosition(e);

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
        string n = lvlManager->player->pName;
        PrintC(n, 8);
        for(unsigned i = 0; i < 33 - n.size(); i++)
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
        for(unsigned i = 0; i < 25 - h.size(); i++)
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
        string a = to_string(lvlManager->player->pArmour);
        PrintC(to_string(lvlManager->player->pArmour), 15);
        for(unsigned i = 0; i < 25 - a.size(); i++)
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
        PrintC(to_string(lvlManager->player->pDamage + lvlManager->player->pWeapon.second), 15);
        PrintC("/ ");
        PrintC(to_string(lvlManager->player->pDamage));
        for(unsigned i = 0; i < 25 - d.size(); i++)
            PrintC(" ");
        PrintC(bsLeftRightLines, 15);
        PrintC("   ");
        PrintC("Damage: ");
        PrintC(to_string(btlScene->enemy->getAttackPower() + btlScene->enemy->getWeapon().second), 15);
        PrintC("/ ");
        PrintC(to_string(btlScene->enemy->getAttackPower()));
        cout << endl;

// Player, Enemy - Weapon
        PrintC("                                                 ");
        PrintC(bsLeftRightLines, 15);
        PrintC("   ");
        PrintC("Weapon: ");
        string w = lvlManager->player->pWeapon.first;
        PrintC(lvlManager->player->pWeapon.first, 15);
        for(unsigned i = 0; i < 25 - w.size(); i++)
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
            if (tolower(userOption) == 'a')
            {
                btlScene->PlayerAttack();
                notvalid = false;
            }
// Player defends
            else if (tolower(userOption) == 'd')
            {
                btlScene->PlayerDefend();
                notvalid = false;
            }

// Player heals
            else if (tolower(userOption) == 'h')
            {
                btlScene->PlayerHeal();
                notvalid = false;
            }
// Player runs
            else if (tolower(userOption) == 'r')
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


// Overload for UIHelpers PrintC function for pausing game
void UI::PrintC(char character, int colour, bool twoChar, bool hideWhenPaused)
{
    if(lvlManager->isPaused && !hideWhenPaused)
        colour = 8;
    else if (lvlManager->isPaused)
        colour = 0;

    UIHelpers::PrintC(character, colour, twoChar);
}

// Overload for UIHelpers PrintC function for pausing game
void UI::PrintC(string character, int colour, bool twoChar, bool hideWhenPaused)
{
    if(lvlManager->isPaused && !hideWhenPaused)
        colour = 8;
    else if (lvlManager->isPaused)
        colour = 0;

    UIHelpers::PrintC(character, colour, twoChar);
}

void UI::ShowNextLevel()
{
   clearScreen();
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
            PrintC("Choose option: ");
            cin >> userOption;

// Player choose low difficulty .
            if (tolower(userOption) == 'l' )
            {

                lvlManager->lowLevel();
            }
// Player choose medium difficulty .
            else if (tolower(userOption) == 'm')
            {
                lvlManager->mediumLevel();
            }
// Player choose high difficulty .
            else if (tolower(userOption) == 'h')
            {
                lvlManager->highLevel();
            }
// Player lets the computer to choose the difficulty
               else if (tolower(userOption) == 'c')
            {
                lvlManager->nextLevel();
            }
            else
            {
                PrintC(" - Not a valid option... Please choose a valid option.");
                cout << endl;
            }
        }
}
