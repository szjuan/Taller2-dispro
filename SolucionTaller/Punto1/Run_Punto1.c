#include "Run_Punto1.h"
#include <stdio.h>
#include "Dibujar_ASCII.h"
#include "CircuitosASCII.h"


int main(void){

   printf("\"--------------------------------------------\"\n");
   printf("\"Simulacion de los Circuitos Digitales:\"\n");
   printf("\"--------------------------------------------\"\n\n");

   printf("\"Registro de Desplazamiento\" \n");
   Registro_de_Desplazamiento();
   printf("\"Incrementador Serial\" \n");
   Incrementador_Serial_4Bits();
   printf("\"Sumador Completo\"\n");
   Sumador_Completo_8Bits();

   printf("\n\"--------------------------------------------\"\n");
   printf("\"Dibujos de los Circuitos Digitales:\"\n");
   printf("\"--------------------------------------------\"\n\n");

   printf("\"Registro de Desplazamiento\" \n");
   printf("\n");
   draw_ascii(DESPLAZAMIENTO);
   printf("\n");
   printf("\"Incrementador Serial\" \n");
   printf("\n");
   draw_ascii(INCREMENTADOR);
   printf("\n");
   printf("\"Sumador Completo\"\n");
   printf("\n");
   draw_ascii(SUMADOR);
   printf("\n");




}
