#include "Level.h"
#include <iostream>
#include <algorithm>
#include <sstream>

Level::Level(int levelNumber)
    : levelNumber(levelNumber),
      player(1, 1) // Default starting position
{
    // Set difficulty based on level number
    numEnemies = levelNumber;
    numItems = levelNumber * 2;

    // Create maze filename based on level number
    std::stringstream ss;
    ss << "level" << levelNumber << ".txt";
    mazeFile = ss.str();

    initialize();
}

void Level::initialize() {
    // Try to load the maze from file
    if (!maze.loadFromFile(mazeFile)) {
        // If loading fails, generate a new maze
        maze.initialize();
        maze.saveToFile(mazeFile);
    }

    // Place player at a random empty position
    auto playerPos = maze.findRandomEmptyPosition();
    player.setPosition(playerPos.first, playerPos.second);

    // Create and place enemies
    enemies.clear();
    for (int i = 0; i < numEnemies; ++i) {
        auto pos = maze.findRandomEmptyPosition();
        enemies.emplace_back(pos.first, pos.second);
    }

    // Create and place items
    items.clear();
    for (int i = 0; i < numItems; ++i) {
        auto pos = maze.findRandomEmptyPosition();
        items.emplace_back(pos.first, pos.second);
    }
}

Maze& Level::getMaze() {
    return maze;
}

Player& Level::getPlayer() {
    return player;
}

std::vector<Enemy>& Level::getEnemies() {
    return enemies;
}

std::vector<Item>& Level::getItems() {
    return items;
}

int Level::getLevelNumber() const {
    return levelNumber;
}

void Level::update() {
    // Update all entities
    player.update();

    for (auto& enemy : enemies) {
        enemy.update();
    }

    for (auto& item : items) {
        item.update();
    }

    // Check for collisions
    checkCollisions();
}

void Level::render() {
    // Make a copy of the maze for rendering
    char displayGrid[Maze::getHeight()][Maze::getWidth()];

    for (int y = 0; y < Maze::getHeight(); ++y) {
        for (int x = 0; x < Maze::getWidth(); ++x) {
            displayGrid[y][x] = maze.getCell(x, y);
        }
    }

    // Place exit (in case it was overwritten)
    auto exitPos = maze.getExitPosition();
    displayGrid[exitPos.second][exitPos.first] = 'E';

    // Place items on the display grid
    for (const auto& item : items) {
        if (!item.isCollected()) {
            displayGrid[item.getY()][item.getX()] = item.getSymbol();
        }
    }

    // Place enemies on the display grid
    for (const auto& enemy : enemies) {
        displayGrid[enemy.getY()][enemy.getX()] = enemy.getSymbol();
    }

    // Place the player (should be on top of everything)
    displayGrid[player.getY()][player.getX()] = player.getSymbol();

    // Clear screen (platform-dependent)
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif

    // Print the level header
    std::cout << "=== Level " << levelNumber << " ===" << std::endl;
    std::cout << "Score: " << player.getScore() << " | Moves: " << player.getMoves() << std::endl;
    std::cout << "Controls: W (up), A (left), S (down), D (right), Q (quit)" << std::endl;

    // Print the grid
    for (int y = 0; y < Maze::getHeight(); ++y) {
        for (int x = 0; x < Maze::getWidth(); ++x) {
            std::cout << displayGrid[y][x];
        }
        std::cout << std::endl;
    }
}

bool Level::isCompleted() const {
    return (player.getX() == maze.getExitPosition().first &&
            player.getY() == maze.getExitPosition().second);
}

void Level::checkCollisions() {
    // Check collisions with items
    for (auto& item : items) {
        if (!item.isCollected() &&
            item.getX() == player.getX() &&
            item.getY() == player.getY()) {
            player.increaseScore(item.getValue());
            item.collect();
        }
    }
}