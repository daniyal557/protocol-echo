#include "item.h"
#include "player.h"
#include "map.h"
#include "display.h"

Item::Item(int br, int bc, int r, int c, char symbol, std::string itemName)
    : Entity(br, bc, r, c, symbol), name(itemName), used(false) {}

std::string Item::getName() const { return name; }
bool Item::isUsed() const { return used; }
void Item::update(Map& map) {}
void Item::interact(Player& player, Map& map, Display& display) {}

Stew::Stew(int br, int bc, int r, int c)
    : Item(br, bc, r, c, 'S', "Stew") {}

void Stew::interact(Player& player, Map& map, Display& display) {
    if (used) return;
    player.setPoisoned(true);
    used = true;
    map.getTile(br, bc, r, c).setObject(nullptr);
    display.addMessage("You drink the stew. Something feels wrong...");
}

Bone::Bone(int br, int bc, int r, int c)
    : Item(br, bc, r, c, 'B', "Bone") {}

void Bone::interact(Player& player, Map& map, Display& display) {
    if (used) return;
    player.addBone();
    used = true;
    map.getTile(br, bc, r, c).setObject(nullptr);
    display.addMessage("You picked up a bone.");
}

MapItem::MapItem(int br, int bc, int r, int c)
    : Item(br, bc, r, c, 'M', "Map") {}

void MapItem::interact(Player& player, Map& map, Display& display) {
    if (used) return;
    player.addMap();
    used = true;
}

Screw::Screw(int br, int bc, int r, int c)
    : Item(br, bc, r, c, 'V', "Screw") {}

void Screw::interact(Player& player, Map& map, Display& display) {
    if (used) return;
    player.addScrew();
    used = true;
    map.getTile(br, bc, r, c).setObject(nullptr);
    display.addMessage("You found a small screw. Seems useless.");
}

Machine::Machine(int br, int bc, int r, int c)
    : Item(br, bc, r, c, 'T', "Machine"), solved(false), unlocked(false) {}

bool Machine::isSolved() const { return solved; }
MachinePuzzle& Machine::getPuzzle() { return puzzle; }

void Machine::interact(Player& player, Map& map, Display& display) {
    if (solved) {
        display.addMessage("The machine hums. The path is open.");
        return;
    }
    if (!player.hasMapItem()) {
        display.addMessage("You don't understand this machine yet.");
        return;
    }
    if (!unlocked) {
        unlocked = true;
        display.addMessage("The map hints at this machine's sequence.");
        return;
    }
    display.addMessage("MACHINE_PUZZLE_OPEN");
}
