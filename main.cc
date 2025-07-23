#include <iostream>
#include <sstream>
#include <string>
#include "GameState.h"

int main() {
    std::string command;
    GameState game;
    std::string setupString = "RNBQKBNRPPPPPPPP--------------------------------pppppppprnbqkbnr";

    //main gameloop goes here
    while (true) {
        std::getline(std::cin, command);

        //std::cout << command;

        std::istringstream iss(command);
        std::string cmd;
        iss >> cmd;

        if (cmd == "white-player") {
            //std::cout << "w detected";
            std::string player1;
            iss >> player1;
            iss >> cmd;
            if (cmd == "black-player") {
                //std::cout <<"b detected";
                std::string player2;
                iss >> player2;
                if (player1 == "human" && player2 == "human") {
                    //std::cout << "reached gamestate" << std::endl;
                    game.init(setupString, 8, 0, 0);
                    game.printBoard();
                } 
                else {
                    std::cout << "not implemented";
                }
            } 
            else {
                std::cerr << "bad command";
            }
        } 
        else if (cmd == "move") {
            std::string originalTile;
            std::string newTile;
            iss >> originalTile; 
            iss >> newTile;

            int r1 = originalTile[0] - '0';
            int c1 = originalTile[1] - 'a' + 1;
            int r2 = newTile[0] - '0';
            int c2 = newTile[1] - 'a' + 1;

            if (game.move(r1, c1, r2, c2)) 
                game.printBoard();
            else
                std::cerr << "bad move";
        }
    }
}
