#ifndef TILE_H
#define TILE_H

class Entity;

class Tile
{
private:
    char baseSymbol;
    bool walkable;

    Entity* occupant;
    Entity* object;

public:
    Tile();

    void setEmpty();
    void setWall();

    char getSymbol() const;
    bool isWalkable() const;

    void setOccupant(Entity* e);
    void removeOccupant();
    Entity* getOccupant() const;

    void setObject(Entity* e);
    Entity* getObject() const;
};

#endif
