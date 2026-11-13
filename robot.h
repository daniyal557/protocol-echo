#ifndef ROBOT_H
#define ROBOT_H
#include "entity.h"
#include "puzzle.h"

class Robot : public Entity {
private:
    bool hostile;
    bool disabled;
    FinalPuzzle finalPuzzle;
public:
    Robot(int br, int bc, int r, int c);
    void setHostile();
    void disable();
    bool isHostile() const;
    bool isDisabled() const;
    bool isFinalPuzzleSolved() const;
    FinalPuzzle& getFinalPuzzle();
    int getColor() const override;
    void update(Map& map) override;
    void interact(Player& player, Map& map, Display& display) override;
};

#endif
