#include "cell.h"

#include <cstddef>
#include "piece.h"
#include "subject.h"
#include "observer.h"
#include "info.h"
#include "attackState.h"


Cell::Cell(Piece p, int r, int c) : r{r}, c{c}, currentPiece{p} {
    this->attackedbyWhite = false;
    this->attackedbyBlack = false;
}

//write assignment copy operator later;


Info Cell::getInfo() const{
    return Info{this->r, this->c, this->attackedbyBlack, this->attackedbyWhite, this->currentPiece};
    
}

void Cell::notify(Subject &sender){
    Info temp = sender.getInfo();
    attackState stateTemp = sender.getAttackState();

    if (this->currentPiece.colour == Colour::Nothing){
        if (stateTemp.type == PieceType::Pawn){
            if(stateTemp.colour == Colour::Black){
                if ((stateTemp.c - this->c == 1  || stateTemp.c - this->c == -1) && stateTemp.r - this->r == 1){
                    this->attackedbyBlack = true;
                }
            }
            if(stateTemp.colour == Colour::White){
                if ( (stateTemp.c - this->c == 1  || stateTemp.c - this->c == -1) && stateTemp.r - this->r == -1){
                    this->attackedbyWhite = true;
                }
            }

        }

        if (stateTemp.type == PieceType::Knight){
            if((stateTemp.c - this->c == abs(1) && stateTemp.r - this->r == abs(2)) || (stateTemp.c - this->c == abs(2) && stateTemp.r - this->r == abs(1))){
                if(stateTemp.colour == Colour::Black){
                     this->attackedbyBlack = true;
                }
                if(stateTemp.colour == Colour::White){
                    this->attackedbyWhite = true;
                }
                
            }if (abs(this->c - stateTemp.c) > abs(temp.col - stateTemp.c) || abs(this->r - stateTemp.r) > abs(temp.row - stateTemp.r)){
               setAttackState(stateTemp);
               notifyObservers();
            }

        }

        if (stateTemp.type == PieceType::Bishop){
            if (abs(stateTemp.c - this->c) == abs(stateTemp.r - this->r)){
                if(stateTemp.colour == Colour::Black){
                     this->attackedbyBlack = true;
                }
                if(stateTemp.colour == Colour::White){
                    this->attackedbyWhite = true;
                }
            }
            if (abs(this->c - stateTemp.c) > abs(temp.col - stateTemp.c) || abs(this->r - stateTemp.r) > abs(temp.row - stateTemp.r)){
               setAttackState(stateTemp);
               notifyObservers();
            }

        }

        if (stateTemp.type == PieceType::Rook){
            if (stateTemp.c == this->c || stateTemp.r == this->r){
                if(stateTemp.colour == Colour::Black){
                     this->attackedbyBlack = true;
                }
                if(stateTemp.colour == Colour::White){
                    this->attackedbyWhite = true;
                }
            }

            if (abs(this->c - stateTemp.c) > abs(temp.col - stateTemp.c) || abs(this->r - stateTemp.r) > abs(temp.row - stateTemp.r)){
               setAttackState(stateTemp);
               notifyObservers();
            }

        }

        if (stateTemp.type == PieceType::Queen){
            if (stateTemp.atype == attackType::diagonal){
                if (abs(stateTemp.c - this->c) == abs(stateTemp.r - this->r)){
                    if(stateTemp.colour == Colour::Black){
                        this->attackedbyBlack = true;
                }
                    if(stateTemp.colour == Colour::White){
                        this->attackedbyWhite = true;
                }
            }
                 

            }else if (stateTemp.atype == attackType::straight){
                if (stateTemp.c == this->c || stateTemp.r == this->r){
                    if(stateTemp.colour == Colour::Black){
                        this->attackedbyBlack = true;
                    }
                    if(stateTemp.colour == Colour::White){
                        this->attackedbyWhite = true;
                }
            }

            }else {

            }

            if (abs(this->c - stateTemp.c) > abs(temp.col - stateTemp.c) || abs(this->r - stateTemp.r) > abs(temp.row - stateTemp.r)){
               setAttackState(stateTemp);
               notifyObservers();
            }


        }

        if (stateTemp.type == PieceType::King){
            if (abs(stateTemp.c - this->c) <= 1 && abs(stateTemp.r - this->r) <= 1){
                if(stateTemp.colour == Colour::Black){
                     this->attackedbyBlack = true;
                }
                if(stateTemp.colour == Colour::White){
                    this->attackedbyWhite = true;
                }
            }

        }else{

        }
           
    }else{

         if (stateTemp.type == PieceType::Pawn){

            if(stateTemp.colour == Colour::Black){
                if ((stateTemp.c - this->c == 1  || stateTemp.c - this->c == -1) && stateTemp.r - this->r == 1){
                    this->attackedbyBlack = true;
                }
            }
            else{
                if ( (stateTemp.c - this->c == 1  || stateTemp.c - this->c == -1) && stateTemp.r - this->r == -1){
                    this->attackedbyWhite = true;
                }
            }

        }

        if (stateTemp.type == PieceType::Knight){
            if((stateTemp.c - this->c == abs(1) && stateTemp.r - this->r == abs(2)) || (stateTemp.c - this->c == abs(2) && stateTemp.r - this->r == abs(1))){
                if(stateTemp.colour == Colour::Black){
                     this->attackedbyBlack = true;
                }
                if(stateTemp.colour == Colour::White){
                    this->attackedbyWhite = true;
                }
                
            }if (abs(this->c - stateTemp.c) > abs(temp.col - stateTemp.c) || abs(this->r - stateTemp.r) > abs(temp.row - stateTemp.r)){
               setAttackState(stateTemp);
               notifyObservers();
            }

        }

        if (stateTemp.type == PieceType::Bishop){
            if (abs(stateTemp.c - this->c) == abs(stateTemp.r - this->r)){
                if(stateTemp.colour == Colour::Black){
                     this->attackedbyBlack = true;
                }
                if(stateTemp.colour == Colour::White){
                    this->attackedbyWhite = true;
                }
            }

        }

        if (stateTemp.type == PieceType::Rook){
            if (stateTemp.c == this->c || stateTemp.r == this->r){
                if(stateTemp.colour == Colour::Black){
                     this->attackedbyBlack = true;
                }
                if(stateTemp.colour == Colour::White){
                    this->attackedbyWhite = true;
                }
            }

        }

        if (stateTemp.type == PieceType::Queen){
            if (stateTemp.atype == attackType::diagonal){
                if (abs(stateTemp.c - this->c) == abs(stateTemp.r - this->r)){
                    if(stateTemp.colour == Colour::Black){
                        this->attackedbyBlack = true;
                }
                    if(stateTemp.colour == Colour::White){
                        this->attackedbyWhite = true;
                }
            }
                 

            }else if (stateTemp.atype == attackType::straight){
                if (stateTemp.c == this->c || stateTemp.r == this->r){
                    if(stateTemp.colour == Colour::Black){
                        this->attackedbyBlack = true;
                    }
                    if(stateTemp.colour == Colour::White){
                        this->attackedbyWhite = true;
                }
            }else {

            }
        }

        if (stateTemp.type == PieceType::King){
            if (abs(stateTemp.c - this->c) <= 1 && abs(stateTemp.r - this->r) <= 1){
                if(stateTemp.colour == Colour::Black){
                     this->attackedbyBlack = true;
                }
                if(stateTemp.colour == Colour::White){
                    this->attackedbyWhite = true;
                }
            }

        }
    
    }

    }

}
