#include "gamestate.h"

void Gamestate::init(std::string startup, int n, bool p1bot, bool p2bot) : player1IsBot{p1bot} , player2IsBot{p2bot} {
    currBoard = new Board(n);

    currBoard->init(startup, n);

    playerTurn = Colour::White;


}