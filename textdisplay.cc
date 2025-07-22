#include <vector>
#include "textdisplay.h"
#include "observer.h"
#include "attackState.h"
#include "info.h"
#include "subject.h"


//potentially check this, not sure if this constructor is properly made
TextDisplay::TextDisplay(std::string setupString, int n): boardSize{n} {
    std::vector<std::vector<char>> display;
    display.resize(n);
    for (int i = 0; i < n ; i++){
        for (int j = 0; j < n; j++){
            display[i][j] = setupString[i * n + j];

        }
    }

}

void TextDisplay::notify(Subject &sender){
    Piece temp = sender.getInfo().curPiece;
    switch(temp.type){
        case(PieceType::Pawn): 
            if (temp.colour == Colour::Nothing){
                display[sender.getInfo().row][sender.getInfo().col] = '-';
            }
            else if (temp.colour == Colour::Black){
                display[sender.getInfo().row][sender.getInfo().col] = 'p';
            }else if(temp.colour == Colour::White){
                display[sender.getInfo().row][sender.getInfo().col] = 'P'; 
            }else{
                std::cerr << "bad colour from textdisplay notify";
            }
        
        case(PieceType::Knight): 
            if (temp.colour == Colour::Nothing){
                display[sender.getInfo().row][sender.getInfo().col] = '-';
            }
            else if (temp.colour == Colour::Black){
                display[sender.getInfo().row][sender.getInfo().col] = 'n';
            }else if(temp.colour == Colour::White){
                display[sender.getInfo().row][sender.getInfo().col] = 'N'; 
            }else{
                std::cerr << "bad colour from textdisplay notify";
            }
        
        case(PieceType::Bishop): 
            if (temp.colour == Colour::Nothing){
                display[sender.getInfo().row][sender.getInfo().col] = '-';
            }
            else if (temp.colour == Colour::Black){
                display[sender.getInfo().row][sender.getInfo().col] = 'b';
            }else if(temp.colour == Colour::White){
                display[sender.getInfo().row][sender.getInfo().col] = 'B'; 
            }else{
                std::cerr << "bad colour from textdisplay notify";
            }
        
        case(PieceType::Rook): 
            if (temp.colour == Colour::Nothing){
                display[sender.getInfo().row][sender.getInfo().col] = '-';
            }
            else if (temp.colour == Colour::Black){
                display[sender.getInfo().row][sender.getInfo().col] = 'r';
            }else if(temp.colour == Colour::White){
                display[sender.getInfo().row][sender.getInfo().col] = 'R'; 
            }else{
                std::cerr << "bad colour from textdisplay notify";
            }
        
        case(PieceType::Queen): 
            if (temp.colour == Colour::Nothing){
                display[sender.getInfo().row][sender.getInfo().col] = '-';
            }
            else if (temp.colour == Colour::Black){
                display[sender.getInfo().row][sender.getInfo().col] = 'q';
            }else if(temp.colour == Colour::White){
                display[sender.getInfo().row][sender.getInfo().col] = 'Q'; 
            }else{
                std::cerr << "bad colour from textdisplay notify";
            }
        
        case(PieceType::King): 
            if (temp.colour == Colour::Nothing){
                display[sender.getInfo().row][sender.getInfo().col] = '-';
            }
            else if (temp.colour == Colour::Black){
                display[sender.getInfo().row][sender.getInfo().col] = 'k';
            }else if(temp.colour == Colour::White){
                display[sender.getInfo().row][sender.getInfo().col] = 'K'; 
            }else{
                std::cerr << "bad colour from textdisplay notify";
            }
            
    }
}

std::ostream &operator<<(std::ostream &out, const TextDisplay &td){
    for (int i = 0; i < td.boardSize; i++){
        for (int j = 0; j < td.boardSize; j++){
            out << td.display[i][j];
        }
        out << "\n";
    }

    return out;
}
