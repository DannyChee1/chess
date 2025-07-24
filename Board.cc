#include <cstddef>
#include "AttackState.h"
#include "Subject.h"
#include "Observer.h"
#include "Info.h"
#include "Cell.h"
#include "Board.h"
#include "TextDisplay.h"
#include <string>

Piece basic = {PieceType::Pawn, Colour::Nothing, 0};

Board::Board(int n) : n{n} {
    for (int i = 0; i < n; i++) {
        std::vector<Cell> tempRow;
        for (int j = 0; j < n; j++)
            tempRow.emplace_back(basic, i, j);
        theBoard.push_back(std::move(tempRow));
    }
    td = nullptr;
} 

void Board::init(std::string setupString, int n) {
    this->n = n;
    theBoard.clear();
    theBoard.resize(n);
    td = new TextDisplay(setupString, n);

    for (int i = 0; i < this->n; i++) {
        for (int j = 0; j < this->n; j++) {
            theBoard[i].emplace_back(basic, i, j);
            theBoard[i][j].attach(td);
            char temp = setupString[this->n * i + j];
            switch(temp) {
                case '-':
                    theBoard[i][j].setCell(Piece{PieceType::Pawn, Colour::Nothing, 0}, i, j); 
                    break;
                case 'p':
                    theBoard[i][j].setCell(Piece{PieceType::Pawn, Colour::Black, 0}, i, j);
                    break;
                case 'n':
                    theBoard[i][j].setCell(Piece{PieceType::Knight, Colour::Black, 0}, i, j); 
                    break;
                case 'b':
                    theBoard[i][j].setCell(Piece{PieceType::Bishop, Colour::Black, 0}, i, j);
                    break; 
                case 'r':
                    theBoard[i][j].setCell(Piece{PieceType::Rook, Colour::Black, 0}, i, j);
                    break; 
                case 'q':
                    theBoard[i][j].setCell(Piece{PieceType::Queen, Colour::Black, 0}, i, j);
                    break; 
                case 'k':
                    theBoard[i][j].setCell(Piece{PieceType::King, Colour::Black, 0}, i, j);
                    rbk = i;
                    cbk = j;
                    break;
                case 'P':
                    theBoard[i][j].setCell(Piece{PieceType::Pawn, Colour::White, 0}, i, j);
                    break; 
                case 'N':
                    theBoard[i][j].setCell(Piece{PieceType::Knight, Colour::White, 0}, i, j);
                    break; 
                case 'B':
                    theBoard[i][j].setCell(Piece{PieceType::Bishop, Colour::White, 0}, i, j);
                    break; 
                case 'R':
                    theBoard[i][j].setCell(Piece{PieceType::Rook, Colour::White, 0}, i, j);
                    break; 
                case 'Q':
                    theBoard[i][j].setCell(Piece{PieceType::Queen, Colour::White, 0}, i, j);
                    break; 
                case 'K':
                    theBoard[i][j].setCell(Piece{PieceType::King, Colour::White, 0}, i, j); 
                    rwk = i;
                    cwk = j;
                    break;
            }
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            // ifs check for edge cases relating to not having neighbours at the edges of the grid
            if (i == 0 && j == 0) {
                for (int k = 0; k <= i + 1; k++) {
                    for (int l = 0; l <= j + 1; l++) {
                        if (k < n && l < n && (l != j || k != i))
                            theBoard[i][j].attach(&(theBoard[k][l]));
                    }
                }
            } else if (i == 0) {
                for (int k = 0; k <= i + 1; k++) {
                    for (int l = j - 1; l <= j + 1; l++) {
                        if (k < n && l < n && (l != j || k != i))
                            theBoard[i][j].attach(&(theBoard[k][l]));
                    }
                }
            } else if (j == 0) {
                for (int k = i - 1; k <= i + 1; k++) {
                    for (int l = 0; l <= j + 1; l++) {
                        if (k < n && l < n && (l != j || k != i))
                            theBoard[i][j].attach(&(theBoard[k][l]));
                    }
                }
            } else {
                for (int k = i - 1; k <= i + 1; k++) {
                    for (int l = j - 1; l <= j + 1; l++) {
                        if (k < n && l < n && (l != j || k != i))
                            theBoard[i][j].attach(&(theBoard[k][l]));
                    }
                }
            }
        }
    }
}

int Board::getDimension() {
    return n;
}

bool Board::moveCheck(int r1, int c1, int r2, int c2, Colour turn) {
    if (r1 == r2 && c1 == c2)
        return false;
    else if (r1 >= n || r2 >= n || c1 >= n || c2 >= n)
        return false;
    
    Colour tempC;
    if (theBoard[r1][c1].getInfo().curPiece.colour != turn)
        return false;
    else
        tempC = theBoard[r1][c1].getInfo().curPiece.colour;

    switch(theBoard[r1][c1].getInfo().curPiece.type){

        //IMPLEMENT EN PESSANT AND TWO MOVE LATER
        case PieceType::Pawn:
            if (tempC == Colour::Black) {
                if (r1 == r2 + 1 && c1 == c2){
                    return (theBoard[r2][c2].getInfo().curPiece.colour == Colour::Nothing);}
                else if (r1 == r2 + 1 && abs(c1 - c2) == 1){
                    return (theBoard[r2][c2].getInfo().curPiece.colour == Colour::White);}
                else{
                    return false;}
            } else {
                if (r1 == r2 - 1 && c1 == c2){
                    return (theBoard[r2][c2].getInfo().curPiece.colour == Colour::Nothing);}
                else if (r1 == r2 - 1 && abs(c1 - c2) == 1){
                    return (theBoard[r2][c2].getInfo().curPiece.colour == Colour::Black);}
                else{
                    return false;}
            }

        case PieceType::Knight:
            if (tempC == Colour::Black) {
                if (abs(r1 - r2) == 1 && abs(c1 - c2) == 2){
                    return (theBoard[r2][c2].getInfo().curPiece.colour != Colour::Black);}
                else if (r1 == r2 + 1 && abs(c1 - c2) == 1){
                    return (theBoard[r2][c2].getInfo().curPiece.colour != Colour::Black);}
                else{
                    return false;}
            } else {
                if (abs(r1 - r2) == 2 && abs(c1 - c2) == 1){
                    return (theBoard[r2][c2].getInfo().curPiece.colour != Colour::White);}
                else if (r1 == r2 - 1 && abs(c1 - c2) == 1){
                    return (theBoard[r2][c2].getInfo().curPiece.colour != Colour::White);}
                else{
                    return false;}
            }

        case PieceType::Bishop:
             if (tempC == Colour::Black){
                if (abs(r1 - r2) ==  abs(c1 - c2)){
                    if (r1 - r2 < 0 && c1 - c2 < 0){
                        for (int i = 0; i < abs(r1 - r2); i++){
                            if (theBoard[r1 + i][c1 + i].getInfo().curPiece.colour != Colour::Nothing){
                                return false;
                            }

                        }

                        return (theBoard[r2][c2].getInfo().curPiece.colour != Colour::Black); 
                    }
                    else if (r1 - r2 < 0 && c1 - c2 > 0){
                        for (int i = 1; i < abs(r1 - r2); i++){
                            if (theBoard[r1 + i][c1 - i].getInfo().curPiece.colour != Colour::Nothing){
                                return false;
                            }

                        }

                        return (theBoard[r2][c2].getInfo().curPiece.colour != Colour::Black); 
                    }
                    else if (r1 - r2 > 0 && c1 - c2 < 0){
                        for (int i = 1; i < abs(r1 - r2); i++){
                            if (theBoard[r1 - i][c1 + i].getInfo().curPiece.colour != Colour::Nothing){
                                return false;
                            }
                        }
                        return (theBoard[r2][c2].getInfo().curPiece.colour != Colour::Black); 
                    }
                    else{
                        for (int i = 1; i < abs(r1 - r2); i++){
                            if (theBoard[r1 - i][c1 - i].getInfo().curPiece.colour != Colour::Nothing){
                                return false;
                            }

                        }

                        return (theBoard[r2][c2].getInfo().curPiece.colour != Colour::Black); 
                    }

                    
                }
                else{
                    return false;
                }

            }else{
                if (abs(r1 - r2) ==  abs(c1 - c2)){
                    if (r1 - r2 < 0 && c1 - c2 < 0){
                        for (int i = 1; i < abs(r1 - r2); i++){
                            if (theBoard[r1 + i][c1 + i].getInfo().curPiece.colour != Colour::Nothing){
                                return false;
                            }

                        }

                        return (theBoard[r2][c2].getInfo().curPiece.colour != Colour::White); 
                    }
                    else if (r1 - r2 < 0 && c1 - c2 > 0){
                        for (int i = 1; i < abs(r1 - r2); i++){
                            if (theBoard[r1 + i][c1 - i].getInfo().curPiece.colour != Colour::Nothing){
                                return false;
                            }

                        }

                        return (theBoard[r2][c2].getInfo().curPiece.colour != Colour::White); 
                    }
                    else if (r1 - r2 > 0 && c1 - c2 < 0){
                        for (int i = 1; i < abs(r1 - r2); i++){
                            if (theBoard[r1 - i][c1 + i].getInfo().curPiece.colour != Colour::Nothing){
                                return false;
                            }
                        }
                        return (theBoard[r2][c2].getInfo().curPiece.colour != Colour::White); 
                    }
                    else{
                        for (int i = 0; i < abs(r1 - r2); i++){
                            if (theBoard[r1 - i][c1 - i].getInfo().curPiece.colour != Colour::Nothing){
                                return false;
                            }

                        }

                        return (theBoard[r2][c2].getInfo().curPiece.colour != Colour::White); 
                    }

                    
                }
                else{
                    return false;
                }

            }

        case PieceType::Rook:
            if (tempC == Colour::Black){
                if (r1 == r2){
                    if (c1 < c2){
                        for (int i = 1; i < abs(c1 - c2); i++){
                            if (theBoard[r1][c1 + i].getInfo().curPiece.colour != Colour::Nothing){
                                return false;
                            }
                        }
                        return (theBoard[r2][c2].getInfo().curPiece.colour != Colour::Black);
                }

                    else{
                        for (int i = 1; i < abs(c1 - c2); i++){
                            if (theBoard[r1][c1 - i].getInfo().curPiece.colour != Colour::Nothing){
                                return false;
                            }
                        }
                        return (theBoard[r2][c2].getInfo().curPiece.colour != Colour::Black);
                }
            }
                else if (c1 == c2){
                     if (r1 < r2){
                        for (int i = 1; i < abs(r1 - r2); i++){
                            if (theBoard[r1 + i][c1].getInfo().curPiece.colour != Colour::Nothing){
                                return false;
                            }
                        }
                        return (theBoard[r2][c2].getInfo().curPiece.colour != Colour::Black);
                }

                    else{
                        for (int i = 1; i < abs(r1 - r2); i++){
                            if (theBoard[r1 - i][c1].getInfo().curPiece.colour != Colour::Nothing){
                                return false;
                            }
                        }
                        return (theBoard[r2][c2].getInfo().curPiece.colour != Colour::Black);
                }
                }else{
                    return false;
                }

            }else{
                if (r1 == r2){
                    if (c1 < c2){
                        for (int i = 1; i < abs(c1 - c2); i++){
                            if (theBoard[r1][c1 + i].getInfo().curPiece.colour != Colour::Nothing){
                                return false;
                            }
                        }
                        return (theBoard[r2][c2].getInfo().curPiece.colour != Colour::White);
                }

                    else{
                        for (int i = 1; i < abs(c1 - c2); i++){
                            if (theBoard[r1][c1 - i].getInfo().curPiece.colour != Colour::Nothing){
                                return false;
                            }
                        }
                        return (theBoard[r2][c2].getInfo().curPiece.colour != Colour::White);
                }
            }
                else if (c1 == c2){
                     if (r1 < r2){
                        for (int i = 1; i < abs(r1 - r2); i++){
                            if (theBoard[r1 + i][c1].getInfo().curPiece.colour != Colour::Nothing){
                                return false;
                            }
                        }
                        return (theBoard[r2][c2].getInfo().curPiece.colour != Colour::White);
                }

                    else{
                        for (int i = 1; i < abs(r1 - r2); i++){
                            if (theBoard[r1 - i][c1].getInfo().curPiece.colour != Colour::Nothing){
                                return false;
                            }
                        }
                        return (theBoard[r2][c2].getInfo().curPiece.colour != Colour::White);
                }
                }else{
                    return false;
                }
               

            }
            

        //I DONT WANNA DO QUEEN TOO MUCH WORK
        case PieceType::Queen:
        if (tempC == Colour::Black){
                if (abs(r1 - r2) ==  abs(c1 - c2)){
                    if (r1 - r2 < 0 && c1 - c2 < 0){
                        for (int i = 1; i < abs(r1 - r2); i++){
                            if (theBoard[r1 + i][c1 + i].getInfo().curPiece.colour != Colour::Nothing){
                                return false;
                            }

                        }

                        return (theBoard[r2][c2].getInfo().curPiece.colour != Colour::Black); 
                    }
                    else if (r1 - r2 < 0 && c1 - c2 > 0){
                        for (int i = 1; i < abs(r1 - r2); i++){
                            if (theBoard[r1 + i][c1 - i].getInfo().curPiece.colour != Colour::Nothing){
                                return false;
                            }

                        }

                        return (theBoard[r2][c2].getInfo().curPiece.colour != Colour::Black); 
                    }
                    else if (r1 - r2 > 0 && c1 - c2 < 0){
                        for (int i = 1; i < abs(r1 - r2); i++){
                            if (theBoard[r1 - i][c1 + i].getInfo().curPiece.colour != Colour::Nothing){
                                return false;
                            }
                        }
                        return (theBoard[r2][c2].getInfo().curPiece.colour != Colour::Black); 
                    }
                    else{
                        for (int i = 1; i < abs(r1 - r2); i++){
                            if (theBoard[r1 - i][c1 - i].getInfo().curPiece.colour != Colour::Nothing){
                                return false;
                            }

                        }

                        return (theBoard[r2][c2].getInfo().curPiece.colour != Colour::Black); 
                    }

                    
                }
                if (r1 == r2){
                    if (c1 < c2){
                        for (int i = 1; i < abs(c1 - c2); i++){
                            if (theBoard[r1][c1 + i].getInfo().curPiece.colour != Colour::Nothing){
                                return false;
                            }
                        }
                        return (theBoard[r2][c2].getInfo().curPiece.colour != Colour::Black);
                }

                    else{
                        for (int i = 1; i < abs(c1 - c2); i++){
                            if (theBoard[r1][c1 - i].getInfo().curPiece.colour != Colour::Nothing){
                                return false;
                            }
                        }
                        return (theBoard[r2][c2].getInfo().curPiece.colour != Colour::Black);
                }
            }
                else if (c1 == c2){
                     if (r1 < r2){
                        for (int i = 1; i < abs(r1 - r2); i++){
                            if (theBoard[r1 + i][c1].getInfo().curPiece.colour != Colour::Nothing){
                                return false;
                            }
                        }
                        return (theBoard[r2][c2].getInfo().curPiece.colour != Colour::Black);
                }

                    else{
                        for (int i = 1; i < abs(r1 - r2); i++){
                            if (theBoard[r1 - i][c1].getInfo().curPiece.colour != Colour::Nothing){
                                return false;
                            }
                        }
                        return (theBoard[r2][c2].getInfo().curPiece.colour != Colour::Black);
                }
                }  else{
                    return false;
                }

            }else{
                if (abs(r1 - r2) ==  abs(c1 - c2)){
                    if (r1 - r2 < 0 && c1 - c2 < 0){
                        for (int i = 1; i < abs(r1 - r2); i++){
                            if (theBoard[r1 + i][c1 + i].getInfo().curPiece.colour != Colour::Nothing){
                                return false;
                            }

                        }

                        return (theBoard[r2][c2].getInfo().curPiece.colour != Colour::White); 
                    }
                    else if (r1 - r2 < 0 && c1 - c2 > 0){
                        for (int i = 1; i < abs(r1 - r2); i++){
                            if (theBoard[r1 + i][c1 - i].getInfo().curPiece.colour != Colour::Nothing){
                                return false;
                            }

                        }

                        return (theBoard[r2][c2].getInfo().curPiece.colour != Colour::White); 
                    }
                    else if (r1 - r2 > 0 && c1 - c2 < 0){
                        for (int i = 1; i < abs(r1 - r2); i++){
                            if (theBoard[r1 - i][c1 + i].getInfo().curPiece.colour != Colour::Nothing){
                                return false;
                            }
                        }
                        return (theBoard[r2][c2].getInfo().curPiece.colour != Colour::White); 
                    }
                    else{
                        for (int i = 1; i < abs(r1 - r2); i++){
                            if (theBoard[r1 - i][c1 - i].getInfo().curPiece.colour != Colour::Nothing){
                                return false;
                            }

                        }

                        return (theBoard[r2][c2].getInfo().curPiece.colour != Colour::White); 
                    }

                    
                }
                if (r1 == r2){
                    if (c1 < c2){
                        for (int i = 1; i < abs(c1 - c2); i++){
                            if (theBoard[r1][c1 + i].getInfo().curPiece.colour != Colour::Nothing){
                                return false;
                            }
                        }
                        return (theBoard[r2][c2].getInfo().curPiece.colour != Colour::White);
                }

                    else{
                        for (int i = 1; i < abs(c1 - c2); i++){
                            if (theBoard[r1][c1 - i].getInfo().curPiece.colour != Colour::Nothing){
                                return false;
                            }
                        }
                        return (theBoard[r2][c2].getInfo().curPiece.colour != Colour::White);
                }
            }
                else if (c1 == c2){
                     if (r1 < r2){
                        for (int i = 1; i < abs(r1 - r2); i++){
                            if (theBoard[r1 + i][c1].getInfo().curPiece.colour != Colour::Nothing){
                                return false;
                            }
                        }
                        return (theBoard[r2][c2].getInfo().curPiece.colour != Colour::White);
                }

                    else{
                        for (int i = 1; i < abs(r1 - r2); i++){
                            if (theBoard[r1 - i][c1].getInfo().curPiece.colour != Colour::Nothing){
                                return false;
                            }
                        }
                        return (theBoard[r2][c2].getInfo().curPiece.colour != Colour::White);
                }
                }
                else{
                    return false;
                }
            }

        //IMPLEMENT CASTLING LATER

        case PieceType::King:
            if (tempC == Colour::Black){
                if (abs(r1 - r2) <= 1 && abs(c1 - c2) <= 1){
                    if (theBoard[r2][c2].getInfo().aWhite){
                        return false;
                    }else{
                        return theBoard[r2][c2].getInfo().curPiece.colour != Colour::Black;
                    }

                }
                else{
                    return false;
                }

            }else{
                if (abs(r1 - r2) <= 1 && abs(c1 - c2) <= 1){
                    if (theBoard[r2][c2].getInfo().aBlack){
                        return false;
                    }else{
                        return theBoard[r2][c2].getInfo().curPiece.colour != Colour::White;
                    }

                }
                else{
                    return false;
                }
                

            }
            
    }
    return true;

}

void Board::clear(){
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            theBoard[i][j].setCell(Piece{PieceType::Pawn,Colour::Nothing,0},i,j);
        }
    }
}
void Board::updateBoard(){
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            theBoard[i][j].notifyObservers();
        }
    }
}

void Board::setPiece(int r, int c, Piece p){
    theBoard[r][c].setCell(p,r,c);
    updateBoard();
}

bool Board::legalBoard(Colour turn){
    if (turn == Colour::Black){
        return !(theBoard[rwk][rwk].getInfo().aBlack);
    }else{
        return !(theBoard[rbk][cbk].getInfo().aWhite);
}

}

bool Board::isCheck(Colour turn){
    if (turn == Colour::Black){

        return !(theBoard[rbk][cbk].getInfo().aWhite);
    
    }else{
        return !(theBoard[rwk][cwk].getInfo().aBlack);
        
    }
} 


void Board::movePiece(int r1, int c1, int r2, int c2){

    if (theBoard[r1][c1].getInfo().curPiece.type == PieceType::King){
        if(theBoard[r1][c1].getInfo().curPiece.colour == Colour::Black){
            rbk = r2;
            cbk = c2; 
        }else{
            rwk = r2;
            cwk = c2;
        }
    }

    theBoard[r2][c2].setCell(theBoard[r1][c1].getInfo().curPiece, r2, c2);
    theBoard[r1][c1].setCell(Piece{PieceType::Pawn, Colour::Nothing, false}, r1, c1);

    
    updateBoard();


}

//checks the legality of a potential future move.
bool Board::checkLegality(int r1, int c1, int r2, int c2, Colour turn){
    if (moveCheck(r1,c1,r2,c2,turn)){
        Piece temp = theBoard[r2][c2].getInfo().curPiece; 
        movePiece(r1,c1,r2,c2);
        if (turn == Colour::Black){
            if(legalBoard(Colour::White)){
                movePiece(r2,c2,r1,c1);
                theBoard[r2][c2].setCell(temp, r2, c2);
                updateBoard();
                return true;

            }else{
                movePiece(r2,c2,r1,c1);
                theBoard[r2][c2].setCell(temp, r2, c2);
                updateBoard();
                return false;
            }
        } else{

            if(legalBoard(Colour::Black)){
                movePiece(r2,c2,r1,c1);
                theBoard[r2][c2].setCell(temp, r2, c2);
                updateBoard();
                return true;

            }else{
                std::cout << "not legal position";
                movePiece(r2,c2,r1,c1);
                theBoard[r2][c2].setCell(temp, r2, c2);
                updateBoard();
                return false;
            }
        }

    }
    else{
        return false;}
}

//acts as a stalemate check if isCheck is false, is a checkmate check if isCheck is true

bool Board::isMate(Colour turn){
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            for (int l = 0; l < n; l++){
                for (int k = 0; k < n; k++){
                    if(checkLegality(i,j,k,l,turn)){
                        return false;
                    }
                }
            }
        }
    }

    return true;

}

std::vector<Info> Board::getPositions(){
    std::vector<Info> positions;
    for (int  i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            if (theBoard[i][j].getInfo().curPiece.colour != Colour::Nothing){
                positions.push_back(theBoard[i][j].getInfo());
            }
        }
    }

    return positions;
}
std::pair<int, int> Board::getKingPosition(Colour colour) {
    return (colour == Colour::White) ? std::make_pair(rwk, cwk) : std::make_pair(rbk, cbk);
}

Cell Board::getCell(int r, int c) {
    return theBoard[r][c];
}

std::vector<Info> Board::generateLegalMoves(int r, int c) {
    std::vector<Info> legalMoves;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == r && j == c) continue;
            if (checkLegality(r, c, i, j, theBoard[r][c].getInfo().curPiece.colour))
                legalMoves.push_back(theBoard[i][j].getInfo());
        }
    }
    return legalMoves;
}

std::ostream &operator<<(std::ostream &out, const Board &b){
    out << *(b.td);
    return out;
}
