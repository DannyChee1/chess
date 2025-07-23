#include <iostream>
#include <sstream>
#include <string>
#include "gamestate.h"




int main()
{
    std::string command;
    Gamestate game;
    std::string setupstring;
    setupstring = "RNBQKBNRPPPPPPPP--------------------------------pppppppprnbqkbnr";

    //main gameloop goes here
    while (true){
         std::getline(std::cin,command);

        //std::cout << command;

        std::istringstream iss(command);

        std::string cmd;

        iss >> cmd;

         if (cmd == "white-player"){
            //std::cout << "w detected";
            std::string player1;
            iss >> player1;
            iss >> cmd;
            if (cmd == "black-player"){
                //std::cout <<"b detected";
                std::string player2;
                iss >> player2;
                if (player1 == "human"){
                    if (player2 == "human"){
                        //std::cout << "reached gamestate" << std::endl;
                        game.init(setupstring, 8, 0, 0);
                        game.printBoard();
                    }
                    
                }else{
                    std::cout << "no implemented";
                }

            }else{
                std::cerr << "bad command";

            }
        }


        else if (cmd == "move"){
            std::string piece;
            std::string originaltile;
            std::string newtile;

            iss >> originaltile; 
            iss >> newtile;

            int r1 = originaltile[1] - '0';
            int c1 = originaltile[0] - 'a' + 1;
            int r2 = newtile[1] - '0';
            int c2 = newtile[0] - 'a' + 1;


            if(game.move(r1,c1,r1,c2)){
                game.printBoard();

            }else{
                std::cerr << "bad move";
            }

        }

    }

}
