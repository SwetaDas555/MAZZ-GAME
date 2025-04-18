#ifndef ITEM_H
#define ITEM_H

#include "Entity.h"

class Item : public Entity {
private:
    int value;
    bool collected;

public:
    Item(int x, int y, int value = 1);

    int getValue() const;
    bool isCollected() const;
    void collect();

    void update() override;
};

#endif // ITEM_H