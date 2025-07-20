#ifndef CELL_H
#define CELL_H
#include "piece.h"
#include "observer.h"
#include "subject.h"
#include "attackState.h"

class Cell : public Subject, public Observer {
    Piece currentPiece;
    bool attackedbyWhite;
    bool attackedbyBlack;
    int r,c;

    public: 
        Cell(Piece p, int r, int c);
        Cell& operator=(const Cell& other);

        void notify(Subject &sender) override;

        Info getInfo() const override;
};


#endif