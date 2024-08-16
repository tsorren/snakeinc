#ifndef MAPA_H_INCLUDED
#define MAPA_H_INCLUDED


#define C_WALL '#'
#define C_AIR ' '
#define C_HEAD 'O'
#define C_BODY 'o'
#define C_FOOD '+'

#define MAP_SIZE 15

struct una_snake;

struct info_modificacion
{
    int x;
    int y;
    char nuevoChar;
    int color;
};

struct una_modificacion
{
    struct info_modificacion info;
    struct una_modificacion *sgteModificacion;
};

struct una_comida
{
    int posX;
    int posY;
};

char** mapaInicializar(struct una_modificacion **, struct una_snake, struct una_comida*);
void modificacionesPush(struct una_modificacion **, struct info_modificacion);
struct info_modificacion modificacionesPop(struct una_modificacion **);
void modificacionesAplicar(char ***, struct una_modificacion **);

void generarComida(char ***, struct una_modificacion **, struct una_comida *);

#endif // MAPA_H_INCLUDED