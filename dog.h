#ifndef DOG_H
#define DOG_H

#include "entity.h"

class Dog : public Entity
{
private:
    bool fed;

public:
    Dog(int br, int bc, int r, int c);

    void update(Map &map) override;
    void interact(Player &player, Map &map, Display &display) override;
    int getColor() const override { return 14; }
};

#endif
