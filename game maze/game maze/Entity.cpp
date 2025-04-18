#include "Entity.h"

Entity::Entity(int x, int y, char symbol) : x(x), y(y), symbol(symbol) {}

int Entity::getX() const {
    return x;
}

int Entity::getY() const {
    return y;
}

char Entity::getSymbol() const {
    return symbol;
}

void Entity::setPosition(int newX, int newY) {
    x = newX;
    y = newY;
}