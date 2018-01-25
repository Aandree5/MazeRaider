#include "Maze.h"
#include "Utils.h"

#include <iostream>
#include <stdlib.h>
#include <stdexcept>
#include <vector>
#include <time.h>

/**
 * Constructor.
 */
Maze::Maze(unsigned width, unsigned height) : m_width(width), m_height(height) {

    // Check that the width and height given are odd numbers.
    if(m_width % 2 == 0 || m_height % 2 == 0) {
        throw std::invalid_argument("Maze must have odd width and odd height.");
    }

    // Create a new 2D array of width and height and fill with 1's.
    m_maze = Utils::create2DBoolArray(m_width, m_height, true);

    // Choose and create entrance point in maze.
    m_maze[0][7] = false;
    m_maze[1][7] = false;
    m_start = std::make_pair(1, 7);
    m_stack.push(std::make_pair(1, 7));

    // Choose and create exit point in maze.
    m_maze[14][7] = false;

    //TODO: Make entrance and exit random not fixed.

    // Initialise random number generator.
    srand(time(NULL));

    // Begin recursive maze generation.
    generateMaze();
}

/**
 * Generate the maze.
 */
void Maze::generateMaze() {

    // Get the current node.
    std::pair<int, int> currentNode = m_stack.top();

    if(currentNode == m_start && !m_firstIteration) {
        return;
    }

    // Get neighbouring wall values in every direction 2 blocks ahead.
    bool left, right, up, down;

    if(currentNode.first - 2 < 0) {
        left = false; // Pretend outside of maze is a path.
    } else {
        left = m_maze[currentNode.first - 2][currentNode.second];
    }

    if(currentNode.first + 2 > m_width - 1) {
        right = false; // Pretend outside of maze is a path.
    } else {
        right = m_maze[currentNode.first + 2][currentNode.second];
    }

    if(currentNode.second - 2 < 0) {
        up = false; // Pretend outside of maze is a path.
    } else {
        up = m_maze[currentNode.first][currentNode.second - 2];
    }

    if(currentNode.second + 2 > m_height - 1) {
        down = false; // Pretend outside of maze is a path.
    } else {
        down = m_maze[currentNode.first][currentNode.second + 2];
    }

    if(!left && !right && !up && !down) { // If dead-end, backtrack.
        m_stack.pop();
        generateMaze();
        return;
    }

    // Create vector used to choose a random direction.
    std::vector<int> availableDirections;

    if(left) {
        availableDirections.push_back(1);
    }

    if(right) {
        availableDirections.push_back(2);
    }

    if(up) {
        availableDirections.push_back(3);
    }

    if(down) {
        availableDirections.push_back(4);
    }

    // Choose random index thus choosing a random direction.
    int randomDirectionIndex = rand() % availableDirections.size();
    std::pair<unsigned, unsigned> newNode;

    switch(availableDirections.at(randomDirectionIndex)) {
        case 1: { // Left
            std::pair<unsigned, unsigned> newNode = std::make_pair(currentNode.first - 2, currentNode.second);
            m_maze[currentNode.first - 1][currentNode.second] = false;
            m_maze[currentNode.first - 2][currentNode.second] = false;
            m_stack.push(newNode);
            break;
        }
        case 2: { // Right
            std::pair<unsigned, unsigned> newNode = std::make_pair(currentNode.first + 2, currentNode.second);
            m_maze[currentNode.first + 1][currentNode.second] = false;
            m_maze[currentNode.first + 2][currentNode.second] = false;
            m_stack.push(newNode);
            break;
        }
        case 3: { // Up
            std::pair<unsigned, unsigned> newNode = std::make_pair(currentNode.first, currentNode.second - 2);
            m_maze[currentNode.first][currentNode.second - 1] = false;
            m_maze[currentNode.first][currentNode.second - 2] = false;
            m_stack.push(newNode);
            break;
        }
        case 4: { // Down
            std::pair<unsigned, unsigned> newNode = std::make_pair(currentNode.first, currentNode.second + 2);
            m_maze[currentNode.first][currentNode.second + 1] = false;
            m_maze[currentNode.first][currentNode.second + 2] = false;
            m_stack.push(newNode);
            break;
        }
    }

    m_firstIteration = false;
    generateMaze();
}

/**
 * Print the maze to the console.
 */
void Maze::printMaze() {

    for(int h = 0; h < m_height; h++) {
        std::cout << std::endl;

        for(int w = 0; w < m_width; w++) {
            std::cout << m_maze[w][h] << ", ";
        }
    }

    std::cout << std::endl;
}
