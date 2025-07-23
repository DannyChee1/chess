#include "Cell.h"
#include <cstddef>
#include "Piece.h"
#include "Subject.h"
#include "Observer.h"
#include "Info.h"
#include "AttackState.h"


int abs(int x){
    if (x < 0){
        return -x;

    }else{
        return x;
    }

}
Cell::Cell(Piece p, int r, int c) : r{r}, c{c}, currentPiece{p} {
    this->attackedByWhite = false;
    this->attackedByBlack = false;
}

void Cell::setCell(Piece p, int row, int col) {
    currentPiece = p;
    r = row;
    c = col;
}

Info Cell::getInfo() const {
    return Info{this->r, this->c, this->attackedByBlack, this->attackedByWhite, this->currentPiece};
}

void Cell::notify(Subject &sender) {
    Info temp = sender.getInfo();
    AttackState stateTemp = sender.getAttackState();

    if (this->currentPiece.colour == Colour::Nothing) {
        if (stateTemp.type == PieceType::Pawn) {
            if (stateTemp.colour == Colour::Black) {
                if ((stateTemp.c - this->c == 1 || stateTemp.c - this->c == -1) && stateTemp.r - this->r == 1)
                    this->attackedByBlack = true;
            }
            if (stateTemp.colour == Colour::White) {
                if ((stateTemp.c - this->c == 1 || stateTemp.c - this->c == -1) && stateTemp.r - this->r == -1)
                    this->attackedByWhite = true;
            }
        }

        if (stateTemp.type == PieceType::Knight) {
            if ((stateTemp.c - this->c == abs(1) && stateTemp.r - this->r == abs(2)) || 
                (stateTemp.c - this->c == abs(2) && stateTemp.r - this->r == abs(1))) {
                if (stateTemp.colour == Colour::Black)
                    this->attackedByBlack = true;
                if (stateTemp.colour == Colour::White)
                    this->attackedByWhite = true;
            }
            if (abs(this->c - stateTemp.c) > abs(temp.col - stateTemp.c) || 
                abs(this->r - stateTemp.r) > abs(temp.row - stateTemp.r)) {
                setAttackState(stateTemp);
                notifyObservers();
            }
        }

        if (stateTemp.type == PieceType::Bishop) {
            if (abs(stateTemp.c - this->c) == abs(stateTemp.r - this->r)) {
                if (stateTemp.colour == Colour::Black)
                    this->attackedByBlack = true;
                if (stateTemp.colour == Colour::White)
                    this->attackedByWhite = true;
            }
            if (abs(this->c - stateTemp.c) > abs(temp.col - stateTemp.c) || 
                abs(this->r - stateTemp.r) > abs(temp.row - stateTemp.r)) {
                setAttackState(stateTemp);
                notifyObservers();
            }
        }

        if (stateTemp.type == PieceType::Rook) {
            if (stateTemp.c == this->c || stateTemp.r == this->r) {
                if (stateTemp.colour == Colour::Black)
                    this->attackedByBlack = true;
                if (stateTemp.colour == Colour::White)
                    this->attackedByWhite = true;
            }
            if (abs(this->c - stateTemp.c) > abs(temp.col - stateTemp.c) || 
                abs(this->r - stateTemp.r) > abs(temp.row - stateTemp.r)) {
                setAttackState(stateTemp);
                notifyObservers();
            }
        }

        if (stateTemp.type == PieceType::Queen) {
            if (stateTemp.atype == AttackType::Diagonal) {
                if (abs(stateTemp.c - this->c) == abs(stateTemp.r - this->r)) {
                    if (stateTemp.colour == Colour::Black)
                        this->attackedByBlack = true;
                    if (stateTemp.colour == Colour::White)
                        this->attackedByWhite = true;
                }
            } else if (stateTemp.atype == AttackType::Straight) {
                if (stateTemp.c == this->c || stateTemp.r == this->r) {
                    if (stateTemp.colour == Colour::Black)
                        this->attackedByBlack = true;
                    if (stateTemp.colour == Colour::White)
                        this->attackedByWhite = true;
                }
            }
            if (abs(this->c - stateTemp.c) > abs(temp.col - stateTemp.c) || 
                abs(this->r - stateTemp.r) > abs(temp.row - stateTemp.r)) {
                setAttackState(stateTemp);
                notifyObservers();
            }
        }

        if (stateTemp.type == PieceType::King) {
            if (abs(stateTemp.c - this->c) <= 1 && abs(stateTemp.r - this->r) <= 1) {
                if (stateTemp.colour == Colour::Black)
                    this->attackedByBlack = true;
                if (stateTemp.colour == Colour::White)
                    this->attackedByWhite = true;
            }
        }
    } else {
        if (stateTemp.type == PieceType::Pawn) {
            if (stateTemp.colour == Colour::Black) {
                if ((stateTemp.c - this->c == 1 || stateTemp.c - this->c == -1) && stateTemp.r - this->r == 1)
                    this->attackedByBlack = true;
            } else {
                if ((stateTemp.c - this->c == 1 || stateTemp.c - this->c == -1) && stateTemp.r - this->r == -1)
                    this->attackedByWhite = true;
            }
        }

        if (stateTemp.type == PieceType::Knight) {
            if ((stateTemp.c - this->c == abs(1) && stateTemp.r - this->r == abs(2)) || 
                (stateTemp.c - this->c == abs(2) && stateTemp.r - this->r == abs(1))) {
                if (stateTemp.colour == Colour::Black)
                    this->attackedByBlack = true;
                if (stateTemp.colour == Colour::White)
                    this->attackedByWhite = true;
            }
            if (abs(this->c - stateTemp.c) > abs(temp.col - stateTemp.c) || 
                abs(this->r - stateTemp.r) > abs(temp.row - stateTemp.r)) {
                setAttackState(stateTemp);
                notifyObservers();
            }
        }

        if (stateTemp.type == PieceType::Bishop) {
            if (abs(stateTemp.c - this->c) == abs(stateTemp.r - this->r)) {
                if (stateTemp.colour == Colour::Black)
                    this->attackedByBlack = true;
                if (stateTemp.colour == Colour::White)
                    this->attackedByWhite = true;
            }
        }

        if (stateTemp.type == PieceType::Rook) {
            if (stateTemp.c == this->c || stateTemp.r == this->r) {
                if (stateTemp.colour == Colour::Black)
                    this->attackedByBlack = true;
                if (stateTemp.colour == Colour::White)
                    this->attackedByWhite = true;
            }
        }

        if (stateTemp.type == PieceType::Queen) {
            if (stateTemp.atype == AttackType::Diagonal) {
                if (abs(stateTemp.c - this->c) == abs(stateTemp.r - this->r)) {
                    if (stateTemp.colour == Colour::Black)
                        this->attackedByBlack = true;
                    if (stateTemp.colour == Colour::White)
                        this->attackedByWhite = true;
                }
            } else if (stateTemp.atype == AttackType::Straight) {
                if (stateTemp.c == this->c || stateTemp.r == this->r) {
                    if (stateTemp.colour == Colour::Black)
                        this->attackedByBlack = true;
                    if (stateTemp.colour == Colour::White)
                        this->attackedByWhite = true;
                }
            }
        }

        if (stateTemp.type == PieceType::King) {
            if (abs(stateTemp.c - this->c) <= 1 && abs(stateTemp.r - this->r) <= 1) {
                if (stateTemp.colour == Colour::Black)
                    this->attackedByBlack = true;
                if (stateTemp.colour == Colour::White)
                    this->attackedByWhite = true;
            }
        }
    }
}
