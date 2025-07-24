#include "GraphicsDisplay.h"



GraphicsDisplay::GraphicsDisplay(size_t n):size{n}{
    //draw border
    xw.fillRectangle(0,0,WINDOW_SIZE,WINDOW_SIZE,Xwindow::Green);
    //draw grid
    xw.fillRectangle(BORDER_SIZE-1,BORDER_SIZE-1,size*(GRID_SIZE/size),size*(GRID_SIZE/size),Xwindow::Blue);
    for (int i=0;i<=size;++i){
        xw.fillRectangle(BORDER_SIZE-1+i*(GRID_SIZE/size),BORDER_SIZE-1,1,size*(GRID_SIZE/size));
    }
    for (int i=0;i<=size;++i){
        xw.fillRectangle(BORDER_SIZE-1,BORDER_SIZE-1+i*(GRID_SIZE/size),size*(GRID_SIZE/size),1);
    }
}

void GraphicsDisplay::notify(Subject &sender){
    int column=sender.getInfo().col;
    int row=sender.getInfo().row;
    if (sender.getInfo().curPiece.colour==Colour::Black){
        xw.fillRectangle(BORDER_SIZE+column*(GRID_SIZE/size),BORDER_SIZE+row*(GRID_SIZE/size),(GRID_SIZE/size)-1,(GRID_SIZE/size)-1,Xwindow::Black);
    }
    if (sender.getInfo().curPiece.colour==Colour::White){
        xw.fillRectangle(BORDER_SIZE+column*(GRID_SIZE/size),BORDER_SIZE+row*(GRID_SIZE/size),(GRID_SIZE/size)-1,(GRID_SIZE/size)-1,Xwindow::White);
    }
}
