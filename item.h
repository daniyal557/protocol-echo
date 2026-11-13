#ifndef ITEM_H
#define ITEM_H
#include <string>
#include "entity.h"
#include "puzzle.h"

class Player;
class Map;
class Display;

class Item : public Entity {
protected:
    std::string name;
    bool used;
public:
    Item(int br, int bc, int r, int c, char symbol, std::string itemName);
    std::string getName() const;
    bool isUsed() const;
    void update(Map& map) override;
    void interact(Player& player, Map& map, Display& display) override;
};

class Stew : public Item {
public:
    Stew(int br, int bc, int r, int c);
    void interact(Player& player, Map& map, Display& display) override;
    int getColor() const override { return 10; }
};

class Bone : public Item {
public:
    Bone(int br, int bc, int r, int c);
    void interact(Player& player, Map& map, Display& display) override;
    int getColor() const override { return 14; }
};

class MapItem : public Item {
public:
    MapItem(int br, int bc, int r, int c);
    void interact(Player& player, Map& map, Display& display) override;
    int getColor() const override { return 11; }
};

class Screw : public Item {
public:
    Screw(int br, int bc, int r, int c);
    void interact(Player& player, Map& map, Display& display) override;
    int getColor() const override { return 8; }
};

class Machine : public Item {
private:
    bool solved;
    bool unlocked;
    MachinePuzzle puzzle;
public:
    Machine(int br, int bc, int r, int c);
    bool isSolved() const;
    MachinePuzzle& getPuzzle();
    void interact(Player& player, Map& map, Display& display) override;
    int getColor() const override { return 11; }
};

#endif
