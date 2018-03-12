#ifndef CHARACTERSELECTION_H
#define CHARACTERSELECTION_H
#include <vector>
#include <array>
#include <map>
#include <memory>
#ifdef _WIN32
#include <windows.h>
#endif // _WIN32
#include <mysql.h>

using namespace std;

class LevelManager;

class CharacterSelection
{
    public:
        CharacterSelection(shared_ptr<LevelManager> lvlman);

        void ShowSelectionScreen();

    protected:

    private:
        weak_ptr<LevelManager> lvlManager;

        // Print array to screen
        void selCharPrintOptions(array<string, 12> &mOptions, int &c);
        // White space between char info
        void selCharWhiteSpaceDivider(array<string, 12> &mOptions, int &c);
        // Screen to create character
        void selCharCreateNew(MYSQL *connection);
        // Delete character
        void selCharDelete(MYSQL *connection, int charID, string name);
};

#endif // CHARACTERSELECTION_H
