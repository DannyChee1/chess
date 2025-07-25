#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <iostream>
#include <cstdlib>
#include <string>
#include <unistd.h>
#include "Window.h"

using namespace std;

Xwindow::Xwindow(int width, int height) : width{width}, height{height} {
  d = XOpenDisplay(NULL);
  if (d == NULL) {
    cerr << "Cannot open display" << endl;
    exit(1);
  }
  s = DefaultScreen(d);
  w = XCreateSimpleWindow(d, RootWindow(d, s), 10, 10, width, height, 1, BlackPixel(d, s), WhitePixel(d, s));
  XSelectInput(d, w, ExposureMask | KeyPressMask);
  XMapRaised(d, w);

  Pixmap pix = XCreatePixmap(d,w,width, height,DefaultDepth(d,DefaultScreen(d)));
  gc = XCreateGC(d, pix, 0,(XGCValues *)0);

  XFlush(d);
  XFlush(d);

  // Set up colours.
  XColor xcolour;
  Colormap cmap;
  char color_vals[8][20]={"white", "black", "red", "green", "blue", "goldenrod","#ebecd0", "goldenrod"};

  cmap=DefaultColormap(d,DefaultScreen(d));
  for(int i=0; i < 8; ++i) {
      XParseColor(d,cmap,color_vals[i],&xcolour);
      XAllocColor(d,cmap,&xcolour);
      colours[i]=xcolour.pixel;
  }

  XSetForeground(d,gc,colours[Black]);

  // Make window non-resizeable.
  XSizeHints hints;
  hints.flags = (USPosition | PSize | PMinSize | PMaxSize );
  hints.height = hints.base_height = hints.min_height = hints.max_height = height;
  hints.width = hints.base_width = hints.min_width = hints.max_width = width;
  XSetNormalHints(d, w, &hints);

  XSynchronize(d,True);

  usleep(1000);
}

Xwindow::~Xwindow() {
  XFreeGC(d, gc);
  XCloseDisplay(d);
}

int Xwindow::getWidth() const { return width; }
int Xwindow::getHeight() const { return height; }

void Xwindow::fillRectangle(int x, int y, int width, int height, int colour) {
  XSetForeground(d, gc, colours[colour]);
  XFillRectangle(d, w, gc, x, y, width, height);
  XSetForeground(d, gc, colours[Black]);
}

void Xwindow::drawPawn(int x, int y, int colour) {

    XSetForeground(d, gc, colours[colour]);
    XFillArc(d, w, gc, x + 12, y + 12, 20, 20, 0, 360*64);
    XFillRectangle(d, w, gc, x + 20, y + 30, 10, 15);
}

void Xwindow::drawKnight(int x, int y, int colour){
    XSetForeground(d, gc, colours[colour]);
    XFillRectangle(d, w, gc, x + 20, y + 30, 10, 20);

    XPoint points[] = {
        {x + 20, y + 30},
        {x + 25, y + 10},
        {x + 35, y + 18},
        {x + 30, y + 28}
    };
    XFillPolygon(d, w, gc, points, 4, Convex, CoordModeOrigin);

    XFillRectangle(d, w, gc, x + 25, y + 10, 3, 6);
}

void Xwindow::drawBishop(int x, int y, int colour) {
    XSetForeground(d, gc, colours[colour]);
    XFillArc(d, w, gc, x + 20, y + 10, 10, 10, 0, 360 * 64);
    XFillArc(d, w, gc, x + 15, y + 20, 20, 30, 0, 360 * 64);
}

void Xwindow::drawRook(int x, int y, int colour) {
    XSetForeground(d, gc, colours[colour]);
    XFillRectangle(d, w, gc, x + 12, y + 8, 6, 10);
    XFillRectangle(d, w, gc, x + 22, y + 8, 6, 10);
    XFillRectangle(d, w, gc, x + 32, y + 8, 6, 10);
    XFillRectangle(d, w, gc, x + 15, y + 18, 20, 30);
    XFillRectangle(d, w, gc, x + 12, y + 45, 26, 5);
}

void Xwindow::drawQueen(int x, int y, int colour) {
  
    XSetForeground(d, gc, colours[colour]);
    XFillArc(d, w, gc, x + 15, y + 8, 5, 5, 0, 360 * 64);
    XFillArc(d, w, gc, x + 23, y + 5, 5, 5, 0, 360 * 64);
    XFillArc(d, w, gc, x + 31, y + 8, 5, 5, 0, 360 * 64);
    XFillArc(d, w, gc, x + 17, y + 15, 16, 16, 0, 360 * 64);
    XFillArc(d, w, gc, x + 13, y + 30, 24, 20, 0, 360 * 64);
}

void Xwindow::drawKing(int x, int y, int colour) {

    XSetForeground(d, gc, colours[colour]);
    XFillArc(d, w, gc, x + 20, y + 10, 10, 10, 0, 360 * 64);
    XDrawLine(d, w, gc, x + 25, y + 5, x + 25, y + 15);
    XDrawLine(d, w, gc, x + 22, y + 10, x + 28, y + 10);
    XFillRectangle(d, w, gc, x + 20, y + 20, 10, 25);
    XFillArc(d, w, gc, x + 15, y + 43, 20, 5, 0, 360 * 64);
}
