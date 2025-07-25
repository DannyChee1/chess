#ifndef MOVE_H
#define MOVE_H

#include <string>

struct Move {
    int fromRow, fromCol, toRow, toCol;
    int moveType; // [normal=0, capture=1, check=2, capture+check=3, avoidcapture=4]
    
    Move(int fromRow, int fromCol, int toRow, int toCol, int moveType) 
    : fromRow(fromRow), fromCol(fromCol), toRow(toRow), toCol(toCol), moveType(moveType) {}
};

#endif 