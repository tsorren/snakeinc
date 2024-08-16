#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#include "mapa.h"
#include "jugador.h"
#include "render.h"
#include "input.h"


int main(void)
{
    hideCursor();
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
        _sleep(200);
    }

    showCursor();
    resetColor();
    moveTo(0, MAP_SIZE + 10);
    free(mapa);
    
    return 0;
}