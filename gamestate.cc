#include "gamestate.h"

void Gamestate::init(std::string startup, int n, int p1bot, int p2bot) {
    currBoard = new Board(n);
    currBoard->init(startup, n);
    std::vector<Board*> history;
    playerTurn = Colour::White;
    Player1IsBot = p1bot;
    Player2IsBot = p2bot;
}

bool Gamestate::move(int r1, int c1, int r2, int c2){
    if(currBoard->checkLegality(r1,c1,r2,c2,playerTurn)){
        history.push_back(currBoard->getPositions());
        currBoard->movePiece(r1,c1,r2,c2);
        switchTurn();
        return true;

    }else{
        std::cout << "illegal move, select a different move";
        return false;
    }

}

void Gamestate::switchTurn(){
    if (playerTurn == Colour::Black){
        playerTurn == Colour::White;
    }else{
        playerTurn == Colour::Black;
    }
}

char Gamestate::hasWon(){
    if (currBoard->isCheck(playerTurn)){
        if (currBoard->isMate(playerTurn)){
            if (playerTurn == Colour::Black){
                return 'w';
            }else{
                return 'b';
            }
        }
    }else{
        if (currBoard->isMate(playerTurn)){
            return 's';
        }else{
            return 'n';
        }
    }
}

void Gamestate::Rewind(int turns){
    int temp = history.size();
    currBoard->clear();
    for (auto &pieces : history[history.size() - turns]) {
        currBoard->setPiece(pieces.row, pieces.col, pieces.curPiece);
    }

    history.erase(history.end() - turns, history.end());
}
    

void Gamestate::printBoard(){
    currBoard->updateBoard();
    std::cout << currBoard;

}
