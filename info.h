#ifndef INFO_H
#define INFO_H
#include <cstddef>
#include "piece.h"

struct Info {
  int row, col;
  bool awhite, wblack;
  Piece curPiece;
  
};

#endif