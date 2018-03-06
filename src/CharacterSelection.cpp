#include "CharacterSelection.h"
#include "UI.h"
#include "Player.h"
#include "UIHelpers.h"

using namespace UIHelpers;

CharacterSelection::CharacterSelection(shared_ptr<LevelManager> lvlman)
{
    lvlManager = lvlman;
}

//Show player character selection screen
void CharacterSelection::ShowSelectionScreen()
{
    if(shared_ptr<LevelManager> lvlman = lvlManager.lock())
    {
        lvlman->changeMusic(LevelManager::Music::SelectionScreen);

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

            string query = SQLPrepare("SELECT pc.char_id, pc.name, pc.mesh, pc.health, pc.armour, pc.attack_power, w.weapon_id, "
            "w.weapon_name, w.weapon_power, w.attack_type, w.attack_colour, pc.heal_power, pc.defence_type, pc.defence_colour, pc.heal_type, pc.heal_colour "
            "FROM user_info i, PlayerChar pc, Weapon w WHERE i.user_id = %? AND i.user_id = pc.player_id AND pc.weapon_id = w.weapon_id "
            "ORDER BY pc.health DESC", lvlman->getPlayerID());

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
                for(unsigned line = 0; line < lvlman->ui->playerMesh[atoi(row[2])].size(); line++)
                {
                    meshOptions[line] += "      " + lvlman->ui->playerMesh[atoi(row[2])][line] + "      ";
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



            cout << endl;
            PrintC(to_string(i) + ". Create new character");
            cout << endl;
            PrintC(to_string(i + 1) + ". Delete character");
            cout << endl << endl;

            int selection;
            selection = requestFromUser<int>("Choose an option: ", 1, i + 2);


            if(selection == i) // Create character
                selCharCreateNew(connection);

            else if(selection == i + 1) // Delete character
            {
                int c;
                cout << endl;
                c = requestFromUser<int>(lvlman, "Select character: ", 1, i + 1);

                selCharDelete(connection, charOptions[c]["id"], charNames[charOptions[c]["id"]]);
            }
            else
            {
                lvlman->player->pCharID = charOptions[selection]["id"];
                lvlman->player->pName = charNames[charOptions[selection]["id"]];
                lvlman->player->pMesh = charOptions[selection]["mesh"];
                lvlman->player->pHealth = charOptions[selection]["health"];
                lvlman->player->pDamage = charOptions[selection]["attack_power"];
                lvlman->player->pArmour = charOptions[selection]["armour"];
                lvlman->player->pWeapon = charWeapons[charOptions[selection]["weapon_id"]];
                lvlman->player->pHealPower = charOptions[selection]["heal_power"];
                lvlman->player->pAttackType = charOptions[selection]["attack_type"];
                lvlman->player->pAttackColour = charOptions[selection]["attack_colour"];
                lvlman->player->pDefenceType = charOptions[selection]["defence_type"];
                lvlman->player->pDefenceColour = charOptions[selection]["defence_colour"];
                lvlman->player->pHealType = charOptions[selection]["heal_type"];
                lvlman->player->pHealColour = charOptions[selection]["heal_colour"];

                selected = true;
                break;
            }
        }
    }
}


// Print array to screen
void CharacterSelection::selCharPrintOptions(array<string, 12> &mOptions, int &c)
{
    selCharWhiteSpaceDivider(mOptions, c);

    for(unsigned l = 0; l < mOptions.size(); l++)
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
void CharacterSelection::selCharWhiteSpaceDivider(array<string, 12> &mOptions, int &c)
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
void CharacterSelection::selCharCreateNew(MYSQL *connection)
{
    if(shared_ptr<LevelManager> lvlman = lvlManager.lock())
    {
        clearScreen();

        // Get a random weapon from database
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
            for(unsigned a = 0; a < lvlman->ui->playerMesh.size(); a++) // Number character mesh
                PrintC("   " + lvlman->ui->playerMesh[a][i] + "       ");

            cout << endl;
        }

        // Show choice numbers
        for(unsigned i = 1; i <= lvlman->ui->playerMesh.size(); i++)
        {
            string number = "  " + to_string(i) + ". ";
            PrintC(number);
            for(unsigned w = 0; w <= (25 - number.size()); w++)
                PrintC(" ");
        }
        cout << endl;

        mesh = requestFromUser<int>("Choose character: ", 1, lvlman->ui->playerMesh.size() + 1);
        name = requestFromUser<string>("Character name: ");

        string createQuery = SQLPrepare("INSERT INTO PlayerChar(player_id, name, mesh, health, armour, attack_power, "
        "weapon_id, heal_power, defence_type, defence_colour, heal_type, heal_colour) "
        "VALUES (%?, '%?', %?, %?, %?, %?, %?, %?, %?, %?, %?, %?)", lvlManager.lock()->getPlayerID(), name, mesh - 1, health, armour,
        attack_power, weapon_id, heal_power, defenceType, defenceColour, healType, healColour);

        if (mysql_query(connection, createQuery.c_str()))
            cout << mysql_error(connection) << endl;
        else
            PrintC(name + " created.");

        Sleep(1000);
    }
}

// Delete character
void CharacterSelection::selCharDelete(MYSQL *connection, int charID, string name)
{
    string deleteQuery = SQLPrepare("DELETE FROM PlayerChar WHERE char_id = %?", charID);
    string safety = requestFromUser<string>("ARE YOU 100% SURE YOU WANT TO DELETE -> " + name + " [y/n]: ");

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
