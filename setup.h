#ifndef SETUP_H
#define SETUP_H

#include "board.h"
#include "piece.h"
#include "subject.h"
#include "observer.h"
#include "gameState.h"
#include <string>

class Setup {
    GameState *gameState;
    public:
        std::string clear();
        bool isValid();
        std::string place(Piece placed_piece, size_t row, size_t column);
        std::string remove(size_t row, size_t column);
        std::string defaultSetup();
        void setColour(Colour starting_colour);
};

#endif