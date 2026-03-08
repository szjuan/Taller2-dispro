#include <stdio.h>
#include <stddef.h>
#include "Dibujar_ASCII.h"

void gotoxy(int x, int y) {
    printf("\033[%d;%dH", y, x);
}

void draw_ascii(const char *art[]) {
    int i = 0;
    while (art[i] != NULL) {
        printf("%s\n", art[i]);
        i++;
    }
    fflush(stdout);
}