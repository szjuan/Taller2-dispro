#include "Contadores_Bits.h"
#include "stdio.h"

/*FN****************************************************************************
*
*   void counter_4Bits(int *Q,int clk_prev,int clk_now,int clr_n,int ena);
*
*   Return: Asigna a memoria un 0 si hay clear o suma 1 al valor de memoria de Q
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

void counter_4Bits(int *Q,int clk_prev,int clk_now,int clr_n,int ena){
    // Clear asíncrono
    if (clr_n == 0) {
        *Q = 0;
        return;
    }

    // Flanco de subida
    if (clk_prev == 0 && clk_now == 1) {
        if (ena == 1) {
            *Q = (*Q + 1) & 0x0F;
        }
    }
}

