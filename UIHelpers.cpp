#include "UIHelpers.h"

bool UIHelpers::ChangeColor(int color)
{
    switch (color)
    {
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
        break;
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
    case 192:
        debugBlackRed;
        break;
    case 238:
        healthYellow;
        break;
    default:
        grey;
        return false;
    }

    return true;
}

// cout with color - CHAR Overload
void UIHelpers::PrintC(char character, int color, bool twoChar)
{
    bool needsReset = ChangeColor(color);

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
void UIHelpers::PrintC(string character, int color, bool twoChar)
{
    bool needsReset = ChangeColor(color);

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

void UIHelpers::setFullScreen()
{
    /*keybd_event(VK_MENU,0x38,0,0);
    keybd_event(VK_RETURN,0x1c,0,0);
    keybd_event(VK_RETURN,0x1c,KEYEVENTF_KEYUP,0);
    keybd_event(VK_MENU,0x38,KEYEVENTF_KEYUP,0);*/

    ShowWindow(GetConsoleWindow(), SW_MAXIMIZE);
}


