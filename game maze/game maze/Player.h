#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"

class Player : public Entity {
private:
    int score;
    int moves;

public:
    virtual void move();  // Ensure this has a definition in Player.cpp
    virtual ~Player() {}  // Virtual destructor to prevent vtable issues
    Player(int x, int y);

    int getScore() const;
    int getMoves() const;

    void increaseScore(int amount = 1);
    void incrementMoves();

    // Move the player in a direction (dx, dy)
    void move(int dx, int dy);

    // Implementation of the update method
    void update() override;
};

#endif // PLAYER_H