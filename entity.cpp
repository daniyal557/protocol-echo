#include "entity.h"

Entity::Entity(int br, int bc, int r, int c, char symbol)
{
    this->br = br;
    this->bc = bc;
    this->r = r;
    this->c = c;
    this->symbol = symbol;
}

Entity::~Entity() {}

int Entity::getBlockRow() const { return br; }
int Entity::getBlockCol() const { return bc; }
int Entity::getRow() const { return r; }
int Entity::getCol() const { return c; }

char Entity::getSymbol() const { return symbol; }

void Entity::setPosition(int newBr, int newBc, int newR, int newC)
{
    br = newBr;
    bc = newBc;
    r = newR;
    c = newC;
}
