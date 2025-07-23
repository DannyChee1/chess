#ifndef GAMESTATE_H
#define GAMESTATE_H
#include "cell.h"
#include "board.h"

class Gamestate{
    Board *currBoard;
    std::vector<std::vector<Info>> history;
    int currTurn;
    Colour playerTurn;
    std::vector<std::vector<int>> move_history;

    public:
    int Player1IsBot; //0 implies human plyer, otherwise implies level of bot
    int Player2IsBot;

    void init(std::string startup, int n, int p1bot, int p2bot); //intializes game
    void switchTurn(); //switches turn
    bool move(int r1, int c1, int r2, int c2); //calls the move function on the board, first makes sure that this peice is colour of player who called for it
    char hasWon(); //returns the character w,b,s,n for who is winning in the current boardstate (w for white, b for black, s for stalemate, n for neither)
    void Rewind(int turns); //rewinds the game by amount of turns
    void printBoard(); //prints the board
}
;

#endif

#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "board.h"
#include "setup.h"

class GameState {
    Board *currBoard;
    size_t currTurn;
    Colour playerTurn;
    bool playerIsBot;
    public:
        GameState();
        ~GameState();
        void move();
        void switchTurn();
        void resign();
        Colour hasWon();
        Board* getBoard();
        void setPlayerTurn(Colour colour);
};

#endif