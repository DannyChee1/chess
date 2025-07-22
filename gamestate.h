#ifndef GAMESTATE_H
#define GAMESTATE_H
#include "cell.h"
#include "board.h"

class Gamestate{
    Board *currBoard;
    std::vector<Board*> history;
    int currTurn;
    Colour playerTurn;

    public:
    bool Player1IsBot;
    bool Player2IsBot;

    void init(std::string startup, int n, bool p1bot, bool p2bot); //intializes game
    void switchTurn(); //switches turn
    void move(int r1, int c1, int r2, int c2); //calls the move function on the board
    void resign();
    Colour hasWon(); //returns colour of player who is currently winning
    Board xTurnsAgo(int turns); //returns the board 
    void Rewind(int turns); //rewinds the board by 
}
;

#endif
