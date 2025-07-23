#include <iostream>
#include <string>
#include "gamestate.h"




int main()
{
    std::string command;
    Gamestate game;

    //main gameloop goes here
    while (true){
        std::cin >> command;

        if (command == "white-player"){
            std::string player1;
            std::cin >> player1;
            std:: cin >> command;
            if (command == "black-player"){
                std::string player2;
                std::cin >> player2;
                if (player1 == "human"){
                    
                }else{
                    std::cout << "nit"
                }

            }else{
                std::cerr << "bad command";

            }
        }

        else if 

    }

}
