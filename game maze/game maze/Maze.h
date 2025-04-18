#ifndef MAZE_H
#define MAZE_H

#include <vector>
#include <string>

class Maze {
private:
    static const int WIDTH = 10;
    static const int HEIGHT = 10;
    char grid[HEIGHT][WIDTH];
    std::pair<int, int> exitPosition;

public:
    Maze();

    // Initialize the maze with walls
    void initialize();

    // Load maze from file
    bool loadFromFile(const std::string& filename);

    // Save maze to file
    bool saveToFile(const std::string& filename);

    // Check if a position is valid (within bounds and not a wall)
    bool isValidPosition(int x, int y) const;

    // Get and set grid elements
    char getCell(int x, int y) const;
    void setCell(int x, int y, char value);

    // Find a random empty position in the maze
    std::pair<int, int> findRandomEmptyPosition();

    // Get exit position
    std::pair<int, int> getExitPosition() const;

    // Set exit position
    void setExitPosition(int x, int y);

    // Getters for dimensions
    static int getWidth() { return WIDTH; }
    static int getHeight() { return HEIGHT; }
};

#endif // MAZE_H