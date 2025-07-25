#ifndef SETUP_H
#define SETUP_H

#include "Board.h"
#include "Piece.h"
#include "Subject.h"
#include "Observer.h"
#include "GameState.h"

class Setup{
    std::string boardString = "RNBQKBNRPPPPPPPP--------------------------------pppppppprnbqkbnr" ;
    Colour startingColour = Colour::White;

public:
    void clear();
    bool isValid();
    void place(char piece, int row, int column);
    void remove(int row, int column);
    void defaultSetup();
    void setColour(Colour colour);
    std::string returnSetup();
    Colour returnColour();
    friend std::ostream &operator<<(std::ostream &out, Setup &set);
};

std::ostream &operator<<(std::ostream &out, Setup &set);


#endif
