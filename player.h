#ifndef PLAYER_H
#define PLAYER_H

#include "entity.h"
#include <ostream>

class Player : public Entity
{
private:
    int health;
    bool poisoned;
    int poisonCounter;
    bool hasBone;
    bool hasMap;
    bool hasScrew;

public:
    Player(int br, int bc, int r, int c);

    void move(char input, Map &map, Display &display);
    void update(Map &map) override;
    void interact(Player &player, Map &map, Display &display) override;
    void takeDamage(int amount);

    void addBone();
    void addMap();
    void addScrew();
    void removeBone();
    void setPoisoned(bool val);

    int getHealth() const;
    bool isAlive() const;
    bool isPoisoned() const;
    bool hasBoneItem() const;
    bool hasMapItem() const;
    bool hasScrewItem() const;

    int getColor() const override { return 15; }

    friend std::ostream &operator<<(std::ostream &out, const Player &p);
};

#endif
