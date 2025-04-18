#ifndef LEVEL_H
#define LEVEL_H

#include <string>
#include <vector>
#include "Maze.h"
#include "Player.h"
#include "Enemy.h"
#include "Item.h"

class Level {
private:
    int levelNumber;
    Maze maze;
    Player player;
    std::vector<Enemy> enemies;
    std::vector<Item> items;

    // Level configuration
    std::string mazeFile;
    int numEnemies;
    int numItems;

public:
    Level(int levelNumber);

    // Initialize level with correct number of entities
    void initialize();

    // Get level components
    Maze& getMaze();
    Player& getPlayer();
    std::vector<Enemy>& getEnemies();
    std::vector<Item>& getItems();

    // Level number
    int getLevelNumber() const;

    // Update level entities
    void update();

    // Render the level
    void render();

    // Check if level is completed
    bool isCompleted() const;

    // Check for collisions between player and other entities
    void checkCollisions();
};

#endif // LEVEL_H