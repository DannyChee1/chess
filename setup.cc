#include "setup.h"

std::string Setup::clear() {
    Board* board = gameState->getBoard();
    int n = board->getDimension();
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j)
            board[i][j].setCell({PieceType::Pawn, Colour::Nothing, false}, i, j);
    }
    std::string result = "";
    for (int i = n; i > 0; --i) {
        result += std::to_string(i) + " ";
        for (int j = 0; j < n; ++j) {
            result += (i + j - 1) % 2 == 0 ? " " : "_";
            if (j < n - 1) result += " ";
        }
        result += "\n";
    }
    result += " ";
    for (int j = 0; j < n; ++j) {
        result += (char)('a' + j);
        if (j < n - 1) result += " ";
    }
    return result;
}

bool Setup::isValid() {
    // Assume standard positioning, i.e. pawns are in the second row and there are
    // no more than two kings of the same colour. 
    // king is not in check
    Board* board = gameState->getBoard();
    int n = board->getDimension();
    
    if (board->isCheck(Colour::White) || board->isCheck(Colour::Black))
        return false;
        
    return true;
}

std::string Setup::place(Piece placed_piece, size_t row, size_t column) {
    Board* board = gameState->getBoard();
    board[row][column].setCell(placed_piece, row, column);
    return "";
}

std::string Setup::remove(size_t row, size_t column) {
    Board* board = gameState->getBoard();
    board[row][column].setCell({PieceType::Pawn, Colour::Nothing, false}, row, column);
    return "";
}

std::string Setup::defaultSetup() {
    return "8 rnbqkbnr\n7 pppppppp\n6 _ _ _ _\n5 _ _ _ _\n4 _ _ _ _\n3 _ _ _ _\n2 PPPPPPPP\n1 RNBQKBNR\nabcdefgh";
}

void Setup::setColour(Colour starting_colour) {
    gameState->setPlayerTurn(starting_colour);
}