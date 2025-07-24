#ifndef COMPUTER_H
#define COMPUTER_H
#include "GameState.h"

class Computer {
    GameState *gameState;
    size_t level = 1;
    public:
        Computer() = default;
        Computer(size_t level) : level(level) {}
        ~Computer();
        GameState playMove(GameState *curr_state);
};

#endif