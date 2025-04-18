#ifndef GAME_H
#define GAME_H

#include "Level.h"

class Game {
private:
    std::vector<Level> levels;
    int currentLevel;
    bool gameOver;
    bool gameWon;

    // Input handling
    char getInput();
    void processInput(char input);

    // Move player with collision detection
    void movePlayer(int dx, int dy);

    // Move enemies with collision detection
    void moveEnemies();

    // Check for game over conditions
    void checkGameOver();

public:
    Game();

    // Game loop
    void run();

    // Level management
    void loadLevel(int levelNum);
    bool advanceToNextLevel();

    // Game state
    bool isGameOver() const;
    bool isGameWon() const;

    // Display game over/win screens
    void showGameOverScreen();
    void showGameWonScreen();
};

#endif // GAME_H