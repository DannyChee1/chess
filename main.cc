#include <iostream>
#include <sstream>
#include <string>
#include "GameState.h"
#include "Computer.h"

bool isValidCoordinate(const std::string &coord) {
    if (coord.length() != 2) return false;
    char file = coord[0];
    char rank = coord[1];
    return (file >= 'a' && file <= 'h' && rank >= '1' && rank <= '8');
}

bool isValidPromotionPiece(const std::string &piece) {
    if (piece.length() != 1) return false;
    char p = piece[0];
    return (p == 'Q' || p == 'R' || p == 'B' || p == 'N' || p == 'q' || p == 'r' || p == 'b' || p == 'n');
}

int main() {
    std::string line, player1, player2, subsection,
    setupString = "RNBQKBNRPPPPPPPP--------------------------------pppppppprnbqkbnr";
    GameState game;
    bool gameStarted = false;
    int level1 = 0, level2 = 0;
    Computer computer1, computer2;

    // Main game loop starts here
    while (true) {
        std::getline(std::cin, line);
        std::istringstream iss(line);
        if (iss >> subsection && subsection == "white-player" && iss >> player1 && 
            iss >> subsection && subsection == "black-player" && iss >> player2) {
                
            bool whiteIsValid = false, blackIsValid = false;
            if (player1 == "human") whiteIsValid = true;
            if (player2 == "human") blackIsValid = true;
            if (player1.length() == 11 && player1.substr(0, 8) == "computer" 
                && player1[9] >= '1' && player1[9] <= '4') {
                level1 = player1[9] - '0';
                whiteIsValid = true;
            }
            if (player2.length() == 11 && player2.substr(0, 8) == "computer" && player2[9] >= '1' && player2[9] <= '4') {
                level2 = player2[9] - '0';
                blackIsValid = true;
            }
            if (!whiteIsValid || !blackIsValid) {
                std::cerr << "Please enter it in this specific format: white-player X black-player Y" << std::endl;
                std::cerr << "where X and Y is either computer[a] or human" << std::endl;
                std::cerr << "where a is a number from 1 to 4" << std::endl;
                continue;
            }
            else { // game is valid and we can start
                game.init(setupString, 8, level1, level2);
                if (level1 != 0) computer1 = Computer(level1);
                if (level2 != 0) computer2 = Computer(level2);
                game.printBoard();
                gameStarted = true;
            }
        }

        else if (subsection == "move") {
            if (!gameStarted) {
                std::cerr << "Game not initialized. Please set up players first." << std::endl;
                continue;
            }

            bool isComputerTurn = false;
            if ((game.getPlayerTurn() == Colour::White && game.player1IsBot != 0) ||
                (game.getPlayerTurn() == Colour::Black && game.player2IsBot != 0))
                isComputerTurn = true;
            

            if (isComputerTurn) { // only need "move" and no extra arguments
                std::string extra;
                if (iss >> extra) {
                    std::cerr << "Invalid command: computer turn only accepts 'move'" << std::endl;
                    continue;
                }
                if (game.getPlayerTurn() == Colour::White) game = computer1.playMove(&game);
                else game = computer2.playMove(&game);
                game.printBoard();
            } 
            else {
                std::string originalTile, newTile, promotionPiece;
                
                if (!(iss >> originalTile)) {
                    std::cerr << "Invalid command: missing starting square" << std::endl;
                    continue;
                }
                
                if (!(iss >> newTile)) {
                    std::cerr << "Invalid command: missing ending square" << std::endl;
                    continue;
                }

                // TODO: If im a pawn and im at the end of the board, i can promote 
                // (handle both white and black promotion)

                bool hasPromotion = false;
                if (iss >> promotionPiece) hasPromotion = true;
                if (!isValidCoordinate(originalTile)) {
                    std::cerr << "Invalid starting square: " << originalTile << std::endl;
                    continue;
                }
                if (!isValidCoordinate(newTile)) {
                    std::cerr << "Invalid ending square: " << newTile << std::endl;
                    continue;
                }
                if (hasPromotion && !isValidPromotionPiece(promotionPiece)) {
                    std::cerr << "Invalid promotion piece: " << promotionPiece << std::endl;
                    continue;
                }

                int r1 = originalTile[1] - '1';
                int c1 = originalTile[0] - 'a';
                int r2 = newTile[1] - '1';
                int c2 = newTile[0] - 'a';


                // TODO: Handle promotion logic.

                if (game.move(r1, c1, r2, c2))
                    game.printBoard();
                else std::cerr << "bad move" << std::endl;
                
            }
        }
        else if (line == "resign") {
            if (!gameStarted) {
                std::cerr << "Game not initialized" << std::endl;
                continue;
            }
            // TODO: Implement resign logic
            std::cout << "Resign not yet implemented" << std::endl;
        }

        else std::cerr << "Invalid command: " << line << std::endl;
    }
}