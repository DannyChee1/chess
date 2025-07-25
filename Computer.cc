#include "Computer.h"
#include "Move.h"
#include <random>
#include <chrono>
#include <vector>

Computer::~Computer() {
    delete gameState;
}

GameState Computer::playMove(GameState *curr_state, int level) {
    // Assume that the board is 8x8
    Colour computer_colour = curr_state->getPlayerTurn();
    Board *board = curr_state->getBoard();
    
    if (level == 1) { // random legal moves
        std::vector<Move> legalMoves;
        
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
        }
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                Cell cell = board->getCell(i, j);
                Piece piece = cell.getInfo().curPiece;

                if (piece.colour == computer_colour) {
                    std::vector<Info> moves = board->generateLegalMoves(i, j);
                    for (const Info &move : moves) 
                        legalMoves.emplace_back(i, j, move.row, move.col, 0); // normal move type
                }
            }
        }
        if (legalMoves.empty()) {
            std::cerr << "No legal moves found" << std::endl;
            return *curr_state;
        }
        
        // Print all legal moves
        std::cout << "Legal moves for " << (computer_colour == Colour::White ? "White" : "Black") << ":" << std::endl;
        for (const auto &move : legalMoves) {
            char fromFile = 'a' + move.fromCol;
            char fromRank = '1' + move.fromRow;
            char toFile = 'a' + move.toCol;
            char toRank = '1' + move.toRow;
            std::cout << "  " << fromFile << fromRank << " " << toFile << toRank << std::endl;
        }
        
        // Mersenne Twister
        std::mt19937 gen(std::chrono::system_clock::now().time_since_epoch().count());
        std::uniform_int_distribution<> distribution(0, legalMoves.size() - 1);
        int randIndex = distribution(gen);
        
        Move selected = legalMoves[randIndex];
        
        // Print the selected move
        char fromFile = 'a' + selected.fromCol;
        char fromRank = '1' + selected.fromRow;
        char toFile = 'a' + selected.toCol;
        char toRank = '1' + selected.toRow;
        std::cout << "Computer chooses: From (" << fromFile << " , " << fromRank << ") to ("
        << toFile << " , " << toRank << ") type = move" << std::endl;
        
        GameState new_state = *curr_state;
        new_state.move(selected.fromRow, selected.fromCol, selected.toRow, selected.toCol);
        return new_state;
    }
    
    else if (level == 2) { // prefers captures and checks
        std::vector<Move> priorityMoves; // captures and checks
        std::vector<Move> normalMoves;
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
        }

        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                Cell cell = board->getCell(i, j);
                Piece piece = cell.getInfo().curPiece;

                if (piece.colour == computer_colour) {
                    std::vector<Info> moves = board->generateLegalMoves(i, j);
                    for (const Info &move : moves) {
                        bool isCapture = (board->getCell(move.row, move.col).getInfo().curPiece.colour != Colour::Nothing);
                        bool isCheck = false;
                        if (board->checkLegality(i, j, move.row, move.col, computer_colour)) {
                            // create a copy of the board to test the move
                            Board testBoard = *board;
                            
                            testBoard.movePiece(i, j, move.row, move.col);
                            isCheck = testBoard.isCheck((computer_colour == Colour::White) ? Colour::Black : Colour::White);
                        }
                        if (isCapture || isCheck) {
                            int moveType = 0;
                            if (isCapture && isCheck) moveType = 3; // capture+check
                            else if (isCapture) moveType = 1; // capture
                            else if (isCheck) moveType = 2; // check
                            priorityMoves.emplace_back(i, j, move.row, move.col, moveType);
                        } 
                        else normalMoves.emplace_back(i, j, move.row, move.col, 0); // normal
                    }
                }
            }
        }
        std::vector<Move> legalMoves = (priorityMoves.empty()) ? normalMoves : priorityMoves;
        if (legalMoves.empty()) {
            std::cerr << "No legal moves found" << std::endl;
            return *curr_state;
        }

        std::cout << "Legal moves for " << (computer_colour == Colour::White ? "White" : "Black") << ":" << std::endl;
        if (!priorityMoves.empty()) {
            std::cout << "Priority moves:" << std::endl;
            for (const auto &move : priorityMoves) {
                char fromFile = 'a' + move.fromCol;
                char fromRank = '1' + move.fromRow;
                char toFile = 'a' + move.toCol;
                char toRank = '1' + move.toRow;
                std::string moveTypeStr;
                switch(move.moveType) {
                    case 0: moveTypeStr = "normal"; break;
                    case 1: moveTypeStr = "capture"; break;
                    case 2: moveTypeStr = "check"; break;
                    case 3: moveTypeStr = "capture+check"; break;
                    default: moveTypeStr = "unknown"; break;
                }
                std::cout << "From (" << fromFile << " , " << fromRank << ") to ("
                << toFile << " , " << toRank << ") type = " << moveTypeStr << std::endl;
            }
        }
        if (!normalMoves.empty()) {
            std::cout << "Normal moves:" << std::endl;
            for (const auto& move : normalMoves) {
                char fromFile = 'a' + move.fromCol;
                char fromRank = '1' + move.fromRow;
                char toFile = 'a' + move.toCol;
                char toRank = '1' + move.toRow;
                std::cout << "From (" << fromFile << " , " << fromRank << ") to ("
                << toFile << " , " << toRank << ") type = move" << std::endl;
            }
        }
        
        std::mt19937 gen(std::chrono::system_clock::now().time_since_epoch().count());
        std::uniform_int_distribution<> distribution(0, legalMoves.size() - 1);
        int randIndex = distribution(gen);
        
        Move selected = legalMoves[randIndex];
        
        char fromFile = 'a' + selected.fromCol;
        char fromRank = '1' + selected.fromRow;
        char toFile = 'a' + selected.toCol;
        char toRank = '1' + selected.toRow;
        std::string moveTypeStr;
        switch(selected.moveType) {
            case 0: moveTypeStr = "normal"; break;
            case 1: moveTypeStr = "capture"; break;
            case 2: moveTypeStr = "check"; break;
            case 3: moveTypeStr = "capture+check"; break;
            default: moveTypeStr = "unknown"; break;
        }
        std::cout << "Computer chooses: From (" << fromFile << " , " << fromRank << ") to ("
        << toFile << " , " << toRank << ") type = " << moveTypeStr << std::endl;
        
        GameState new_state = *curr_state;
        new_state.move(selected.fromRow, selected.fromCol, selected.toRow, selected.toCol);
        return new_state;
    }
    else if (level == 3) { // prefers captures, checks, and avoiding capture
        std::vector<Move> priorityMoves; // captures, checks, and avoiding capture
        std::vector<Move> normalMoves;
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
        }

        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                Cell cell = board->getCell(i, j);
                Piece piece = cell.getInfo().curPiece;

                if (piece.colour == computer_colour) {
                    std::vector<Info> moves = board->generateLegalMoves(i, j);
                    for (const Info &move : moves) {
                        bool isCapture = (board->getCell(move.row, move.col).getInfo().curPiece.colour != Colour::Nothing);
                        bool isCheck = false;
                        bool isAvoidCapture = false;
                        
                        // Check if current piece is under attack
                        bool isAttacked = false;
                        if (computer_colour == Colour::White) 
                            isAttacked = board->getCell(i, j).getInfo().aBlack;
                        else isAttacked = board->getCell(i, j).getInfo().aWhite;
                        
                        if (board->checkLegality(i, j, move.row, move.col, computer_colour)) {
                            Board testBoard = *board;
                            
                            testBoard.movePiece(i, j, move.row, move.col);
                            testBoard.updateBoard(); // Ensure attack states are updated
                            
                            isCheck = testBoard.isCheck((computer_colour == Colour::White) ? Colour::Black : Colour::White);
                            
                            // destination safe?
                            if (isAttacked) {
                                if (computer_colour == Colour::White)
                                    isAvoidCapture = !testBoard.getCell(move.row, move.col).getInfo().aBlack;
                                else
                                    isAvoidCapture = !testBoard.getCell(move.row, move.col).getInfo().aWhite;
                            }
                        }
                        
                        if (isAvoidCapture) {
                            int moveType = 4; // avoiding capture
                            priorityMoves.emplace_back(i, j, move.row, move.col, moveType);
                        } 
                        else if (isCapture || isCheck) {
                            int moveType = 0;
                            if (isCapture && isCheck) moveType = 3; // capture+check
                            else if (isCapture) moveType = 1; // capture
                            else if (isCheck) moveType = 2; // check
                            priorityMoves.emplace_back(i, j, move.row, move.col, moveType);
                        } 
                        else normalMoves.emplace_back(i, j, move.row, move.col, 0); // normal
                    }
                }
            }
        }
        std::vector<Move> legalMoves = (priorityMoves.empty()) ? normalMoves : priorityMoves;
        if (legalMoves.empty()) {
            std::cerr << "No legal moves found" << std::endl;
            return *curr_state;
        }

        std::cout << "Legal moves for " << (computer_colour == Colour::White ? "White" : "Black") << ":" << std::endl;
        if (!priorityMoves.empty()) {
            std::cout << "Priority moves:" << std::endl;
            for (const auto &move : priorityMoves) {
                char fromFile = 'a' + move.fromCol;
                char fromRank = '1' + move.fromRow;
                char toFile = 'a' + move.toCol;
                char toRank = '1' + move.toRow;
                std::string moveTypeStr;
                switch(move.moveType) {
                    case 0: moveTypeStr = "normal"; break;
                    case 1: moveTypeStr = "capture"; break;
                    case 2: moveTypeStr = "check"; break;
                    case 3: moveTypeStr = "capture+check"; break;
                    case 4: moveTypeStr = "avoiding_capture"; break;
                    default: moveTypeStr = "unknown"; break;
                }
                std::cout << "From (" << fromFile << " , " << fromRank << ") to ("
                << toFile << " , " << toRank << ") type = " << moveTypeStr << std::endl;
            }
        }
        if (!normalMoves.empty()) {
            std::cout << "Normal moves:" << std::endl;
            for (const auto& move : normalMoves) {
                char fromFile = 'a' + move.fromCol;
                char fromRank = '1' + move.fromRow;
                char toFile = 'a' + move.toCol;
                char toRank = '1' + move.toRow;
                std::cout << "From (" << fromFile << " , " << fromRank << ") to ("
                << toFile << " , " << toRank << ") type = move" << std::endl;
            }
        }

        std::mt19937 gen(std::chrono::system_clock::now().time_since_epoch().count());
        std::uniform_int_distribution<> distribution(0, legalMoves.size() - 1);
        int randIndex = distribution(gen);
        
        Move selected = legalMoves[randIndex];
        
        char fromFile = 'a' + selected.fromCol;
        char fromRank = '1' + selected.fromRow;
        char toFile = 'a' + selected.toCol;
        char toRank = '1' + selected.toRow;
        std::string moveTypeStr;
        switch(selected.moveType) {
            case 0: moveTypeStr = "normal"; break;
            case 1: moveTypeStr = "capture"; break;
            case 2: moveTypeStr = "check"; break;
            case 3: moveTypeStr = "capture+check"; break;
            case 4: moveTypeStr = "avoiding_capture"; break;
            default: moveTypeStr = "unknown"; break;
        }
        std::cout << "Computer chooses: From (" << fromFile << " , " << fromRank << ") to ("
        << toFile << " , " << toRank << ") type = " << moveTypeStr << std::endl;
        
        GameState new_state = *curr_state;
        new_state.move(selected.fromRow, selected.fromCol, selected.toRow, selected.toCol);
        return new_state;
    }
    
    // Other levels not implemented
    return *curr_state;
}


