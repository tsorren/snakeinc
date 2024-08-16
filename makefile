CC = gcc
DEBUG_CFLAGS = -g
RELEASE_CFLAGS = -O2 -DNDEBUG
CFLAGS = -c -std=c23# -Wall -pedantic-errors

# por defecto uso 
ifndef BUILD_TYPE
    BUILD_TYPE = release
endif

# modifico CFLAGS en base a BUILD_TYPE
ifeq ($(BUILD_TYPE),debug)
    CFLAGS += $(DEBUG_CFLAGS)
else ifeq ($(BUILD_TYPE),release)
    CFLAGS += $(RELEASE_CFLAGS)
endif

#indica qué objetivos deben realizarse sí o sí, sin importar las dependencias
.PHONY: clean run

exec: main.o input.o jugador.o mapa.o render.o
	$(CC) main.o input.o jugador.o mapa.o render.o -o exec

main.o: main.c input.h jugador.h mapa.h render.h
	$(CC) $(CFLAGS) -o main.o main.c

input.o: input.c input.h
	$(CC) $(CFLAGS) -o input.o input.c

mapa.o: mapa.c mapa.h jugador.h render.h
	$(CC) $(CFLAGS) -o mapa.o mapa.c

jugador.o: jugador.c jugador.h mapa.h
	$(CC) $(CFLAGS) -o jugador.o jugador.c

render.o: render.c render.h
	$(CC) $(CFLAGS) -o render.o render.c


clean:
	rm -f main.o input.o jugador.o mapa.o render.o exec

run: exec
	./exec