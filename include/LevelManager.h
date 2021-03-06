#ifndef LEVELMANAGER_H
#define LEVELMANAGER_H
#include <vector>
#include <memory>
#include <cstdlib>
#include <string>


using namespace std;

class UI;
class Maze;
class Player;
class Enemy;
class ScoreTime;
class EnemyAI;
class CharacterSelection;

class LevelManager : public std::enable_shared_from_this<LevelManager>
{
    public:
        LevelManager(int pID);
        ~LevelManager();

        void BuildLevel();

        shared_ptr<UI> ui;
        shared_ptr<CharacterSelection> cSelection;
        shared_ptr<Maze>maze;
        Player *player;
        shared_ptr<EnemyAI>enemyai;
        ScoreTime *scoretime;
        vector<shared_ptr<Enemy>> enemies;
        //this allow get music
        enum class Music
        {
            Muted,
            MainMenu,
            SelectionScreen,
            Map,
            Battle,
            GameOver,
            Victory
        };
        //we are using this class for effects such as moving run
        enum class Effect
        {
            Move,
            Run,
            PickUp,
            Attack,
            Defend,
            Heal,
            EnemyKilled,
            LevelLost,
            LevelPassed,
            PauseOpen,
            PauseClose
        };

        Music music;
        bool isMuted;

        void changeMusic(Music m);
        void playEffect(Effect e);

        int getPlayerID();

        bool isPaused;
        bool exitToMenu;

        void nextLevel();
        void lowLevel();
        void mediumLevel();
        void highLevel();
        void saveMaze();
        void makeMazeTable();

    protected:

    private:

        pair<int, int> mazeSize;
        int nrEnemies;

        int playerID;

        void loadLevel();
};

#endif // LEVELMANAGER_H
