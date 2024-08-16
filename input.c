#include <conio.h>
#include "input.h"

void inputLeer(char *charAlmacenado)
{
    if(_kbhit())
    {
        *charAlmacenado = _getch();
    }
}

void inputProcesar(char charActual, struct una_snake* snake, bool* loop)
{
    switch(charActual)
    {
        case 'a':
        case 'A':
            snakeModificarDir(snake, IZQ);
            break;
        case 'w':
        case 'W':
            snakeModificarDir(snake, ARR);
            break;
        case 's':
        case 'S':
            snakeModificarDir(snake, ABA);
            break;
        case 'd':
        case 'D':
            snakeModificarDir(snake, DER);
            break;
        case 'p':
        case 'P':
            *loop = 0;
            break;
    }
}