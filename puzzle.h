#ifndef PUZZLE_H
#define PUZZLE_H
#include <string>

class MachinePuzzle {
private:
    bool solved;
    int step;
public:
    MachinePuzzle();
    bool isSolved() const;
    int getStep() const;
    bool submitChoice(int choice);
    void reset();
};

class FinalPuzzle {
private:
    bool solved;
public:
    FinalPuzzle();
    bool isSolved() const;
    bool checkAnswer(std::string input);
};

#endif
