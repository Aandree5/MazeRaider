#include<vector>
#include<stack>

#ifndef MAZE_H
#define MAZE_H


class Maze {

    public:
        Maze(unsigned width, unsigned height);

        void printMaze();

    protected:

    private:
        bool** m_maze;
        unsigned m_width;
        unsigned m_height;
        std::stack< std::pair<unsigned, unsigned> > m_stack;
        std::pair<int, int> m_start;
        bool m_firstIteration = true;
        bool m_exitConnected = false;

        void generateMaze();
};

#endif // MAZEGENERATOR_H
