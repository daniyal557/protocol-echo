#include "puzzle.h"
#include <string>
#include <algorithm>
using namespace std;

MachinePuzzle::MachinePuzzle() {
    solved = false;
    step = 0;
}

bool MachinePuzzle::isSolved() const { return solved; }
int MachinePuzzle::getStep() const { return step; }

bool MachinePuzzle::submitChoice(int choice) {
    if (step == 0) {
        if (choice == 3) {
            step = 1;
            return true;
        } else {
            return false;
        }
    } else if (step == 1) {
        if (choice == 1) {
            solved = true;
            return true;
        } else {
            return false;
        }
    }
    return false;
}

void MachinePuzzle::reset() {
    solved = false;
    step = 0;
}

FinalPuzzle::FinalPuzzle() { solved = false; }
bool FinalPuzzle::isSolved() const { return solved; }

bool FinalPuzzle::checkAnswer(string input) {
    transform(input.begin(), input.end(), input.begin(), ::toupper);
    if (input == "SAVE") {
        solved = true;
        return true;
    }
    return false;
}
