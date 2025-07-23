#ifndef INFO_H
#define INFO_H

#include <cstddef>
#include "Piece.h"

// Info struct is wrapper for all necessary information pertaining to a cell
struct Info {
    int row, col;
    bool aWhite, aBlack;
    Piece curPiece;
};

#endif