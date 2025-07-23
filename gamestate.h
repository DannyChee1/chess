#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "Board.h"
#include "Setup.h"

class GameState {
    Board *currBoard;
    std::vector<std::vector<Info>> history;
    int currTurn;
    Colour playerTurn;
    std::vector<std::vector<int>> moveHistory;
    int player1IsBot; // 0 implies human player, otherwise implies level of bot
    int player2IsBot;

public:
    GameState();
    ~GameState();
    
    void init(std::string startup, int n, int p1Bot, int p2Bot);
    void switchTurn();
    bool move(int r1, int c1, int r2, int c2);
    char hasWon(); // returns 'w', 'b', 's', 'n' for who is winning
    void rewind(int turns);
    void printBoard();
    Board* getBoard();
    void setPlayerTurn(Colour colour);
};

#endif