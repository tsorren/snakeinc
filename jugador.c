#include<stdio.h>
#include<stdlib.h>
#include "jugador.h"
#include "mapa.h"
#include "render.h"

struct una_parte* snakeCrecer(struct una_snake* snake, struct info_parte info)
{
    snake->longitud++;
    struct una_parte* nuevaParte = malloc(sizeof(struct una_parte));
    nuevaParte->info = info;
    nuevaParte->sgteParte = NULL;

    if(snake->cabeza == NULL)
        snake->cabeza = nuevaParte;
    else
        snake->cola->sgteParte = nuevaParte;

    snake->cola = nuevaParte;
    return nuevaParte;
}

void snakeInicializar(struct una_snake* snake)
{
    snake->longitud = 0;
    snake->cabeza = NULL;
    snake->cola = NULL;
    snake->dir = ARR;
    struct info_parte info;
    info.posX = MAP_SIZE / 2;
    info.posY = MAP_SIZE / 2;

    snakeCrecer(snake, info);
}

void snakeModificarDir(struct una_snake* snake, enum direcciones dir)
{
    if((dir == IZQ || dir == DER) && (snake->dir == IZQ || snake->dir == DER))
        return;
    if((dir == ARR || dir == ABA) && (snake->dir == ARR || snake->dir == ABA))
        return;
    snake->dir = dir;
}

bool snakePuedeMoverse(int x, int y, char **mapa, bool* comio)
{
    bool noSeChoca = (mapa[x][y] != C_WALL) && (mapa[x][y] != C_HEAD) && (mapa[x][y] != C_BODY);
    bool noSeSale = 0 < x && x < MAP_SIZE && 0 < y && y < MAP_SIZE;

    if(mapa[x][y] == C_FOOD)
    {
        *comio = 1;
    }
    return noSeChoca && noSeSale;
}

void snakeMoverse(struct una_snake *snake, char ***mapa, struct una_modificacion **modifs, bool* loop, bool* comio)
{
    struct una_parte *cuerpo = snake->cabeza;
    struct info_modificacion infoMod;
    bool puedeMoverse = 0;

    int movX = 0;
    int movY = 0;
    int *x = &snake->cabeza->info.posX;
    int* y = &snake->cabeza->info.posY;

    switch(snake->dir)
    {
        case IZQ: movX = -1; break;
        case ARR: movY = -1; break;
        case ABA: movY = 1; break;
        case DER: movX = 1; break;
    }
    
    // Comprueba si la snake puede moverse
    puedeMoverse = snakePuedeMoverse(*x + movX, *y + movY, *mapa, comio);

    if(puedeMoverse)
    {
        struct una_parte *nuevaParte = NULL;
        if(*comio)
        {
            struct info_parte nuevaParteInfo;
            if(snake->cola == NULL)
            {
                nuevaParteInfo = snake->cabeza->info;
            }
            else
            {
                nuevaParteInfo = snake->cola->info;
            }
            nuevaParte = snakeCrecer(snake, nuevaParteInfo);
            mostrarPuntaje(snake->longitud);
        }
        else
        {
            if(snake->cola == NULL)
            {
                infoMod.color = FWHT;
                infoMod.nuevoChar = C_AIR;
                infoMod.x = snake->cabeza->info.posX;
                infoMod.y = snake->cabeza->info.posY;
                modificacionesPush(modifs, infoMod);
            }
            else
            {
                infoMod.color = FWHT;
                infoMod.nuevoChar = C_AIR;
                infoMod.x = snake->cola->info.posX;
                infoMod.y = snake->cola->info.posY;
                modificacionesPush(modifs, infoMod);
            }
        }
        if(snake->cabeza->sgteParte != NULL)
        {
            infoMod.color = FRED;
            infoMod.nuevoChar = C_BODY;
            infoMod.x = snake->cabeza->info.posX;
            infoMod.y = snake->cabeza->info.posY;
            modificacionesPush(modifs, infoMod);
        }

        int auxX = cuerpo->info.posX;
        int auxY = cuerpo->info.posY;
        int prevX;
        int prevY;

        while(cuerpo->sgteParte != NULL && cuerpo->sgteParte != nuevaParte)
        {
            prevX = cuerpo->sgteParte->info.posX;
            prevY = cuerpo->sgteParte->info.posY;
            cuerpo->sgteParte->info.posX = auxX;
            cuerpo->sgteParte->info.posY = auxY;
            auxX = prevX;
            auxY = prevY;
            cuerpo = cuerpo->sgteParte;
        }

        *x = *x + movX;
        *y = *y + movY;

        infoMod.color = FRED;
        infoMod.nuevoChar = C_HEAD;
        infoMod.x = snake->cabeza->info.posX;
        infoMod.y = snake->cabeza->info.posY;
        modificacionesPush(modifs, infoMod);
    }
    else
    {
        *loop = 0;
    }
}