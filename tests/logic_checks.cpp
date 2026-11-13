#include "puzzle.h"
#include "map.h"
#include <cassert>
#include <iostream>
int main() {
    MachinePuzzle machine;
    assert(!machine.isSolved());
    assert(!machine.submitChoice(1));
    assert(machine.getStep() == 0);
    assert(machine.submitChoice(3));
    assert(!machine.submitChoice(2));
    assert(!machine.isSolved());
    assert(machine.submitChoice(1));
    assert(machine.isSolved());
    machine.reset();
    assert(machine.getStep() == 0 && !machine.isSolved());
    FinalPuzzle final;
    assert(!final.checkAnswer("NOPE"));
    assert(!final.isSolved());
    assert(final.checkAnswer("save"));
    assert(final.isSolved());
    Map map;
    assert(!map.isWalkable(-1, 0, 0, 0));
    assert(!map.isWalkable(3, 3, 0, 1));
    map.openFinalZone();
    assert(map.isWalkable(3, 3, 0, 1));
    int br, bc, r, c;
    for (int row=0; row<16; ++row) for (int col=0; col<16; ++col) {
        map.toLocal(row, col, br, bc, r, c);
        assert(map.toGlobalRow(br, r) == row);
        assert(map.toGlobalCol(bc, c) == col);
    }
    std::cout << "PASS: puzzle branches, reset, final answer, map unlock and coordinates\n";
}
