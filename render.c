#include <stdio.h>
#include <windows.h>
#include "render.h"

#define PADDING_X 5
#define PADDING_Y 5

void enableANSI() {
    // Obtener el manejador de la consola
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    // Habilitar el modo de salida VT100 en cmd.exe
    DWORD dwMode = 0;
    GetConsoleMode(hOut, &dwMode);
    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(hOut, dwMode);
}

void clearScreen() {
    // ANSI code to clear the screen and move the cursor to the top-left corner
    printf("\033[2J\033[H");
}

void setColor(int textColor, int bgColor) {
    // ANSI code to set text color and background color
    // Text colors: 30: Negro - 31: Rojo - 32: Verde - 33: Amarillo - 34: Azul - 35: Magenta - 36: Cian - 37: Blanco
    // Background colors: 40: Negro - 41: Rojo - 42: Verde - 43: Amarillo - 44: Azul - 45: Magenta - 46: Cian - 47: Blanco
    printf("\033[%d;%dm", textColor, bgColor);
}

void resetColor() {
    // ANSI code to reset text and background color to default
    printf("\033[0m");
}

void moveTo(int x, int y) {
    // ANSI code to move the cursor to a specific position
    // Positions are 1-indexed (top-left corner is (1, 1))
    printf("\033[%d;%dH", y, x);
}

void hideCursor() {
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;

    GetConsoleCursorInfo(consoleHandle, &cursorInfo);  // Obtén la información actual del cursor
    cursorInfo.bVisible = FALSE;                      // Establece la visibilidad del cursor a FALSE
    SetConsoleCursorInfo(consoleHandle, &cursorInfo); // Aplica los cambios
}

void showCursor() {
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;

    GetConsoleCursorInfo(consoleHandle, &cursorInfo);  // Obtén la información actual del cursor
    cursorInfo.bVisible = TRUE;                       // Establece la visibilidad del cursor a TRUE
    SetConsoleCursorInfo(consoleHandle, &cursorInfo); // Aplica los cambios
}

void mostrarChar(char c, int x, int y, int color)
{
    setColor(color, BBLK);
    int newX = (x + PADDING_X) * 2;
    int newY = (y + PADDING_Y);
    moveTo(newX, newY);
    printf("%c", c);
}

void mostrarPuntaje(int longitud)
{
    int puntaje = (longitud - 1) * 25;
    setColor(FWHT, BBLK);
    int newX = (PADDING_X) * 2;
    int newY = (PADDING_Y - 2);
    moveTo(newX, newY);
    printf("                               ");
    moveTo(newX, newY);
    printf("Score: %d", puntaje);
}