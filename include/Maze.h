#ifndef MAZE_H
#define MAZE_H

#include<vector>
#include<stack>

class Maze {

    public:
        Maze(unsigned width, unsigned height);
        std::tuple<int**, unsigned, unsigned> getDataMWH();

    protected:

    private:
        int** m_maze;
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
