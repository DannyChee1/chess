#ifndef CELL_H
#define CELL_H

#include "Piece.h"
#include "Observer.h"
#include "Subject.h"
#include "AttackState.h"

class Cell : public Subject, public Observer {
    Piece currentPiece;
    bool attackedByWhite;
    bool attackedByBlack;
    int r, c;

public: 
    Cell(Piece p, int r, int c);
    void setCell(Piece p, int row, int col); 
    void notify(Subject &sender) override;
    Info getInfo() const override;
};

#endif