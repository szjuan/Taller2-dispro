#include "Contadores_Bits.h"
#include "stdio.h"

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

