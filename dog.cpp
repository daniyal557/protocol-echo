#include <iostream>
#include "dog.h"
#include "player.h"
#include "display.h"

using namespace std;

Dog::Dog(int br, int bc, int r, int c)
    : Entity(br, bc, r, c, 'D')
{
    fed = false;
}

void Dog::update(Map &map)
{
    // Dog is static for now (no movement or AI)
}

void Dog::interact(Player &player, Map &map, Display &display)
{
    if (!fed)
    {
        if (player.hasBoneItem())
        {
            display.addMessage("The dog sniffs the bone and eats it.");
            display.addMessage("It drops something at your feet.");
            display.addMessage("You received the map.");
            fed = true;
            player.removeBone();
            player.addMap();
        }
        else
        {
            display.addMessage("The dog looks weak... it needs something.");
        }
    }
    else
    {
        display.addMessage("The dog sits peacefully. It trusts you.");
    }
}
