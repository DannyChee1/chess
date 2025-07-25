#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include <vector>
#include <cstddef>
#include <string>
#include "Cell.h"
#include "AttackState.h"
#include "Info.h"


class TextDisplay;

class GraphicsDisplay;

class Board {
    std::vector<std::vector<Cell>> theBoard;  // The actual board
    TextDisplay *td = nullptr; // Text display observer
    GraphicsDisplay *gd = nullptr;
    int n; // dimensions of the board
    int rbk, cbk = 0; // position of black king
    int rwk, cwk = 0; // position of white king

public:
    int lastMoveRow = 0;
    int lastMoveCol = 0;
    Board(int n);
    Board(const Board& other); // Copy constructor
    ~Board();
    Board& operator=(const Board& other); // Copy Assignment

    void init(std::string setupString, int n);
    void clear(); // turns the board completely empty
    bool isMate(Colour turn); // checks if it was turn's move, would the game be in check/stale mate
    bool isCheck(Colour turn); // checks if turn is in check
    int getDimension(); // gets n

    bool moveCheck(int r1, int c1, int r2, int c2, Colour turn); // checks if a move is a rule legal move
    bool legalBoard(Colour turn); // checks if a board is legal 
    bool checkLegality(int r1, int c1, int r2, int c2, Colour turn); // checks the overall legality of a move
    void movePiece(int r1, int c1, int r2, int c2); // moves a piece on the board
    void updateBoard(); // calls all of the cells on the board to notify
    void setPiece(int r, int c, Piece p); // sets a piece on the board
    std::vector<Info> getPositions(); // gets the positions 
    std::pair<int, int> getKingPosition(Colour colour); // gets the position of the king of the given colour
    std::vector<Info> generateLegalMoves(int r, int c); // generates the legal moves for a given position
    Cell getCell(int r, int c); // gets a cell
    friend std::ostream &operator<<(std::ostream &out, const Board &b);
    void updateGraphics();
};

#endif
