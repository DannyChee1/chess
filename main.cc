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
    char p = piece[0];
    return (p == 'Q' || p == 'R' || p == 'B' || p == 'K' || p == 'q' || p == 'r' || p == 'b' || p == 'k');
}

int main() {
    std::string line, player1, player2, command,
    setupString = "RNBQKBNRPPPPPPPP--------------------------------pppppppprnbqkbnr";
    std::string promotiontest = "--------p-----------K-------------k--------------------P--------";
    GameState game;
    bool gameStarted = false;
    int level1 = 0, level2 = 0;
    Computer computer1, computer2;
    double blackScore = 0;
    double whiteScore = 0;
    bool playing = true;
    Colour setupColour = Colour::White;

    // Main game loop starts here
    while (playing) {
        std::getline(std::cin, line);
        if(std::cin.eof()){
            playing = false;
        }
        std::istringstream iss(line);
        if (iss >> command && command == "game" && iss >> player1 && iss >> player2) {
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
                game.init(setupString, 8, level1, level2, setupColour);
                if (level1 != 0) computer1 = Computer(level1);
                if (level2 != 0) computer2 = Computer(level2);
                game.printBoard();
                gameStarted = true;
            }
        }

        else if (command == "move") {
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
                if (game.getPlayerTurn() == Colour::White) game = computer1.playMove(&game, level1);
                else game = computer2.playMove(&game, level2);
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



                if (game.move(r1, c1, r2, c2)){
                    if(hasPromotion == true){
                        if(promotionPiece[0] == 'q' || promotionPiece[0] == 'Q'){
                            game.promotion(PieceType::Queen);
                        }else if(promotionPiece[0] == 'R' || promotionPiece[0] == 'r'){
                            game.promotion(PieceType::Rook);
                        }else if(promotionPiece[0] == 'b' || promotionPiece[0] == 'B'){
                            game.promotion(PieceType::Bishop);
                        }else {
                            game.promotion(PieceType::Knight);}

                    }
                    //game.printBoard();
                    
                    if(game.hasWon() == 'b'){
                        std::cout << "Black wins!";
                        gameStarted = false;
                        ++blackScore; 
                    }else if(game.hasWon() == 'w'){
                        std::cout << "White wins!";
                        gameStarted = false;
                        ++whiteScore; 
                    }else if(game.hasWon() == 's'){
                        std::cout << "Stalemate ...";
                        gameStarted = false;
                        whiteScore = whiteScore + 0.5; 
                        blackScore = blackScore + 0.5; 
                    }
                    
                }
                else std::cerr << "Not A Legal Move" << std::endl;
                
            }
        }
        else if (line == "resign") {
            if (!gameStarted) {
                std::cerr << "Game not initialized" << std::endl;
                continue;
            }
            else{
                if(game.getPlayerTurn() == Colour::White){
                    std::cout << "White resigns! \n";
                    std::cout << "Black wins! \n";
                    gameStarted = false;
                    ++blackScore;
                    
                }else{
                    std::cout << "Black resigns! \n";
                    std::cout << "White wins! \n";
                    gameStarted = false;
                    ++whiteScore;

                }
            }
            
        }else if (command == "setup"){
            if(!gameStarted){
            bool setup = true;
            Setup temp;
            while(setup){
                
                std::getline(std::cin, line);
                std::istringstream iss(line);

                std::string command;
                std::string cmd2;
                std::string cmd3;
                if(iss >> command){
                    if(command == "+"){
                        if(iss >> cmd2){
                            if(cmd2[0] == 'P' ||cmd2[0] == 'p' ||cmd2[0] == 'R' ||cmd2[0] == 'r' ||cmd2[0] == 'B' ||cmd2[0] == 'b' ||cmd2[0] == 'Q' ||cmd2[0] == 'q' ||cmd2[0] == 'N' ||cmd2[0] == 'n' ||cmd2[0] == 'k' || cmd2[0] == 'K'){
                            if(iss >> cmd3){
                                int r1 = cmd3[1] - '1';
                                int c1 = cmd3[0] - 'a';
                                temp.place(cmd2[0], r1,c1);
                                std::cout << temp;

                            }else{
                                std::cerr << "bad command \n" ;

                            }
                        }
                        }else{
                                std::cerr << "bad command \n" ;

                            }


                    }else if(command == "-"){
                        if(iss >> cmd2){
                            int r1 = cmd2[1] - '1';
                            int c1 = cmd2[0] - 'a';
                            temp.remove(r1,c1);
                            std::cout << temp;
                    }else{
                        std::cerr << "error";
                    }
                }else if(command == "="){
                    if(iss >> cmd2){
                        if(cmd2 == "white" || cmd2 == "White"){
                            temp.setColour(Colour::White);
                        }else if(cmd2 == "black" || cmd2 == "Black"){
                            temp.setColour(Colour::Black);
                        }else{
                            std::cerr << "not black or white";
                    }
                }


                }else if(command == "done"){
                    if(temp.isValid()){
                        setupColour = temp.returnColour();
                        setupString = temp.returnSetup();
                        setup = false;
                    }else{
                        std::cerr<<"not valid board";
                    }
                }else{
                    std::cerr <<"not a command";
                }

        }}
        }else{
            std::cerr << "cannot call setup in a game";
        }
    }

        else std::cerr << "Invalid command: " << line << std::endl;
    }

    std::cout << "Final Score: \nWhite: " << whiteScore << "\nBlack: " << blackScore;

    
}