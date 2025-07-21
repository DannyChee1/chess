#include <cstddef>
#include "attackState.h"
#include "subject.h"
#include "observer.h"
#include "info.h"
#include "cell.h"
#include "board.h"
#include "textdisplay.h"
#include <string>

void Board::init (std::string setupstring, int n){
    this->n = n;
    theBoard.clear();
    theBoard.resize(n);
    td = new TextDisplay(n);

    for (int i = 0; i < this->n; i++){
        for (int j = 0; j < this->n; j++){
            theBoard[i].emplace_back(i,j);
            theBoard[i][j].attach(td);
            char temp = setupstring[this->n * i + j];
            switch(temp){
                case '-':
                    theBoard[i][j].setCell(Piece{PieceType::Pawn,Colour::Nothing, false}, false, false, i, j); 

                case 'p':
                    theBoard[i][j].setCell(Piece{PieceType::Pawn,Colour::Black, false}, false, false, i, j); ;

                case 'n':
                    theBoard[i][j].setCell(Piece{PieceType::Knight,Colour::Black, false}, false, false, i, j); 
                case 'b':
                    theBoard[i][j].setCell(Piece{PieceType::Bishop,Colour::Black, false}, false, false, i, j); 
                case 'r':
                    theBoard[i][j].setCell(Piece{PieceType::Rook,Colour::Black, false}, false, false, i, j); 
                case 'q':
                    theBoard[i][j].setCell(Piece{PieceType::Queen,Colour::Black, false}, false, false, i, j); 
                case 'k':
                    theBoard[i][j].setCell(Piece{PieceType::King,Colour::Black, false}, false, false, i, j); 
                case 'P':
                    theBoard[i][j].setCell(Piece{PieceType::Pawn,Colour::White, false}, false, false, i, j); 
                case 'N':
                     theBoard[i][j].setCell(Piece{PieceType::Knight,Colour::White, false}, false, false, i, j); 
                case 'B':
                     theBoard[i][j].setCell(Piece{PieceType::Bishop,Colour::White, false}, false, false, i, j); 
                case 'R':
                    theBoard[i][j].setCell(Piece{PieceType::Rook,Colour::White, false}, false, false, i, j); 
                case 'Q':
                    theBoard[i][j].setCell(Piece{PieceType::Queen,Colour::White, false}, false, false, i, j); 
                case 'K':
                    theBoard[i][j].setCell(Piece{PieceType::King,Colour::White, false}, false, false, i, j); 

            }



            

        }
    }
}


bool Board::moveCheck(int r1, int c1, int r2, int c2){
    if (r1 == r2 && c1 == c2){
        return false;
    }
    else if (r1 >= n || r2 >= n  || c1 >= n  || c2 >= n){
        return false;
    }
    Colour tempC;
    if (theBoard[r1][c1].getInfo().curPiece.colour == Colour::Nothing){
        return false;
    }
    else {
        tempC = theBoard[r1][c1].getInfo().curPiece.colour;
    }

    switch(theBoard[r1][c1].getInfo().curPiece.type){


        //IMPLEMENT EN PESSANT AND TWO MOVE LATER
        case PieceType::Pawn:
            if (tempC == Colour::Black){
                if (r1 == r2 + 1 && c1 == c2){
                    return (theBoard[r2][c2].getInfo().curPiece.colour == Colour::Nothing);
                }
                else if (r1 == r2 + 1 && abs(c1 - c2) == 1){
                     return (theBoard[r2][c2].getInfo().curPiece.colour == Colour::White);
                }else{
                    return false;
                }

            }else{
                if (r1 == r2 - 1 && c1 == c2){
                    return (theBoard[r2][c2].getInfo().curPiece.colour == Colour::Nothing);
                }
                else if (r1 == r2 - 1 && abs(c1 - c2) == 1){
                     return (theBoard[r2][c2].getInfo().curPiece.colour == Colour::Black);
                }else{
                    return false;
                }

            }

        case PieceType::Knight:
            if (tempC == Colour::Black){
                if (abs(r1 - r2) == 1 && abs(c1 - c2) == 2){
                    return (theBoard[r2][c2].getInfo().curPiece.colour != Colour::Black);
                }
                else if (r1 == r2 + 1 && abs(c1 - c2) == 1){
                     return (theBoard[r2][c2].getInfo().curPiece.colour != Colour::Black);
                }else{
                    return false;
                }

            }else{
                if (abs(r1 - r2) == 2 && abs(c1 - c2) == 1){
                    return (theBoard[r2][c2].getInfo().curPiece.colour != Colour::White);
                }
                else if (r1 == r2 - 1 && abs(c1 - c2) == 1){
                     return (theBoard[r2][c2].getInfo().curPiece.colour != Colour::White);
                }else{
                    return false;
                }

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
                        for (int i = 0; i < abs(r1 - r2); i++){
                            if (theBoard[r1 + i][c1 - i].getInfo().curPiece.colour != Colour::Nothing){
                                return false;
                            }

                        }

                        return (theBoard[r2][c2].getInfo().curPiece.colour != Colour::Black); 
                    }
                    else if (r1 - r2 > 0 && c1 - c2 < 0){
                        for (int i = 0; i < abs(r1 - r2); i++){
                            if (theBoard[r1 - i][c1 + i].getInfo().curPiece.colour != Colour::Nothing){
                                return false;
                            }
                        }
                        return (theBoard[r2][c2].getInfo().curPiece.colour != Colour::Black); 
                    }
                    else{
                        for (int i = 0; i < abs(r1 - r2); i++){
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
                        for (int i = 0; i < abs(r1 - r2); i++){
                            if (theBoard[r1 + i][c1 + i].getInfo().curPiece.colour != Colour::Nothing){
                                return false;
                            }

                        }

                        return (theBoard[r2][c2].getInfo().curPiece.colour != Colour::White); 
                    }
                    else if (r1 - r2 < 0 && c1 - c2 > 0){
                        for (int i = 0; i < abs(r1 - r2); i++){
                            if (theBoard[r1 + i][c1 - i].getInfo().curPiece.colour != Colour::Nothing){
                                return false;
                            }

                        }

                        return (theBoard[r2][c2].getInfo().curPiece.colour != Colour::White); 
                    }
                    else if (r1 - r2 > 0 && c1 - c2 < 0){
                        for (int i = 0; i < abs(r1 - r2); i++){
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
                        for (int i = 0; i < abs(c1 - c2); i++){
                            if (theBoard[r1][c1 + i].getInfo().curPiece.colour != Colour::Nothing){
                                return false;
                            }
                        }
                        return (theBoard[r2][c2].getInfo().curPiece.colour != Colour::Black);
                }

                    else{
                        for (int i = 0; i < abs(c1 - c2); i++){
                            if (theBoard[r1][c1 - i].getInfo().curPiece.colour != Colour::Nothing){
                                return false;
                            }
                        }
                        return (theBoard[r2][c2].getInfo().curPiece.colour != Colour::Black);
                }
            }
                else if (c1 == c2){
                     if (r1 < r2){
                        for (int i = 0; i < abs(r1 - r2); i++){
                            if (theBoard[r1 + i][c1].getInfo().curPiece.colour != Colour::Nothing){
                                return false;
                            }
                        }
                        return (theBoard[r2][c2].getInfo().curPiece.colour != Colour::Black);
                }

                    else{
                        for (int i = 0; i < abs(r1 - r2); i++){
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
                        for (int i = 0; i < abs(c1 - c2); i++){
                            if (theBoard[r1][c1 + i].getInfo().curPiece.colour != Colour::Nothing){
                                return false;
                            }
                        }
                        return (theBoard[r2][c2].getInfo().curPiece.colour != Colour::White);
                }

                    else{
                        for (int i = 0; i < abs(c1 - c2); i++){
                            if (theBoard[r1][c1 - i].getInfo().curPiece.colour != Colour::Nothing){
                                return false;
                            }
                        }
                        return (theBoard[r2][c2].getInfo().curPiece.colour != Colour::White);
                }
            }
                else if (c1 == c2){
                     if (r1 < r2){
                        for (int i = 0; i < abs(r1 - r2); i++){
                            if (theBoard[r1 + i][c1].getInfo().curPiece.colour != Colour::Nothing){
                                return false;
                            }
                        }
                        return (theBoard[r2][c2].getInfo().curPiece.colour != Colour::White);
                }

                    else{
                        for (int i = 0; i < abs(r1 - r2); i++){
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

        //IMPLEMENT CASTLING LATER

        case PieceType::King:
            if (tempC == Colour::Black){
                if (abs(r1 - r2) <= 1 && abs(c1 - c2) <= 1){
                    if (theBoard[r2][c2].getInfo().awhite){
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
                    if (theBoard[r2][c2].getInfo().ablack){
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

}


