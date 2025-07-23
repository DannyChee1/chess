#include "gamestate.h"

void GameState::move() {
    currBoard->movePiece(r1, c1, r2, c2); //idk if this is correct
}
void GameState::switchTurn() {
    playerTurn = playerTurn == Colour::White ? Colour::Black : Colour::White;
}
void GameState::resign() {
    if (playerTurn == Colour::White)
        std::cout << "Black wins!" << std::endl;
    else 
        std::cout << "White wins!" << std::endl;
}
Colour GameState::hasWon() {
    if (currBoard->isMate(playerTurn)) {
        return playerTurn;
    }
    return Colour::Nothing;
}
Board* GameState::getBoard() {
    return currBoard;
}
void GameState::setPlayerTurn(Colour colour) {
    playerTurn = colour;
}
