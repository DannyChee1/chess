#ifndef COMPUTER_H
#define COMPUTER_H
#include "GameState.h"

class Computer {
    GameState *gameState;
    size_t level;
    public:
        Computer();
        ~Computer();
        GameState playMove(GameState *curr_state);
};

#endif