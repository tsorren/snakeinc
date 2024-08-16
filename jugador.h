#ifndef JUGADOR_H_INCLUDED

struct una_modificacion;

struct info_parte
{
    int posX;
    int posY;
};

struct una_parte
{
    struct info_parte info;
    struct una_parte *sgteParte;
};

enum direcciones
{
    IZQ,
    ARR,
    ABA,
    DER
};

struct una_snake {
    int longitud;
    enum direcciones dir;
    struct una_parte *cabeza;
    struct una_parte *cola;
};

struct una_parte* snakeCrecer(struct una_snake *, struct info_parte info);
void snakeInicializar(struct una_snake*);
void snakeModificarDir(struct una_snake *, enum direcciones);
void snakeMoverse(struct una_snake *, char ***, struct una_modificacion **, bool*, bool*);

#endif // JUGADOR_H_INCLUDED