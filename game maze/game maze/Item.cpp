#include "Item.h"

Item::Item(int x, int y, int value) : Entity(x, y, '*'), value(value), collected(false) {}

int Item::getValue() const {
    return value;
}

bool Item::isCollected() const {
    return collected;
}

void Item::collect() {
    collected = true;
}

void Item::update() {
    // Items don't have behavior that needs updating
}