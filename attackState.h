#ifndef ATTACKSTATE_H
#define ATTACKSTATE_H

#include <cstddef>
#include "Piece.h"

enum class AttackType { None, Diagonal, Straight };

struct AttackState {
    int r, c; // the coordinates of the original attacking piece 
    Colour colour; // colour of piece attacking us
    PieceType type; // type of piece that is attacking us
    AttackType atype; // direction of attack
};

#endif