#include "EnemyAI.h"
#include "Maze.h"
#include "LevelManager.h"
#include "Player.h"
#include "UIHelpers.h"

using namespace UIHelpers;

EnemyAI::EnemyAI(LevelManager* lvlman)
{
    lvlManager = lvlman;
}

void EnemyAI::getNextPosition(Enemy* enemy)
{
    if (abs(lvlManager->player->xPos - enemy->xPos) < followPlayerLimit ||
        abs(lvlManager->player->yPos - enemy->yPos) < followPlayerLimit )
    {
        vector<pos> path = findPath({enemy->xPos, enemy->yPos});

        //DEBUG
        //debugPrintNodes(path);
        //system("pause");

        // (1, 0) = Parent at right | (-1, 0) = Parent at Left | (0, 1) = Parent at Top | (0, -1) = Parent at Bottom

        pos dir = path[1] - path[0];
        pos nextPos;

        for(pos p : path)
        {
            if((p.X != path[0].X && dir.X == 0) || (p.Y != path[0].Y && dir.Y == 0))
                break;
            else
            {
                enemy->xPos = p.X;
                enemy->yPos = p.Y;
            }
        }
    }
    else
    {
        enemy->randomMoveEnemy();
    }
}

// Find shortest path to player
vector<EnemyAI::pos> EnemyAI::findPath(pos p)
{
    pos startPosition = p;
    pos destPosition = {lvlManager->player->xPos, lvlManager->player->yPos};
    vector<node> openList;
    vector<node> closeList;
    node currNode;

    currNode.position = startPosition;
    currNode.F = 0;
    currNode.G = 0;
    currNode.H = 0;
    currNode.parent.X = 0;
    currNode.parent.Y = 0;

    openList.emplace_back(currNode);

    while (openList.size() > 0)
    {
        if(currNode.position == destPosition)
            break;

        closeList.emplace_back(currNode);
        auto it = find(openList.begin(), openList.end(), currNode);
            if (it != openList.end())
                openList.erase(it);

        vector<node> tempList = checkNodes(currNode, startPosition, destPosition, closeList);
        openList.insert(openList.end(), tempList.begin(), tempList.end());

        sort(openList.begin(), openList.end());

        vector<node> sameFValue;
        sameFValue.emplace_back(openList[0]);
        for(node n : openList)
        {
            if(n.F == sameFValue[0].F)
                sameFValue.emplace_back(n);
            else
                break;
        }

        if(sameFValue.size() > 1)
            sort(sameFValue.begin(), sameFValue.end(), node::compareH);

        currNode = sameFValue[0];
    }

    //DEBUG
    //debugPrintNodes(openList, closeList);
    //system("pause");

    //debugPrintNodes(closeList);
    //system("pause");

    vector<pos> path;
    path.emplace_back(currNode.position);

    while(currNode.position != startPosition)
    {
        for(node n : closeList)
        {
            if(n.position == currNode.parent)
            {
                path.insert(path.begin(), n.position);
                currNode = n;
                break;
            }
        }
    }

    return path;
}

// Check surrounding nodes
vector<EnemyAI::node> EnemyAI::checkNodes(node cNode, pos sPosition, pos dPosition, vector<node>& closed)
{
    vector<node> tList;
    node tempNode;
    array<pos, 4> directions;
    directions[0] = {1, 0};
    directions[1] = {-1, 0};
    directions[2] = {0, 1};
    directions[3] = {0, -1};

    for(pos dir : directions)
    {
        bool notChecked = true;
        for(node n : closed)
            if(n.position == cNode.position + dir)
            {
                if(n.F < cNode.F)
                {
                    n.parent = cNode.position;
                    // Distance from starting position
                    n.G = cNode.G + 1;
                    // Distance from destination position
                    n.H = cNode.H + 1;
                    // Sum of both distances
                    n.F = n.G + n.H;
                }
                notChecked = false;
                continue;
            }
        // 0 = to path
        if(notChecked && lvlManager->maze->getMazeArray()[cNode.position.X + dir.X][cNode.position.Y + dir.Y] == 0)
        {
            tempNode.position = cNode.position + dir;
            tempNode.parent = cNode.position;

            // Distance from starting position
            tempNode.G = abs(tempNode.position.X - sPosition.X) + abs(tempNode.position.Y - sPosition.Y);
            // Distance from destination position
            tempNode.H = abs(tempNode.position.X - dPosition.X) + abs(tempNode.position.Y - dPosition.Y);
            // Sum of both distances
            tempNode.F = tempNode.G + tempNode.H;

            tList.emplace_back(tempNode);
        }
    }

    return tList;
}


// DEBUG
void EnemyAI::debugPrintNodeF(node n, int colour)
{
        #ifdef _WIN32
        HANDLE hStdOut = GetStdHandle( STD_OUTPUT_HANDLE );
        CONSOLE_SCREEN_BUFFER_INFO cbsi;
        GetConsoleScreenBufferInfo(hStdOut, &cbsi);
        COORD originalPos = cbsi.dwCursorPosition;
    #endif // _WIN32

    #ifdef __linux__
        int hStdOut;
        cout << "\033[s";
    #endif // __linux__

    cursorPosition(hStdOut, n.position.X * 2, n.position.Y + 3);
    if(n.F < 10)
        PrintC(to_string(n.F), colour, true);
    else
        PrintC(to_string(n.F), colour);

    #ifdef _WIN32
        SetConsoleCursorPosition( hStdOut, originalPos );
    #endif // _WIN32

    #ifdef __linux__
        cout << "\033[u";
    #endif // __linux__
}

void EnemyAI::debugPrintNodeParent(pos p, pos dir)
{
    #ifdef _WIN32
    HANDLE hStdOut = GetStdHandle( STD_OUTPUT_HANDLE );
    CONSOLE_SCREEN_BUFFER_INFO cbsi;
    GetConsoleScreenBufferInfo(hStdOut, &cbsi);
    COORD originalPos = cbsi.dwCursorPosition;
    #endif // _WIN32

    #ifdef __linux__
        int hStdOut;
        cout << "\033[s";
    #endif // __linux__

    cursorPosition(hStdOut, p.X * 2, p.Y + 3);

    // (1, 0) = Parent at right | (-1, 0) = Parent at Left | (0, 1) = Parent at Top | (0, -1) = Parent at Bottom
    if(dir.X == 1 && dir.Y == 0)
        PrintC(" >", 3);
    else if(dir.X == -1 && dir.Y == 0)
        PrintC("< ", 3);
    else if(dir.X == 0 && dir.Y == -1)
        PrintC(R"(/\)", 3);
    else if(dir.X == 0 && dir.Y == 1)
        PrintC(R"(\/)", 3);


    #ifdef _WIN32
        SetConsoleCursorPosition( hStdOut, originalPos );
    #endif // _WIN32

    #ifdef __linux__
        cout << "\033[u";
    #endif // __linux__
}

void EnemyAI::debugPrintNodes(vector<node> showValueOpenL, vector<node> showValueClosedL)
{
    for(node n : showValueOpenL)
        debugPrintNodeF(n, 164);

    for(node n : showValueClosedL)
        debugPrintNodeF(n, 192);
}

void EnemyAI::debugPrintNodes(vector<node> showParentList)
{
    #ifdef _WIN32
    HANDLE hStdOut = GetStdHandle( STD_OUTPUT_HANDLE );
    CONSOLE_SCREEN_BUFFER_INFO cbsi;
    GetConsoleScreenBufferInfo(hStdOut, &cbsi);
    COORD originalPos = cbsi.dwCursorPosition;
    #endif // _WIN32

    #ifdef __linux__
        int hStdOut;
        cout << "\033[s";
    #endif // __linux__


    for(node n : showParentList)
    {
        pos dir = n.parent - n.position;

        debugPrintNodeParent(n.position, dir);
    }


    #ifdef _WIN32
        SetConsoleCursorPosition( hStdOut, originalPos );
    #endif // _WIN32

    #ifdef __linux__
        cout << "\033[u";
    #endif // __linux__
}

void EnemyAI::debugPrintNodes(vector<pos> showParentList)
{
    #ifdef _WIN32
    HANDLE hStdOut = GetStdHandle( STD_OUTPUT_HANDLE );
    CONSOLE_SCREEN_BUFFER_INFO cbsi;
    GetConsoleScreenBufferInfo(hStdOut, &cbsi);
    COORD originalPos = cbsi.dwCursorPosition;
    #endif // _WIN32

    #ifdef __linux__
        int hStdOut;
        cout << "\033[s";
    #endif // __linux__


    for(int i = 0; i < showParentList.size() - 1; i++)
    {
        pos dir = showParentList[i] - showParentList[i - 1];

        debugPrintNodeParent(showParentList[i], dir);
    }


    #ifdef _WIN32
        SetConsoleCursorPosition( hStdOut, originalPos );
    #endif // _WIN32

    #ifdef __linux__
        cout << "\033[u";
    #endif // __linux__
}
