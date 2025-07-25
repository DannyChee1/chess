#include "Setup.h"

void Setup::clear() {
    boardString = "----------------------------------------------------------------";
}

void Setup::defaultSetup() {
    boardString =  "RNBQKBNRPPPPPPPP--------------------------------pppppppprnbqkbnr";
}

bool Setup::isValid() {

    int wKingCount = 0;
    int bKingCount = 0;
    for (int i = 0; i < 8; ++i){
        for (int j = 0; j < 8; ++j){
            if(boardString[i * 8 + j] == 'k'){
                ++bKingCount;
            }else if(boardString[i * 8 + j] == 'K'){
                ++wKingCount;
            }
        }
    }
    if (bKingCount != 1 || wKingCount != 1){
        return false;
    }
    Board* temp = new Board{8};
    temp->init(boardString, 8);
    if (temp->isCheck(Colour::Black) || temp->isCheck(Colour::White)) 
        {return false;}
    delete temp;
    for(int i = 0; i < 8; ++i){
        if(boardString[i] == 'p'){
            return false;
        }
    }
    for(int i = 56; i< 64; ++i){
        if(boardString[i] == 'P'){
            return false;
        }
    }
    return true;

}

void Setup::place(char piece, int row, int column) {
    boardString[row * 8 + column] = piece;
    
}

void Setup::remove(int row, int column) {
    boardString[row * 8 + column] = '-';
}

void Setup::setColour(Colour colour) {
    startingColour = colour;
}

 std::string Setup::returnSetup(){
    return boardString;
 }
Colour Setup::returnColour(){
        return startingColour;
    }

    std::ostream &operator<<(std::ostream &out, Setup &set){
        for (int i = 7; i > -1; --i){
            for (int j = 0; j < 8; ++j){
                out << set.returnSetup()[i * 8 + j];
            }
            out << "\n";
        }
        return out;
    }