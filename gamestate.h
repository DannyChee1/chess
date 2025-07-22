#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "board.h"
#include "setup.h"

class GameState {
    Board *currBoard;
    size_t currTurn;
    Colour playerTurn;
    bool playerIsBot;
    public:
        GameState();
        ~GameState();
        void move();
        void switchTurn();
        void resign();
        Colour hasWon();
};

#endif