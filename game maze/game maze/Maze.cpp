#include "Maze.h"
#include <fstream>
#include <stdexcept>
#include <random>
#include <chrono>

Maze::Maze() : exitPosition({0, 0}) {
    initialize();
}

void Maze::initialize() {
    // Initialize with empty spaces
    for (int y = 0; y < HEIGHT; ++y) {
        for (int x = 0; x < WIDTH; ++x) {
            grid[y][x] = ' ';
        }
    }

    // Add border walls
    for (int x = 0; x < WIDTH; ++x) {
        grid[0][x] = grid[HEIGHT-1][x] = '█';
    }
    for (int y = 0; y < HEIGHT; ++y) {
        grid[y][0] = grid[y][WIDTH-1] = '█';
    }

    // Set exit in a fixed position for now
    setExitPosition(WIDTH-2, HEIGHT-2);
    grid[exitPosition.second][exitPosition.first] = 'E';
}

bool Maze::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        return false;
    }

    std::string line;
    int y = 0;

    while (getline(file, line) && y < HEIGHT) {
        for (int x = 0; x < WIDTH && x < static_cast<int>(line.length()); ++x) {
            grid[y][x] = line[x];
            if (line[x] == 'E') {
                exitPosition = {x, y};
            }
        }
        ++y;
    }

    file.close();
    return true;
}

bool Maze::saveToFile(const std::string& filename) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        return false;
    }

    for (int y = 0; y < HEIGHT; ++y) {
        for (int x = 0; x < WIDTH; ++x) {
            file << grid[y][x];
        }
        file << std::endl;
    }

    file.close();
    return true;
}

bool Maze::isValidPosition(int x, int y) const {
    if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT) {
        return false;
    }

    return grid[y][x] != '█';
}

char Maze::getCell(int x, int y) const {
    if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT) {
        throw std::out_of_range("Position out of bounds");
    }

    return grid[y][x];
}

void Maze::setCell(int x, int y, char value) {
    if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT) {
        throw std::out_of_range("Position out of bounds");
    }

    grid[y][x] = value;
}

std::pair<int, int> Maze::findRandomEmptyPosition() {
    // Seed with time
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::mt19937 rng(seed);
    std::uniform_int_distribution<int> x_dist(1, WIDTH - 2);
    std::uniform_int_distribution<int> y_dist(1, HEIGHT - 2);

    int x, y;
    do {
        x = x_dist(rng);
        y = y_dist(rng);
    } while (grid[y][x] != ' ');

    return {x, y};
}

std::pair<int, int> Maze::getExitPosition() const {
    return exitPosition;
}

void Maze::setExitPosition(int x, int y) {
    exitPosition = {x, y};
    grid[y][x] = 'E';
}