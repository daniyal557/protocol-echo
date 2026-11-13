#include "player.h"
#include "map.h"
#include "tile.h"
#include "entity.h"
#include <ostream>

std::ostream &operator<<(std::ostream &out, const Player &p)
{
    out << "Health: " << p.health;
    out << " | Poisoned: " << (p.poisoned ? "Yes" : "No");
    out << " | Bone: " << (p.hasBone ? "Yes" : "No");
    out << " | Map: " << (p.hasMap ? "Yes" : "No");
    out << " | Screw: " << (p.hasScrew ? "Yes" : "No");
    return out;
}

Player::Player(int br, int bc, int r, int c)
    : Entity(br, bc, r, c, 'P')
{
    health = 100;
    poisoned = false;
    poisonCounter = 0;

    hasBone = false;
    hasMap = false;
    hasScrew = false;
}

void Player::move(char input, Map &map, Display &display)
{
    int newBr = br, newBc = bc, newR = r, newC = c;

    if (input == 'w')
        newR--;
    else if (input == 's')
        newR++;
    else if (input == 'a')
        newC--;
    else if (input == 'd')
        newC++;
    else
        return;

    if (newR < 0)
    {
        newBr--;
        newR = Map::getBlockSize() - 1;
    }
    else if (newR >= Map::getBlockSize())
    {
        newBr++;
        newR = 0;
    }

    if (newC < 0)
    {
        newBc--;
        newC = Map::getBlockSize() - 1;
    }
    else if (newC >= Map::getBlockSize())
    {
        newBc++;
        newC = 0;
    }

    if (newBr < 0 || newBr >= 4 || newBc < 0 || newBc >= 4)
        return;

    Tile &target = map.getTile(newBr, newBc, newR, newC);

    // bump into entity → interact, stay put
    if (target.getOccupant() != nullptr)
    {
        target.getOccupant()->interact(*this, map, display);
        return;
    }

    if (!target.isWalkable())
        return;

    map.getTile(br, bc, r, c).removeOccupant();
    br = newBr;
    bc = newBc;
    r = newR;
    c = newC;
    target.setOccupant(this);

    // walk onto object → auto-interact
    Entity *obj = target.getObject();
    if (obj != nullptr)
        obj->interact(*this, map, display);
}

void Player::takeDamage(int amount)
{
    health -= amount;
    if (health < 0)
        health = 0;
}

void Player::update(Map &map)
{
    if (poisoned && health > 0)
    {
        poisonCounter++;
        if (poisonCounter >= 5)
        {
            health -= 5;
            poisonCounter = 0;
            if (health < 0)
                health = 0;
        }
    }
}

void Player::interact(Player &player, Map &map, Display &display) {}

void Player::addBone()
{
    hasBone = true;
}

void Player::addMap()
{
    hasMap = true;
}

void Player::addScrew()
{
    hasScrew = true;
}

bool Player::hasBoneItem() const
{
    return hasBone;
}

void Player::removeBone() { hasBone = false; }

bool Player::hasMapItem() const
{
    return hasMap;
}

bool Player::hasScrewItem() const
{
    return hasScrew;
}

int Player::getHealth() const { return health; }
bool Player::isPoisoned() const { return poisoned; }
void Player::setPoisoned(bool val) { poisoned = val; }
bool Player::isAlive() const { return health > 0; }
