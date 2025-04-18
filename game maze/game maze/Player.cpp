//
// Created by Acer on 3/29/2025.
//

#include "Player.h"

Player::Player(int x, int y) : Entity(x, y, 'P'), score(0), moves(0) {}

int Player::getScore() const {
    return score;
}

int Player::getMoves() const {
    return moves;
}

void Player::increaseScore(int amount) {
    score += amount;
}

void Player::incrementMoves() {
    moves++;
}

void Player::move(int dx, int dy) {
    x += dx;
    y += dy;
    incrementMoves();
}

void Player::update() {
    // Player updates are handled by input in the Game class
}