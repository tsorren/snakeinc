#ifndef RENDER_H_INCLUDED
#define RENDER_H_INCLUDED

#define PADDING_X 5
#define PADDING_Y 5

#define FBLK 30
#define FRED 31
#define FGRN 32
#define FYEL 33
#define FBLU 34
#define FMAG 35
#define FCYA 36
#define FWHT 37

#define BBLK 40
#define BRED 41
#define BGRN 42
#define BYEL 43
#define BBLU 44
#define BMAG 45
#define BCYA 46
#define BWHT 47

void setConsoleFontSize(int);
void setScreenSize(int, int);
void enableANSI();
void clearScreen();

void setColor(int , int);
void resetColor();
void moveTo(int, int);

void showCursor();
void hideCursor();

void mostrarChar(char, int, int, int);
void mostrarPuntaje(int);
#endif // RENDER_H_INCLUDED