#ifndef SETUP_H
#define SETUP_H

#include "board.h"
#include "piece.h"
#include "subject.h"
#include "observer.h"
#include "gameState.h"


class Setup {
    std::string boardString;
    Colour starting_colour;
    public:
        std::string clear();
        bool isValid();
        std::string place(Piece placed_piece, std::string board, size_t row, size_t column);
        std::string remove(std::string board, size_t row, size_t column);
        std::string defaultSetup();
        void setColour(Colour colour);
};

#endif