#include "robot.h"
#include "player.h"
#include "display.h"
using namespace std;

Robot::Robot(int br, int bc, int r, int c)
    : Entity(br, bc, r, c, 'R'), hostile(false), disabled(false) {}

void Robot::setHostile() { hostile = true; }
void Robot::disable()    { disabled = true; }
bool Robot::isHostile()  const { return hostile; }
bool Robot::isDisabled() const { return disabled; }
bool Robot::isFinalPuzzleSolved() const { return finalPuzzle.isSolved(); }
FinalPuzzle& Robot::getFinalPuzzle() { return finalPuzzle; }

int Robot::getColor() const {
    if (disabled) return 8;
    if (hostile)  return 12;
    return 9;
}

void Robot::update(Map& map) {}

void Robot::interact(Player& player, Map& map, Display& display) {
    if (disabled) {
        display.addMessage("The robot is inactive. Its core is silent.");
        return;
    }
    if (!hostile) {
        display.addMessage("Robot: Objective: Stabilize environment.");
        display.addMessage("Robot: Consume village nutrient. It is SAFE.");
        return;
    }
    display.addMessage("R0B0T: ERR0R... HUMAN SURVIVAL N0T REQUIRED.");
    if (player.hasScrewItem()) {
        display.addMessage("You see a loose panel. Press E to use screw.");
    } else {
        display.addMessage("You have nothing to fight with.");
    }
}
