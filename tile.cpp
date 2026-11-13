#include "tile.h"

Tile::Tile()
{
    baseSymbol = '|';
    walkable = true;
    occupant = nullptr;
    object = nullptr;
}

void Tile::setEmpty()
{
    baseSymbol = '|';
    walkable = true;
}

void Tile::setWall()
{
    baseSymbol = 'X';
    walkable = false;
}

char Tile::getSymbol() const
{
    return baseSymbol;
}

bool Tile::isWalkable() const
{
    return walkable;
}

void Tile::setOccupant(Entity *e)
{
    occupant = e;
}

void Tile::removeOccupant()
{
    occupant = nullptr;
}

Entity *Tile::getOccupant() const
{
    return occupant;
}

void Tile::setObject(Entity *e)
{
    object = e;
}

Entity *Tile::getObject() const
{
    return object;
}
