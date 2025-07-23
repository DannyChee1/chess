#include "setup.h"

std::string Setup::clear() {
    return "----------------------------------------------------------------";
}

bool Setup::isValid() {
    // Pawns are not in promotion rank or in first/last row
    // Does not contain exactly 2 kings
    // Neither king is in check
    int kingCount = 0;
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            if ((i < 1 || i > 5) && (boardString[i * j] == 'P' || boardString[i * j] == 'p'))
                return false;
            if ((i == 0 && boardString[i * j] == 'P') || (i == 6 && boardString[i * j] == 'p'))
                return false;
            if (boardString[i * j] == 'k' || boardString[i * j] == 'K')
                ++kingCount;
        }
    }
    if (kingCount != 2) return false;
    Board board {8};
    board.init(boardString, 8);
    if (board.isCheck(Colour::Black) || board.isCheck(Colour::White)) return false;
    return true;
    
}

std::string Setup::place(Piece placed_piece, std::string board, size_t row, size_t column) {
    char c;
    if (placed_piece.colour == Colour::Black) {
        if (placed_piece.type == PieceType::Pawn) c = 'p';
        if (placed_piece.type == PieceType::Knight) c = 'k';
        if (placed_piece.type == PieceType::Bishop) c = 'b';
        if (placed_piece.type == PieceType::Rook) c = 'r';
        if (placed_piece.type == PieceType::Queen) c = 'q';
        if (placed_piece.type == PieceType::King) c = 'k';
    }
    else if (placed_piece.colour == Colour::Black) {
        if (placed_piece.type == PieceType::Pawn) c = 'p';
        if (placed_piece.type == PieceType::Knight) c = 'k';
        if (placed_piece.type == PieceType::Bishop) c = 'b';
        if (placed_piece.type == PieceType::Rook) c = 'r';
        if (placed_piece.type == PieceType::Queen) c = 'q';
        if (placed_piece.type == PieceType::King) c = 'k';
    }
    else c = '-';
    board[row * column] = c;
    return board;
}

std::string Setup::remove(std::string board, size_t row, size_t column) {
    board[row * column] = '-';
    return board;
}

std::string Setup::defaultSetup() {
    return "rnbqkbnrpppppppp--------------------------------PPPPPPPPRNBQKBNR";
}

void Setup::setColour(Colour colour) {
    starting_colour = colour;
}