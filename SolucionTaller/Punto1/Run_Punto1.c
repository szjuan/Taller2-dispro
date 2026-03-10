#include "Run_Punto1.h"
#include <stdio.h>
#include "Dibujar_ASCII.h"
#include "CircuitosASCII.h"


int main(void){

    printf("--------------------------------------------\n");
    printf("Simulacion de los Circuitos Digitales:\n");
    printf("--------------------------------------------\n\n");

    printf("Registro de Desplazamiento\n");
    Registro_de_Desplazamiento();

    printf("\nIncrementador Serial\n");
    Incrementador_Serial_4Bits();


    printf("\nSumador Completo\n");
    Sumador_Completo_8Bits();

    /* Pausa opcional */
    printf("\nPresiona Enter para ver los dibujos...");
    getchar();

    /* Limpiar pantalla */
    printf("\033[2J");
    printf("\033[H");

    printf("--------------------------------------------\n");
    printf("Dibujos de los Circuitos Digitales:\n");
    printf("--------------------------------------------\n\n");

    draw_block(10,5,  "Registro de Desplazamiento", DESPLAZAMIENTO);
    draw_block(20,25, "Incrementador Serial", INCREMENTADOR);
    draw_block(30,45, "Sumador Completo", SUMADOR);

}
