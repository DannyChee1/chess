#include "cell.h"

#include <cstddef>
#include "piece.h"
#include "subject.h"
#include "observer.h"
#include "info.h"

Cell::Cell(Piece p, int r, int c) : r{r}, c{c}, currentPiece{p} {
    this->attackedbyWhite = false;
    this->attackedbyBlack = false;
}


void Cell::notify(Subject &whoFrom){
    Info temp = whoFrom.getInfo();
    if (temp.curPiece.colour == Colour::Nothing){

    }
}
