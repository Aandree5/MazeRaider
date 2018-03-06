#include "UIHelpers.h"

// change the text colour
bool UIHelpers::ChangeColour(int colour)
{
    switch (colour)
    {
    case 0:
        blackonblack;
        break;
    case 1:
        darkblue;
        break;
    case 2:
        darkgreen;
        break;
    case 3:
        darkcyan;
        break;
    case 4:
        darkred;
        break;
    case 5:
        darkpurple;
        break;
    case 6:
        armygreen;
        break;
    case 7:
        grey;
        return false;
    case 8:
        darkgrey;
        break;
    case 9:
        blue;
        break;
    case 10:
        green;
        break;
    case 11:
        cyan;
        break;
    case 12:
        red;
        break;
    case 13:
        purple;
        break;
    case 14:
        yellow;
        break;
    case 15:
        white;
        break;
    case 34:
        healthGreen;
        break;
    case 68:
        healthRed;
        break;
    case 164:
        debugBlackGreen;
        break;
    case 185:
        playerColor;
        break;
    case 192:
        debugBlackRed;
        break;
    case 196:
        enemyColor;
        break;
    case 232:
        chestColor;
        break;
    case 238:
        healthYellow;
        break;
    case 240:
        blackonwhite;
        break;
    default:
        grey;
        return false;
    }

    return true;
}

// cout with color - CHAR Overload
void UIHelpers::PrintC(char character, int colour, bool twoChar)
{
    bool needsReset = ChangeColour(colour);

    if (twoChar)
        cout << character << character;
    else
        cout << character;


    cout << flush;

    // Return color to default
    if (needsReset)
        grey;
}

// cout with color - STRING Overload
void UIHelpers::PrintC(string character, int colour, bool twoChar)
{
    bool needsReset = ChangeColour(colour);

    if (twoChar)
        cout << character << character;
    else
        cout << character;


    cout << flush;

    // Return color to default
    if (needsReset)
        grey;
}

string UIHelpers::toLower(string str)
{
    string strLower;

    for( char c : str )
        strLower += tolower(c) ;

    return strLower;
}

void UIHelpers::SetFullScreen()
{
    /*keybd_event(VK_MENU,0x38,0,0);
    keybd_event(VK_RETURN,0x1c,0,0);
    keybd_event(VK_RETURN,0x1c,KEYEVENTF_KEYUP,0);
    keybd_event(VK_MENU,0x38,KEYEVENTF_KEYUP,0);*/

    ShowWindow(GetConsoleWindow(), SW_MAXIMIZE);
}

// Show pause screen
void UIHelpers::BuildPause(shared_ptr<LevelManager> lvlManager, int x, int y, bool allowSave)
{
    #ifdef _WIN32
        HANDLE hStdOut = GetStdHandle( STD_OUTPUT_HANDLE );
        CONSOLE_SCREEN_BUFFER_INFO cbsi;
        GetConsoleScreenBufferInfo(hStdOut, &cbsi);
    #endif // _WIN32

    #ifdef __linux__
        int hStdOut;
    #endif // __linux__



    int input;
    string mute = "Mute  ";
    if(lvlManager->isMuted)
        mute = "Unmute";

    array<string, 15> menuContent = {R"( __             _                 )",
                                     R"(/__ _ __  _    |_) _     _  _  _| )",
                                     R"(\_|(_||||(/_   |  (_||_|_> (/_(_| )",
                                       "----------------------------------",
                                       "  ",
                                       "(P) Resume to game    ",
                                       "(H) HighScore         ",
                                       "(M) " + mute + "            ",
                                       "  ",
                                       "(E) Exit to main menu ",
                                       "  ",
                                       "----------------------------------",
                                       "  ",
                                       "  ",
                                       "  "};

    int width = 40;
    int height = menuContent.size();

    if((x = x - (width / 2)) < 0)
        x = 0;

    if((y = y - (height / 2)) < 0)
        y = 0;

// Top of window
    cursorPosition(hStdOut, x, y);
    y++;

    PrintC(bsTopLeftCorner, 15);

    for(int w = 0; w < width; w++)
        PrintC(bsTopBottomLines, 15);

    PrintC(bsTopRightCorner, 15);

    cursorPosition(hStdOut, x, y);
    y++;


// Content of window
    for(int h = 0; h < height; h++)
    {
        int wSpace = (width - menuContent[h].size()) / 2;

        PrintC(bsLeftRightLines, 15);

        for(int w = 0; w < wSpace; w++)
            PrintC(" ");

        PrintC(menuContent[h]);

        for(int w = 0; w < wSpace; w++)
            PrintC(" ");

        PrintC(bsLeftRightLines, 15);

        cursorPosition(hStdOut, x, y);
        y++;
    }


// Bottom of window
    PrintC(bsBottomLeftCorner, 15);

    for(int w = 0; w < width; w++)
        PrintC(bsTopBottomLines, 15);

    PrintC(bsBottomRightCorner, 15);


    if((x = (x + (width / 2)) - 9) < 0)
        x = 0;

    y -= 3;
    cursorPosition(hStdOut, x, y);



    input = requestFromUser<char>(lvlManager);

    if(tolower(input) == 'e')
        lvlManager->exitToMenu = true;
    else if(tolower(input) == 'm')
    {
        lvlManager->changeMusic(LevelManager::Music::Muted);
        lvlManager->isMuted = !lvlManager->isMuted;
    }
}
