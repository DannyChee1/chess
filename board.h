#ifndef BOARD_H
#define BOARD_H
#include <iostream>
#include <vector>
#include <cstddef>
#include <string>
#include "cell.h"
#include "attackState.h"
#include "info.h"

class TextDisplay;

class Board {
    std::vector<std::vector<Cell>> theBoard;  // The actual board.
    TextDisplay *td = nullptr; // Text display observer.
    int  n; //dimensions of the board



  public:

    ~Board();

    void init(std::string setupstring, int n);
    bool isStalemate(Colour turn);
    bool isCheckmate(Colour turn);
    bool isCheck(Colour turn);

    bool moveCheck(int r1, int c1, int r2, int c2);

    bool legalBoard(Colour turn);

    void movePiece(int r1, int c1, int r2, int c2);

    bool promote(int c, Piece peice);

    friend std::ostream &operator<<(std::ostream &out, const Board &b);
};


#endif