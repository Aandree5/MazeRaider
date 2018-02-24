#include "UIHelpers.h"


bool UIHelpers::ChangeColor(int color)
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

