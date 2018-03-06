#ifndef ENEMYAI_H
#define ENEMYAI_H
#include <vector>
#include <array>
#include <algorithm>
#include <memory>

using namespace std;

class LevelManager;
class Enemy;

class EnemyAI
{
    public:
        EnemyAI(shared_ptr<LevelManager> lvman);

        void getNextPosition(shared_ptr<Enemy> enemy);

        int followPlayerLimit = 5;
    protected:

    private:
        //variables
        weak_ptr<LevelManager> lvlManager;

        // Path finding node structure
        struct pos
        {
            int X;
            int Y;

            friend bool operator== (const pos& p1, const pos& p2)
            {
                return p1.X == p2.X && p1.Y == p2.Y;
            }

            friend bool operator!= (const pos& p1, const pos& p2)
            {
                return p1.X != p2.X || p1.Y != p2.Y;
            }

            friend pos operator+(const pos& p1, const pos& p2)
            {
                return {p1.X + p2.X, p1.Y + p2.Y};
            }

            friend pos operator-(const pos& p1, const pos& p2)
            {
                return {p1.X - p2.X, p1.Y - p2.Y};
            }
        };

        struct node
        {
            pos position;
            int G; // Distance from starting position
            int H; // Distance from destination position
            int F; // Sum of both distances
            pos parent;

            friend bool operator==(const node& n1, const node& n2)
            {
                return n1.position == n2.position;
            }

            friend bool operator<(const node& n1, const node& n2)
            {
                return n1.F < n2.F;
            }

            friend bool operator>(const node& n1, const node& n2)
            {
                return n1.F > n2.F;
            }

            static bool compareH( const node& n1, const node& n2 )
            {
                return n1.H < n2.H;
            }
        };


        // Find shortest path to player
        vector<pos> findPath(pos p);
        // Check surrounding nodes
        vector<node> checkNodes(node cNode, pos sPosition, pos dPosition, vector<node>& closed);

        // DEBUG
        void debugPrintNodeF(node n, int colour);
        void debugPrintNodeParent(pos p, pos dir);
        void debugPrintNodes(vector<node> showValueOpenL, vector<node> showValueClosedL);
        void debugPrintNodes(vector<node> showParentList);
        void debugPrintNodes(vector<pos> showParentList);
};

#endif // ENEMYAI_H
