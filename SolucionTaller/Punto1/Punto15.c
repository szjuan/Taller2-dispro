#include <stdio.h>
#include "LogicGates.h"
#include "FormatoWaveDrom.h"
#include "CambioDeBases.h"

#include "Run_Punto1.h"

#define MAX_TIEMPO 60

//PARCIAL 4
int main15(void) {

    /* ================== SEÑALES ================== */
    int clk[MAX_TIEMPO] = {1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,
                     1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,
                     1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0};

    int clr[MAX_TIEMPO] = {0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,1,1,
                     1,1,1,1,1,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,
                     1,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1};

    int pre[MAX_TIEMPO] = {0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
                     1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
                     1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};


    int a0[MAX_TIEMPO], a1[MAX_TIEMPO], a2[MAX_TIEMPO], a3[MAX_TIEMPO], a4[MAX_TIEMPO], a5[MAX_TIEMPO], a6[MAX_TIEMPO], a7[MAX_TIEMPO];
    int b0[MAX_TIEMPO], b1[MAX_TIEMPO], b2[MAX_TIEMPO], b3[MAX_TIEMPO], b4[MAX_TIEMPO], b5[MAX_TIEMPO], b6[MAX_TIEMPO], b7[MAX_TIEMPO];

    int qs[MAX_TIEMPO], c[MAX_TIEMPO];

    int G0[MAX_TIEMPO], P0[MAX_TIEMPO], G1[MAX_TIEMPO], P1[MAX_TIEMPO];

    for (int i = 0; i < MAX_TIEMPO; i++) {
        a0[i] = a1[i] = a2[i] = a3[i] = a4[i] = a5[i] = a6[i] = a7[i] = 0;
        b0[i] = b1[i] = b2[i] = b3[i] = b4[i] = b5[i] = b6[i] = b7[i] = 0;

        qs[i] = c[i] = 0;
        G0[i] = P0[i] = G1[i] = P1[i] = 0;
    }

    //Grupo B
    int B0 = 0, B1 = 0, B2 = 0, B3 = 1, B4 = 0, B5 = 1, B6 = 0, B7 = 0, QS = 0;

    //Grupo A
    int A0 = 0, A1 = 1, A2 = 1, A3 = 0, A4 = 0, A5 = 1, A6 = 1, A7 = 1;

    //Inicialicacion de Variables.
    a0[0] = A0;
    a1[0] = A1;
    a2[0] = A2;
    a3[0] = A3;
    a4[0] = A4;
    a5[0] = A5;
    a6[0] = A6;
    a7[0] = A7;

    b0[0] = B0;
    b1[0] = B1;
    b2[0] = B2;
    b3[0] = B3;
    b4[0] = B4;
    b5[0] = B5;
    b6[0] = B6;
    b7[0] = B7;

    qs[0] = QS;

    G0[0] = XOR_Gate(A0, B0);
    P0[0] = AND_Gate(A0, B0);

    G1[0] = XOR_Gate(QS,G0[0]);
    P1[0] = AND_Gate(QS,G0[0]);

    c[0] = OR_Gate(P0[0],P1[0]);

    a0[1] = A0;
    a1[1] = A1;
    a2[1] = A2;
    a3[1] = A3;
    a4[1] = A4;
    a5[1] = A5;
    a6[1] = A6;
    a7[1] = A7;

    b0[1] = B0;
    b1[1] = B1;
    b2[1] = B2;
    b3[1] = B3;
    b4[1] = B4;
    b5[1] = B5;
    b6[1] = B6;
    b7[1] = B7;

    qs[1] = QS;

    G0[1] = XOR_Gate(A0, B0);
    P0[1] = AND_Gate(A0, B0);

    G1[1] = XOR_Gate(QS,G0[1]);
    P1[1] = AND_Gate(QS,G0[1]);

    c[1] = OR_Gate(P0[1],P1[1]);

    for (int i = 2; i < MAX_TIEMPO; i++) {

        //Flip Flops Lado A
        def_flip_flop(&A7, clk[i-1], clk[i], 1, pre[i], 1, G1[i-1], &a7[i]);
        def_flip_flop(&A6, clk[i-1], clk[i], 1, pre[i], 1, a7[i-1], &a6[i]);
        def_flip_flop(&A5, clk[i-1], clk[i], 1, pre[i], 1, a6[i-1], &a5[i]);
        def_flip_flop(&A4, clk[i-1], clk[i], 1, pre[i], 1, a5[i-1], &a4[i]);
        def_flip_flop(&A3, clk[i-1], clk[i], 1, pre[i], 1, a4[i-1], &a3[i]);
        def_flip_flop(&A2, clk[i-1], clk[i], 1, pre[i], 1, a3[i-1], &a2[i]);
        def_flip_flop(&A1, clk[i-1], clk[i], 1, pre[i], 1, a2[i-1], &a1[i]);
        def_flip_flop(&A0, clk[i-1], clk[i], 1, pre[i], 1, a1[i-1], &a0[i]);

        //Flip Flops Lado B
        def_flip_flop(&B7, clk[i-1], clk[i], pre[i], 1, 1, b0[i-1], &b7[i]);
        def_flip_flop(&B6, clk[i-1], clk[i], pre[i], 1, 1, b7[i-1], &b6[i]);
        def_flip_flop(&B5, clk[i-1], clk[i], pre[i], 1, 1, b6[i-1], &b5[i]);
        def_flip_flop(&B4, clk[i-1], clk[i], pre[i], 1, 1, b5[i-1], &b4[i]);
        def_flip_flop(&B3, clk[i-1], clk[i], pre[i], 1, 1, b4[i-1], &b3[i]);
        def_flip_flop(&B2, clk[i-1], clk[i], pre[i], 1, 1, b3[i-1], &b2[i]);
        def_flip_flop(&B1, clk[i-1], clk[i], pre[i], 1, 1, b2[i-1], &b1[i]);
        def_flip_flop(&B0, clk[i-1], clk[i], pre[i], 1, 1, b1[i-1], &b0[i]);

        // Flip Flop QS
        def_flip_flop(&QS, clk[i-1], clk[i], clr[i], 1, 1, c[i-1], &qs[i]);

        G0[i] = XOR_Gate(a0[i], b0[i]);
        P0[i] = AND_Gate(a0[i], b0[i]);

        G1[i] = XOR_Gate(qs[i],G0[i]);
        P1[i] = AND_Gate(qs[i],G0[i]);

        c[i] = OR_Gate(P0[i],P1[i]);
    }

    /* ================== FIND & REPLACE ================== */
    const int REDUCED_SIZE = MAX_TIEMPO / 2;

    // --- señales que sí vas a imprimir ---
    int clk_red[REDUCED_SIZE];
    int clr_red[REDUCED_SIZE];
    int pre_red[REDUCED_SIZE];

    int qs_red[REDUCED_SIZE];
    int c_red[REDUCED_SIZE];

    int G0_red[REDUCED_SIZE];
    int P0_red[REDUCED_SIZE];
    int G1_red[REDUCED_SIZE];
    int P1_red[REDUCED_SIZE];

    // --- señales A y B: SOLO find & replace ---
    int a0_red[REDUCED_SIZE], a1_red[REDUCED_SIZE], a2_red[REDUCED_SIZE], a3_red[REDUCED_SIZE];
    int a4_red[REDUCED_SIZE], a5_red[REDUCED_SIZE], a6_red[REDUCED_SIZE], a7_red[REDUCED_SIZE];

    int b0_red[REDUCED_SIZE], b1_red[REDUCED_SIZE], b2_red[REDUCED_SIZE], b3_red[REDUCED_SIZE];
    int b4_red[REDUCED_SIZE], b5_red[REDUCED_SIZE], b6_red[REDUCED_SIZE], b7_red[REDUCED_SIZE];

    //find & replace principales
    find_replace(clk, MAX_TIEMPO, clk_red);
    find_replace(clr, MAX_TIEMPO, clr_red);
    find_replace(pre, MAX_TIEMPO, pre_red);


    find_replace(qs, MAX_TIEMPO, qs_red);
    find_replace(c,  MAX_TIEMPO, c_red);


    find_replace(G0, MAX_TIEMPO, G0_red);
    find_replace(P0, MAX_TIEMPO, P0_red);
    find_replace(G1, MAX_TIEMPO, G1_red);
    find_replace(P1, MAX_TIEMPO, P1_red);


    // A0..A7
    find_replace(a0, MAX_TIEMPO, a0_red);
    find_replace(a1, MAX_TIEMPO, a1_red);
    find_replace(a2, MAX_TIEMPO, a2_red);
    find_replace(a3, MAX_TIEMPO, a3_red);
    find_replace(a4, MAX_TIEMPO, a4_red);
    find_replace(a5, MAX_TIEMPO, a5_red);
    find_replace(a6, MAX_TIEMPO, a6_red);
    find_replace(a7, MAX_TIEMPO, a7_red);


    // B0..B7
    find_replace(b0, MAX_TIEMPO, b0_red);
    find_replace(b1, MAX_TIEMPO, b1_red);
    find_replace(b2, MAX_TIEMPO, b2_red);
    find_replace(b3, MAX_TIEMPO, b3_red);
    find_replace(b4, MAX_TIEMPO, b4_red);
    find_replace(b5, MAX_TIEMPO, b5_red);
    find_replace(b6, MAX_TIEMPO, b6_red);
    find_replace(b7, MAX_TIEMPO, b7_red);

    //Pasar de 8 bits a Hexa
    char HexA[REDUCED_SIZE][3];
    char HexB[REDUCED_SIZE][3];
    for (int t = 0; t < REDUCED_SIZE; t++){
        // Convertir bus A
        bus8_to_hex(
            a7_red, a6_red, a5_red, a4_red,
            a3_red, a2_red, a1_red, a0_red,
            t,HexA[t]
        );

        // Convertir bus B
        bus8_to_hex(
            b7_red, b6_red, b5_red, b4_red,
            b3_red, b2_red, b1_red, b0_red,
            t,HexB[t]
        );
    }


    /* ================== WaveDrom JSON ================== */

    printf("{ \"signal\": [\n");

    print_clock("clk", REDUCED_SIZE, 0);


    print_wave("clr", REDUCED_SIZE, clr_red, 0);
    print_wave("pre", REDUCED_SIZE, pre_red, 0);


    print_wave("QS", REDUCED_SIZE, qs_red, 0);
    print_wave("C",  REDUCED_SIZE, c_red,  0);


    print_wave("G0", REDUCED_SIZE, G0_red, 0);
    print_wave("P0", REDUCED_SIZE, P0_red, 0);
    print_wave("G1", REDUCED_SIZE, G1_red, 0);
    print_wave("P1", REDUCED_SIZE, P1_red, 0);


    print_bus_hex("A", REDUCED_SIZE, HexA, 0);
    print_bus_hex("B", REDUCED_SIZE, HexB, 1);


    printf("] }\n");

    return 0;
}

