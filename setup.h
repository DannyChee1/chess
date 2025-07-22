#ifndef SETUP_H
#define SETUP_H

#include "board.h"
#include "piece.h"
#include "subject.h"
#include "observer.h"
#include "gameState.h"

class Setup {
    GameState *gameState;
    public:
        void clear();
        void isValid();
        void place(Piece placed_piece, size_t row, size_t column);
        void remove(size_t row, size_t column);
        void defaultSetup();
        void setColour(Colour starting_colour);
};

#endif