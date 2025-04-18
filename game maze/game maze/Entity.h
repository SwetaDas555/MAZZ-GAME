#ifndef ENTITY_H
#define ENTITY_H

#include <utility>

// Base class for all game entities
class Entity {
protected:
    int x, y;
    char symbol;

public:
    Entity(int x, int y, char symbol);
    virtual ~Entity() = default;

    // Getters
    int getX() const;
    int getY() const;
    char getSymbol() const;

    // Setters
    void setPosition(int newX, int newY);

    // Virtual methods for entity behavior
    virtual void update() = 0;
};

#endif // ENTITY_H