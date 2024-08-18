#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#include "jugador.h"
#include "mapa.h"
#include "render.h"

/*

char **mapaInicializar(struct una_modificacion **, struct una_snake);
void modificacionesPush(struct una_modificacion **, struct info_modificacion);
struct info_modificacion modificacionesPop(struct una_modificacion **);
void modificacionesAplicar(char ***, struct una_modificacion **);

*/

char** mapaInicializar(struct una_modificacion **modifs, struct una_snake snake, struct una_comida* comida)
{
    srand(time(NULL));

    char **mapa = malloc(MAP_SIZE * sizeof(char*));
    for (int i = 0; i < MAP_SIZE; i++)
    {
        mapa[i] = malloc(MAP_SIZE * sizeof(char));
    }

    generarComida(&mapa, modifs, comida);

    struct info_modificacion infoMod;
    for (int i = 0; i < MAP_SIZE; i++)
    {
        for (int j = 0; j < MAP_SIZE; j++)
        {
            
            if(i % (MAP_SIZE - 1) == 0)
            {
                infoMod.nuevoChar = C_WALL;
                infoMod.color = FYEL;
            }
            else if(j % (MAP_SIZE - 1) == 0)
            {
                infoMod.nuevoChar = C_WALL;
                infoMod.color = FYEL;
            }
            else if(i == snake.cabeza->info.posX && j == snake.cabeza->info.posY)
            {
                infoMod.nuevoChar = C_HEAD;
                infoMod.color = FRED;
            }
            else if(i != comida->posX || j != comida->posY)
            {
                infoMod.nuevoChar = C_AIR;
                infoMod.color = FWHT;
            }
            infoMod.x = i;
            infoMod.y = j;
            modificacionesPush(modifs, infoMod);
        }
    }
    modificacionesAplicar(&mapa, modifs);
    return mapa;
}

void modificacionesPush(struct una_modificacion **modifs, struct info_modificacion info)
{
    struct una_modificacion *nuevaMod = malloc(sizeof(struct una_modificacion));
    
    nuevaMod->info = info;
    nuevaMod->sgteModificacion = *modifs;

    *modifs = nuevaMod;
}

struct info_modificacion modificacionesPop(struct una_modificacion **modifs)
{
    if (*modifs == NULL) {
        printf("La pila modificaciones está vacía.\n");
        exit;
    }

    struct una_modificacion *cabeza = *modifs;
    struct info_modificacion info = (*modifs)->info;

    *modifs = (*modifs)->sgteModificacion;

    free(cabeza);
    return info;
}

void modificacionesAplicar(char ***mapa, struct una_modificacion **modifs)
{
    struct info_modificacion info;
    while(*modifs != NULL)
    {
        info = modificacionesPop(modifs);
        (*mapa)[info.x][info.y] = info.nuevoChar;
        mostrarChar(info.nuevoChar, info.x, info.y, info.color);
    }
}

void generarComida(char ***mapa, struct una_modificacion **modifs, struct una_comida *comida)
{
    int x;
    int y;
    char posibleChar;
    struct info_modificacion infoMod;
    do
    {
        x = (rand() % (MAP_SIZE - 2)) + 1;
        y = (rand() % (MAP_SIZE - 2)) + 1;
        posibleChar = (*mapa)[x][y];
    } while (posibleChar == '#' || posibleChar == 'O' || posibleChar == 'o');

    infoMod.x = x;
    infoMod.y = y;
    infoMod.color = FGRN;
    infoMod.nuevoChar = C_FOOD;
    modificacionesPush(modifs, infoMod);

}