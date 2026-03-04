#include <stdio.h>
#include "LogicGates.h"
#include "FormatoWaveDrom.h"
#include "CambioDeBases.h"
#include "Contadores_Bits.h"

#include "Run_Punto1.h"

#define MAX_TIEMPO 140

//PARCIAL 1
int main3(void) {

    /* ================== SEÑALES ================== */
    int clk[MAX_TIEMPO] = {1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,
                     1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,
                     1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,
                     1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,
                     1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,
                     1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,
                     1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0};

    int clr[MAX_TIEMPO] = {0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
                     1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
                     1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
                     1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
                     1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
                     1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
                     1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};

    int Input[MAX_TIEMPO] = {0,1,1,1,1,1,1,0,0,1,1,1,1,1,1,0,0,1,1,
                     1,1,1,1,0,0,1,1,1,1,1,1,0,0,1,1,1,1,1,1,
                     0,0,1,1,1,1,1,1,0,0,1,1,1,1,1,1,0,0,1,1,
                     1,1,1,1,0,0,1,1,1,1,1,1,0,0,1,1,1,1,1,1,
                     0,0,1,1,1,1,1,1,0,0,1,1,1,1,1,1,0,0,1,1,
                     1,1,1,1,0,0,1,1,1,1,1,1,0,0,1,1,1,1,1,1,
                     0,0,1,1,1,1,1,1,0,0,1,1,1,1,1,1,0,0,1,1,1};


    int q1[MAX_TIEMPO], q2[MAX_TIEMPO], q3[MAX_TIEMPO], q3_not[MAX_TIEMPO];
    int ena[MAX_TIEMPO], cnt[MAX_TIEMPO];

    for (int i = 0; i < MAX_TIEMPO; i++) {
        q1[i] = q2[i] = q3[i] = q3_not[i] = 0;
        ena[i] = 0;
        cnt[i] = 0;
    }

    int Q1 = 0, Q2 = 1, Q3 = 0;
    int CNT = 0;

    q1[0] = Q1;
    q2[0] = Q2;
    q3[0] = Q3;
    q3_not[0] = NOT_Gate(Q3);
    ena[0] = AND_Gate(q3[0], q3_not[0]);
    cnt[0] = CNT;

    q1[1] = Q1;
    q2[1] = Q2;
    q3[1] = Q3;
    q3_not[1] = NOT_Gate(Q3);
    ena[1] = AND_Gate(q3[1], q3_not[1]);
    cnt[1] = CNT;

    for (int i = 2; i < MAX_TIEMPO; i++)
    {
        // Cadena de FFs (D1=INPUT, D2=Q1, D3=Q2)
        def_flip_flop(&Q1, clk[i-1], clk[i], 1, clr[i], 1, Input[i],  &q1[i]);
        def_flip_flop(&Q2, clk[i-1], clk[i], 1, clr[i], 1, q1[i-1],   &q2[i]);
        def_flip_flop(&Q3, clk[i-1], clk[i], clr[i], 1, 1, q2[i-1],   &q3[i]);

        q3_not[i] = NOT_Gate(q3[i]);

        ena[i] = AND_Gate(q3[i], q3_not[i]);

        counter_4Bits(&CNT, clk[i-1], clk[i], clr[i], ena[i]);
        cnt[i] = CNT;
    }

    //* ================== FIND & REPLACE ================== */

    const int REDUCED_SIZE = MAX_TIEMPO / 2;

    // Señales existentes (clk, clr, Input)
    int clk_red[REDUCED_SIZE];
    int clr_red[REDUCED_SIZE];
    int in_red[REDUCED_SIZE];

    // Señales nuevas del circuito (Q1, Q2, Q3, Q3_NOT, ENA)
    int Q1_red[REDUCED_SIZE];
    int Q2_red[REDUCED_SIZE];
    int Q3_red[REDUCED_SIZE];
    int Q3N_red[REDUCED_SIZE];
    int ena_red[REDUCED_SIZE];

    // CNT como entero por tiempo (0..15) y su hex
    int cnt_red[REDUCED_SIZE];
    char HexCNT[REDUCED_SIZE][3];

    // Convertir Counter a HEX
    for (int t = 0; t < REDUCED_SIZE; t++){
        counter_to_hex2(cnt_red, t, HexCNT[t]);
    }

    // Reduce
    find_replace(clk,   MAX_TIEMPO, clk_red);
    find_replace(clr,   MAX_TIEMPO, clr_red);
    find_replace(Input, MAX_TIEMPO, in_red);

    find_replace(q1,     MAX_TIEMPO, Q1_red);
    find_replace(q2,     MAX_TIEMPO, Q2_red);
    find_replace(q3,     MAX_TIEMPO, Q3_red);
    find_replace(q3_not, MAX_TIEMPO, Q3N_red);
    find_replace(ena,    MAX_TIEMPO, ena_red);

    find_replace(cnt,    MAX_TIEMPO, cnt_red);

    /* ================== WaveDrom JSON ================== */

    printf("{ \"signal\": [\n");

    print_clock("clk", REDUCED_SIZE, 0);

    // Entradas
    print_wave("clr",   REDUCED_SIZE, clr_red, 0);
    print_wave("Input", REDUCED_SIZE, in_red,  0);

    // Salidas FF
    print_wave("Q1",     REDUCED_SIZE, Q1_red,  0);
    print_wave("Q2",     REDUCED_SIZE, Q2_red,  0);
    print_wave("Q3",     REDUCED_SIZE, Q3_red,  0);
    print_wave("Q3_NOT", REDUCED_SIZE, Q3N_red, 0);

    // Enable
    print_wave("ENA", REDUCED_SIZE, ena_red, 0);

    // Bus CNT en hexadecimal (WaveDrom bus con data)
    print_bus_hex("CNT", REDUCED_SIZE, HexCNT, 1);

    printf("] }\n");

    return 0;
}

