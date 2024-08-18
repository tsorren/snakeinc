#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <math.h>

#include "mapa.h"
#include "render.h"
#include "input.h"


int main(void)
{
    hideCursor();
    setConsoleFontSize(25);
    setScreenSize(MAP_SIZE * 2 + 18,  MAP_SIZE + 7);
    enableANSI();
    clearScreen();
    
    struct una_modificacion *modifs_mapa = NULL;
    struct una_snake snake;
    struct una_comida comida;

    snakeInicializar(&snake);
    char **mapa = mapaInicializar(&modifs_mapa, snake, &comida);
    mostrarPuntaje(snake.longitud);

    char inputActual;
    bool loop = 1;
    bool comio = 0;
    _sleep(1000);
    while(loop)
    {
        inputLeer(&inputActual);
        inputProcesar(inputActual, &snake, &loop);

        /*
        moveTo(5, MAP_SIZE + 7);
        printf(" ");
        moveTo(5, MAP_SIZE + 7);
        printf("%c", inputActual);
        */

        snakeMoverse(&snake, &mapa, &modifs_mapa, &loop, &comio);
        if(comio)
        {
            generarComida(&mapa, &modifs_mapa, &comida);
            comio = 0;
        }

        modificacionesAplicar(&mapa, &modifs_mapa);
        _sleep(160/(log10(snake.longitud + 15)));
    }

    resetColor();
    free(mapa);
    moveTo(PADDING_X * 2, MAP_SIZE + PADDING_X + 1);
    printf("Fin del juego...");
    _sleep(1000);
    _getch();
    showCursor();

    return 0;
}