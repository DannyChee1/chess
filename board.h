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
    int rbk, cbk = 0; //position of black king
    int rwk, cwk = 0; //position of white king



  public:

    Board(int n);
    ~Board();


    void init(std::string setupstring, int n); //intializes board based on the setupstring
    //bool isStalemate(Colour turn);
    void clear(); //turns the board compeltely empty
    bool isMate(Colour turn); //checks if it was turns move, would the game be in check/stale mate
    bool isCheck(Colour turn); //checks if turn is in check
    int getDimension(); //gets n

    bool moveCheck(int r1, int c1, int r2, int c2, Colour turn); //checks if a move is a rule legal move

    bool legalBoard(Colour turn); //checks if a board is legal 

    bool checkLegality(int r1, int c1, int r2, int c2, Colour turn); //checks the overall legality of a move (if it is rule legal and if it leaves the board in a legal state)

    void movePiece(int r1, int c1, int r2, int c2); //moves a piece on the board

    void updateBoard(); //calls all of the cells on the board to notify

    void setPiece(int r, int c, Piece p); //sets a piece on the board

    std::vector<Info> getPositions(); //gets the positions 

    friend std::ostream &operator<<(std::ostream &out, const Board &b);
};


#endif