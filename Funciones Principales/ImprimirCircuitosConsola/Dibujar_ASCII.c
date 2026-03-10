#include <stdio.h>
#include <stddef.h>
#include "Dibujar_ASCII.h"

/*FN****************************************************************************
*
*   void gotoxy(int x, int y);
*   void draw_ascii(const char *art[]);
*
*
*   Return:  gotoxy() mueve el cursor de la termina a la posicion determinada X y Y.
*   Return:   draw_ascii() recorre un arreglo char y imprime lo que encuentre hasta que encuentre NULL
*
*   Registro de Versiones:
*
*   DATE       RESPONSABLE           COMENTARIO
*   -----------------------------------------------------------------------
*   Marzo  8/26  Juan Andres Sanchez   Implementación Inicial
*
*   REVISADO
*   -----------------------------------------------------------------------
*   Sofia Vega, Andres Trujillo
*
*******************************************************************************/



void gotoxy(int x, int y) {
    printf("\033[%d;%dH", y, x);
}

void draw_ascii(int x, int y, const char *art[]) {
    int i = 0;
    while (art[i] != NULL) {
        gotoxy(x, y + i);
        printf("%s", art[i]);
        i++;
    }
    fflush(stdout);
}

void draw_block(int x, int y, const char *title, const char *art[]) {
    gotoxy(x, y);
    printf("%s", title);
    draw_ascii(x, y + 2, art);
}