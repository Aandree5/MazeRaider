#include "UI.h"
#include "Maze.h"
#include "Player.h"
#include "ScoreTime.h"
#include "LevelManager.h"
#include "BattleScene.h"
#include <mysql.h>

UI::UI(LevelManager* lvlman)
{
    lvlManager = lvlman;
    playerOldPos = make_pair(make_pair(lvlman->player->xPos, lvlman->player->yPos),
                              lvlman->maze->getMazeArray()[lvlman->player->xPos][lvlman->player->yPos]);

    inBattle = false;
    btlScene = nullptr;
}

bool UI::ChangeColor(int color)
{
    switch (color)
    {
    case 12:
        red;
        break;
    case 9:
        blue;
        break;
    case 10:
        green;
        break;
    case 14:
        yellow;
        break;
    case 11:
        cyan;
        break;
    case 15:
        white;
        break;
    case 13:
        purple;
        break;
    case 4:
        darkred;
        break;
    case 3:
        darkblue;
        break;
    case 2:
        darkgreen;
        break;
    case 5:
        darkpurple;
        break;
    case 34:
        healthGreen;
        break;
    case 238:
        healthYellow;
        break;
    case 68:
        healthRed;
        break;
    default:
        grey;
        return false;
    }

    return true;
}

// cout with color   CHAR Overload
void UI::PrintC(char character, int color, bool twoChar)
{
    bool needsReset = ChangeColor(color);

    if (twoChar)
        cout << character << character;
    else
        cout << character;

    // Return color to default
    if (needsReset)
        grey;
}

// cout with color   STRING Overload
void UI::PrintC(string character, int color, bool twoChar)
{
    bool needsReset = ChangeColor(color);

    if (twoChar)
        cout << character << character;
    else
        cout << character;

    // Return color to default
    if (needsReset)
        grey;
}

// Build UI
void  UI::ShowUI()
{
    int battleState = 0; // 0 = Battle Continues  |  1 = Player Lost (GameOver)  |  2 = Enemy Killed
    while (true && battleState != 1)
    {
        clearScreen();
        battleState = 0;

        PrintStateInfo();
        if (!inBattle)
            PrintMaze();
        else
            battleState = btlScene->BuildScene();

        if (battleState == 1)
        {
            delete btlScene;
            btlScene = nullptr;
            break;
        }
        else if (battleState == 2)
        {
            delete btlScene;
            btlScene = nullptr;
            continue;
        }

        if (btlScene == nullptr || btlScene->TPlayerFEnemy)
            PrintUOptions();
    }

    if (battleState == 1)
        ShowGameOver();
}

// Print Maze
void  UI::PrintMaze()
{
    // Get player position, 2 = Player
    if (lvlManager->maze->getMazeArray()[lvlManager->player->xPos][lvlManager->player->yPos] != 2)
    {
        // Replace player old position and store the new "old" position to replace later
        lvlManager->maze->getMazeArray()[playerOldPos.first.first][playerOldPos.first.second] = playerOldPos.second;
        playerOldPos = make_pair(make_pair(lvlManager->player->xPos, lvlManager->player->yPos),
                              lvlManager->maze->getMazeArray()[lvlManager->player->xPos][lvlManager->player->yPos]);

        lvlManager->maze->getMazeArray()[lvlManager->player->xPos][lvlManager->player->yPos] = 2;
    }

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
            case 2: // 1: Wall
                PrintC( mazeWall, 11, true  );
                break;
            case 3: // 3: Chest
                PrintC( mazeWall, 14, true );
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

     MYSQL* connection;
     MYSQL_ROW row;
      connection = mysql_init(0);

     if(connection)
        cout<<"connection successful "<<endl;
     else
        cout<<"connection problem: "<<mysql_error(connection)<<endl;

    connection = mysql_real_connect(connection,"server1.jesseprescott.co.uk","jessepre","Mazeraider123?","jessepre_mazeraider",0,NULL,0);
    if(connection){
        cout<<"Connected"<<connection<<endl;

        string username,password;
        cout<<"enter username: "<<endl; cin>>username;
        cout<<"enter password: "<<endl; cin>>password;

        string query="select * from information where username='"+username+"' and password='"+password+"';";

        int queryResult = mysql_query(connection, query.c_str());
        MYSQL_RES* result = mysql_store_result(connection);

        if (mysql_num_rows(result) >= 1)
        {
            cout<<"Welcome to the game"<<endl;
        }
        else{
            cout<<"Please try again"<<endl;
        }
    }
}

// Print User Possible Options
void UI::PrintUOptions()
{
    char userOption;

    if (!inBattle)
    {
        cout << endl << endl << "Choose option:    w - Up       a - Left        d - Right        s - Down" << endl;
        cin >> userOption;


        if (userOption != (char)98)
            lvlManager->player->movePlayer(userOption);
        else
            btlScene = new BattleScene(lvlManager);
    }
    else
    {
        cout << endl;
        cout << "Attack:    a        Defend:    d" << endl;
        cout << "  Heal:    h           Run:    r" << endl;
        cin >> userOption;

        // Player attacks
        if (userOption == (char)97)
            btlScene->PlayerAttack(1, 10, 10, 5);

        // Player defends
        else if (userOption == (char)100)
            btlScene->PlayerDefend(0, 3, 150);

        // Player heals
        else if (userOption == (char)104)
            btlScene->PlayerHeal(0, 2, 10, 150);

        // Player runs
        else if (userOption == (char)114)
        {
            inBattle = false;
            delete btlScene;
            btlScene = nullptr;
        }
    }
}

void UI::ShowGameOver()
{
    clearScreen();
    cout << "Game Over!";
}
