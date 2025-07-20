#ifndef INFO_H
#define INFO_H
#include <cstddef>
#include "piece.h"

//info struct is wrapper for all neccesary information pertaining to a cell

struct Info {
  int row, col;
  bool awhite, wblack;
  Piece curPiece;
  
};

#endif