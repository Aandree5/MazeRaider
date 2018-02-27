#ifndef MAZE_H
#define MAZE_H

#include<vector>
#include<stack>

class Maze {

    public:
        Maze(unsigned width, unsigned height, unsigned seed);
        Maze(unsigned width, unsigned height) : Maze(width, height, 0) {}
        int** getMazeArray();
        std::pair<unsigned, unsigned> getMazeSizeWH();
        std::pair<int,int> getMazeStart();
<<<<<<< HEAD
=======
        int getSeed();
>>>>>>> 979a7bdd2014764ad282952f69348112ddc1675e
        void updateChest(int x, int y);

    protected:

    private:
        int** m_maze;
        int m_seed;
        unsigned m_width;
        unsigned m_height;
        std::stack< std::pair<unsigned, unsigned> > m_stack;
        std::vector<std::pair<int, int> > m_visitedNodes;
        std::pair<int, int> m_start;
        std::vector<std::pair<int, int> > m_deadEnds;
        bool m_firstIteration = true;
        bool m_exitConnected = false;
        const int m_chestChance = 15;

        void generateMaze();
        void generateChests();
};

#endif // MAZEGENERATOR_H
