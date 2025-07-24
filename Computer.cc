#include "Computer.h"
#include <random>
#include <chrono>

GameState Computer::playMove(GameState *curr_state) {
    // Assume that the board is 8x8
    Colour computer_colour = curr_state->getPlayerTurn();
    Board *board = curr_state->getBoard();
    if (level == 1) { // random legal moves
        std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>> legalMoves;
        
        /*
        You currently have the current computer's colour. Find the king's position, and if it is in checkmate, then cerr something
        went wrong checkmate. If it is in stalement, then cerr something went wrong stalemate. If it is in check, then
        add all legal moves to legal_moves. Then, go to every other colour's piece and then add all their possible moves to legal_moves.
        Then, randomly choose a move from legal_moves and play that move.
        */
        // Check for checkmate or stalemate
        if (board->isMate(computer_colour)) {
            if (board->isCheck(computer_colour)) {
                std::cerr << "Something went wrong: checkmate" << std::endl;
                return *curr_state;
            }
            else {
                std::cerr << "Something went wrong: stalemate" << std::endl;
                return *curr_state;
            }
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                Cell cell = board->getCell(i, j);
                Piece piece = cell.getInfo().curPiece;

                if (piece.colour == computer_colour) {
                    std::vector<Info> moves = board->generateLegalMoves(i, j);
                    for (const Info &move : moves) 
                        legalMoves.push_back({{i, j}, {move.row, move.col}});
                }
            }
        }
        if (legalMoves.empty()) {
            std::cerr << "No legal moves found" << std::endl;
            return *curr_state;
        }
        // Mersenne Twister
        std::mt19937 gen(std::chrono::system_clock::now().time_since_epoch().count());
        std::uniform_int_distribution<> distribution(0, legalMoves.size() - 1);
        int randIndex = distribution(gen);
        
        std::pair<std::pair<int, int>, std::pair<int, int>> selected = legalMoves[randIndex];
        
        GameState new_state = *curr_state;
        new_state.move(selected.first.first, selected.first.second, selected.second.first, selected.second.second);
        return new_state;
    }
    
    // Other levels not implemented
    return *curr_state;
}
}

