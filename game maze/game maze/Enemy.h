#ifndef ENEMY_H
#define ENEMY_H

#include "Entity.h"
#include <random>

class Enemy : public Entity {
private:
    std::mt19937 rng;
    std::uniform_int_distribution<int> direction;

public:
    Enemy(int x, int y);

    // Get a random direction for movement
    std::pair<int, int> getRandomDirection();

    // Implementation of the update method for random movement
    void update() override;
};

#endif // ENEMY_H