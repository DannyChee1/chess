#ifndef SETUP_H
#define SETUP_H

#include "Board.h"
#include "Piece.h"
#include "Subject.h"
#include "Observer.h"
#include "GameState.h"

class Setup {
    std::string boardString;
    Colour startingColour;

public:
    std::string clear();
    bool isValid();
    std::string place(Piece placedPiece, std::string board, size_t row, size_t column);
    std::string remove(std::string board, size_t row, size_t column);
    std::string defaultSetup();
    void setColour(Colour colour);
};

#endif
