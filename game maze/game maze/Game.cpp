#include "Game.h"
#include <iostream>
#include <conio.h> // For _getch() on Windows
#include <limits>

// For non-Windows platforms, define a simple getch substitute
#ifndef _WIN32
int _getch() {
    int ch;
    system("stty raw");
    ch = getchar();
    system("stty cooked");
    return ch;
}
#endif

Game::Game() : currentLevel(0), gameOver(false), gameWon(false) {
    // Create 4 levels
    for (int i = 1; i <= 4; ++i) {
        levels.emplace_back(i);
    }
}

void Game::run() {
    loadLevel(1);

    while (!gameOver && !gameWon) {
        // Get the current level
        Level& level = levels[currentLevel - 1];

        // Render the level
        level.render();

        // Process input
        char input = getInput();
        processInput(input);

        // Update enemies
        moveEnemies();

        // Check for level completion
        if (level.isCompleted() && !gameOver) {
            if (!advanceToNextLevel()) {
                gameWon = true;
                showGameWonScreen();
            }
        }

        // Check for game over conditions
        checkGameOver();
    }
}

char Game::getInput() {
    char input = static_cast<char>(tolower(_getch()));

    // Validate input
    while (input != 'w' && input != 'a' && input != 's' && input != 'd' && input != 'q') {
        input = static_cast<char>(tolower(_getch()));
    }

    return input;
}

void Game::processInput(char input) {
    if (input == 'q') {
        gameOver = true;
        return;
    }

    // Movement directions
    int dx = 0, dy = 0;

    switch (input) {
        case 'w': dy = -1; break; // Up
        case 's': dy = 1; break;  // Down
        case 'a': dx = -1; break; // Left
        case 'd': dx = 1; break;  // Right
    }

    movePlayer(dx, dy);
}

void Game::movePlayer(int dx, int dy) {
    Level& level = levels[currentLevel - 1];
    Player& player = level.getPlayer();
    Maze& maze = level.getMaze();

    int newX = player.getX() + dx;
    int newY = player.getY() + dy;

    // Check if the new position is valid
    if (maze.isValidPosition(newX, newY)) {
        player.move(dx, dy);
        level.checkCollisions();
    }
}

void Game::moveEnemies() {
    Level& level = levels[currentLevel - 1];
    Maze& maze = level.getMaze();
    Player& player = level.getPlayer();

    for (auto& enemy : level.getEnemies()) {
        // Get a random direction
        auto [dx, dy] = enemy.getRandomDirection();

        int newX = enemy.getX() + dx;
        int newY = enemy.getY() + dy;

        // Check if the new position is valid
        if (maze.isValidPosition(newX, newY)) {
            enemy.setPosition(newX, newY);

            // Check for collision with player
            if (enemy.getX() == player.getX() && enemy.getY() == player.getY()) {
                gameOver = true;
                showGameOverScreen();
                return;
            }
        }
    }
}

void Game::checkGameOver() {
    Level& level = levels[currentLevel - 1];
    Player& player = level.getPlayer();

    // Check for collisions with enemies
    for (const auto& enemy : level.getEnemies()) {
        if (enemy.getX() == player.getX() && enemy.getY() == player.getY()) {
            gameOver = true;
            showGameOverScreen();
            return;
        }
    }
}

void Game::loadLevel(int levelNum) {
    if (levelNum > 0 && levelNum <= static_cast<int>(levels.size())) {
        currentLevel = levelNum;
        levels[currentLevel - 1].initialize();
    }
}

bool Game::advanceToNextLevel() {
    currentLevel++;

    if (currentLevel <= static_cast<int>(levels.size())) {
        levels[currentLevel - 1].initialize();
        return true;
    }

    return false;
}

bool Game::isGameOver() const {
    return gameOver;
}

bool Game::isGameWon() const {
    return gameWon;
}

void Game::showGameOverScreen() {
    // Clear screen
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif

    std::cout << "==================================" << std::endl;
    std::cout << "           GAME OVER!            " << std::endl;
    std::cout << "==================================" << std::endl;
    std::cout << "You were caught by an enemy!" << std::endl;

    Level& level = levels[currentLevel - 1];
    Player& player = level.getPlayer();

    std::cout << "Final Score: " << player.getScore() << std::endl;
    std::cout << "Moves Made: " << player.getMoves() << std::endl;
    std::cout << "Level Reached: " << currentLevel << std::endl;
    std::cout << "==================================" << std::endl;
    std::cout << "Press any key to exit..." << std::endl;

    _getch();
}

void Game::showGameWonScreen() {
    // Clear screen
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif

    std::cout << "==================================" << std::endl;
    std::cout << "         CONGRATULATIONS!        " << std::endl;
    std::cout << "         YOU HAVE WON!           " << std::endl;
    std::cout << "==================================" << std::endl;

    Level& level = levels[currentLevel - 1];
    Player& player = level.getPlayer();

    std::cout << "Final Score: " << player.getScore() << std::endl;
    std::cout << "Moves Made: " << player.getMoves() << std::endl;
    std::cout << "All " << levels.size() << " levels completed!" << std::endl;
    std::cout << "==================================" << std::endl;
    std::cout << "Press any key to exit..." << std::endl;

    _getch();
}