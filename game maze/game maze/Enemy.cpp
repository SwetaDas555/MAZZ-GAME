#include "Enemy.h"
#include <random>
#include <chrono>

Enemy::Enemy(int x, int y) : Entity(x, y, 'X'),
                           direction(-1, 1) {
    // Initialize random number generator with time-based seed
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    rng = std::mt19937(seed);
}

std::pair<int, int> Enemy::getRandomDirection() {
    int dx = direction(rng);
    int dy = direction(rng);

    // Ensure we don't have a zero movement
    if (dx == 0 && dy == 0) {
        dx = 1;  // Default move right if both are zero
    }

    return {dx, dy};
}

void Enemy::update() {
    // Enemy movement is handled in the Game class to check for collisions
}