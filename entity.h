#ifndef ENTITY_H
#define ENTITY_H

class Map;
class Player;
class Display;

class Entity
{
protected:
    int br, bc;
    int r, c;
    char symbol;

public:
    Entity(int br, int bc, int r, int c, char symbol);
    virtual ~Entity();

    int getBlockRow() const;
    int getBlockCol() const;
    int getRow() const;
    int getCol() const;
    char getSymbol() const;
    void setPosition(int newBr, int newBc, int newR, int newC);

    virtual int getColor() const { return 7; }
    virtual void update(Map &map) = 0;
    virtual void interact(Player &player, Map &map, Display &display) {}
};

#endif
