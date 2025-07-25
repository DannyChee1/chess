#include "GameState.h"

void GameState::init(std::string startup, int n, int p1Bot, int p2Bot, Colour colour) {
    currBoard = new Board(n);
    currBoard->init(startup, n);
    std::vector<Board*> history;
    playerTurn = colour;
    player1IsBot = p1Bot;
    player2IsBot = p2Bot;
}

bool GameState::move(int r1, int c1, int r2, int c2) {
    if (currBoard->checkLegality(r1, c1, r2, c2, playerTurn)) {
        history.push_back(currBoard->getPositions());
        if(currBoard->getCell(r1,c1).getInfo().curPiece.type == PieceType::Pawn){
            if(c2 != c1 && currBoard->getCell(r2,c2).getInfo().curPiece.colour == Colour::Nothing){
                currBoard->setPiece(r1 ,c2,Piece{PieceType::Pawn,Colour::Nothing,0});
            }
        }
        if(currBoard->getCell(r1,c1).getInfo().curPiece.type == PieceType::King && abs(c1 - c2) > 1){
            if(c2 > c1){
                currBoard->setPiece(r1 ,7,Piece{PieceType::Pawn,Colour::Nothing,0});
                currBoard->setPiece(r1 ,5,Piece{PieceType::Rook,playerTurn,1});
            }else{
                currBoard->setPiece(r1 ,0,Piece{PieceType::Pawn,Colour::Nothing,0});
                currBoard->setPiece(r1 ,3,Piece{PieceType::Rook,playerTurn,1});

            }
        }
        Piece temp = currBoard->getCell(r1,c1).getInfo().curPiece;
        currBoard->movePiece(r1, c1, r2, c2);
        temp.previousMoves = temp.previousMoves + 1;
        currBoard->setPiece(r2,c2,temp);
        currBoard->lastMoveRow = r2;
        currBoard->lastMoveCol = c2;
        switchTurn();
        return true;
    } else {
        return false;
    }
}

void GameState::promotion(PieceType p){
    switchTurn();
    int col = currBoard->promotion(playerTurn);
    if(col >= 0){
        if (playerTurn == Colour::White){
        currBoard->setPiece(7,col,Piece{p,playerTurn,1});
    }else{
        currBoard->setPiece(0,col,Piece{p,playerTurn,1});
    }
    currBoard->updateBoard();
    currBoard->updateGraphics();

    }else{
    }
    switchTurn();

}
void GameState::switchTurn() {
    playerTurn = (playerTurn == Colour::Black) ? Colour::White : Colour::Black;
}

char GameState::hasWon() {
    if (currBoard->isCheck(playerTurn)) {
        if (currBoard->isMate(playerTurn)) {
            return (playerTurn == Colour::Black) ? 'w' : 'b';
        }else{
            return 'n';
        }
    } else {
        if (currBoard->isMate(playerTurn))
            return 's';
        else
            return 'n';
    }
}

void GameState::rewind(int turns) {
    int temp = history.size();
    currBoard->clear();
    for (auto &pieces : history[history.size() - turns])
        currBoard->setPiece(pieces.row, pieces.col, pieces.curPiece);

    history.erase(history.end() - turns, history.end());
}

void GameState::printBoard() {
    currBoard->updateBoard();
    std::cout << *currBoard;
    currBoard->updateGraphics();
}

Board* GameState::getBoard() {
    return currBoard;
}

void GameState::setPlayerTurn(Colour colour) {
    playerTurn = colour;
}

Colour GameState::getPlayerTurn() {
    return playerTurn;
}