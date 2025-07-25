#include "GraphicsDisplay.h"
#include <iostream>

GraphicsDisplay::GraphicsDisplay(int n):size{n}{
    //draw border
    xw.fillRectangle(0,0,window_size,window_size,Xwindow::Green);
    int cellDim = board_size/size;
    for (int i = 0; i < 8; i++){
        for (int j = 0; j < 8; j++){
            if ((i + j) % 2 == 0){
                xw.fillRectangle(edge_size + j * cellDim, edge_size + (7 - i) * cellDim, cellDim, cellDim, Xwindow::Brown);
            }else{
                xw.fillRectangle(edge_size + j * cellDim, edge_size + (7 - i) * cellDim, cellDim, cellDim, Xwindow::ChessWhite);
            }
        }
    }
    
}

void GraphicsDisplay::notify(Subject &sender){
    int column=sender.getInfo().col;
    int row=sender.getInfo().row;
    int cellDim = board_size/size;
    std::cout << sender.getInfo().col << " " << sender.getInfo().col << " " ;

    
    if(sender.getInfo().curPiece.colour == Colour::White){
        switch(sender.getInfo().curPiece.type){
        case PieceType::Pawn:
            xw.drawPawn(edge_size + column * cellDim, edge_size + (7 - row)* cellDim , Xwindow::White);
            break;
        case PieceType::Knight:
            xw.drawKnight(edge_size + column * cellDim, edge_size + (7 - row)* cellDim , Xwindow::White);
            break;
        case PieceType::Bishop:
            xw.drawBishop(edge_size + column * cellDim, edge_size + (7 - row)* cellDim , Xwindow::White);
            break;
        case PieceType::Rook:
            xw.drawRook(edge_size + column * cellDim, edge_size + (7 - row)* cellDim , Xwindow::White);
            break;
        case PieceType::Queen:
            xw.drawQueen(edge_size + column * cellDim, edge_size + (7 - row)* cellDim , Xwindow::White);
            break;
        case PieceType::King:
            xw.drawKing(edge_size + column * cellDim, edge_size + (7 - row)* cellDim , Xwindow::White);
            break;
        }
    }else if(sender.getInfo().curPiece.colour == Colour::Black){
        switch(sender.getInfo().curPiece.type){
        case PieceType::Pawn:
            xw.drawPawn(edge_size + column * cellDim, edge_size + (7 - row)* cellDim , Xwindow::Black);
            break;
        case PieceType::Knight:
            xw.drawKnight(edge_size + column * cellDim, edge_size + (7 - row)* cellDim , Xwindow::Black);
            break;
        case PieceType::Bishop:
            xw.drawBishop(edge_size + column * cellDim, edge_size + (7 - row)* cellDim , Xwindow::Black);
            break;
        case PieceType::Rook:
            xw.drawRook(edge_size + column * cellDim, edge_size + (7 - row)* cellDim , Xwindow::Black);
            break;
        case PieceType::Queen:
            xw.drawQueen(edge_size + column * cellDim, edge_size + (7 - row)* cellDim , Xwindow::Black);
            break;
        case PieceType::King:
            xw.drawKing(edge_size + column * cellDim, edge_size + (7 - row)* cellDim , Xwindow::Black);
            break;
        }
    
    }
    else{
        if ((column + row) % 2 == 0){
            xw.fillRectangle(edge_size + column * cellDim, edge_size + (7 - row) * cellDim, cellDim, cellDim, Xwindow::Brown);
        }else{
            xw.fillRectangle(edge_size + column * cellDim, edge_size + (7 - row) * cellDim, cellDim, cellDim, Xwindow::ChessWhite);
        }
    }
    

}
