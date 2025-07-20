#ifndef ATTACKSTATE_H
#define ATTACKSTATE_H
#include <cstddef>
#include "piece.h"

enum class attackType { none, diagonal, straight };

struct attackState {
  int r,c; //the coordinates of the original attacking peice 
  Colour colour; //colour of piece attacking us
  PieceType type; //type of peice that is attacking us
  attackType atype; //direciton of attack
  
};

#endif