#ifndef __WINDOW_H
#define __WINDOW_H
#include <X11/Xlib.h>
#include <iostream>
#include <string>

class Xwindow {
  Display *d;
  Window w;
  int s, width, height;
  GC gc;
  unsigned long colours[5];

 public:
  Xwindow(int width=500, int height=500);  
  ~Xwindow();                              

  enum {White=0, Black, Red, Green, Blue, B, ChessWhite, Brown}; 

  int getWidth() const;
  int getHeight() const;

  // Draws a rectangle
  void fillRectangle(int x, int y, int width, int height, int colour);

  // Draws a string
  void drawString(int x, int y, std::string msg);

  void drawPawn(int x, int y, int colour);
  void drawKnight(int x, int y, int colour);
  void drawBishop(int x, int y, int colour);
  void drawRook(int x, int y, int colour);
  void drawQueen(int x, int y, int colour);
  void drawKing(int x, int y, int colour);
};

#endif
