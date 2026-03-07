#include <stdio.h>
#include "LogicGates.h"
#include "FormatoWaveDrom.h"

#include "Run_Punto1.h"

#define MAX_TIEMPO 140


//PARCIAL 4
int Registro_de_Desplazamiento(void) {

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

    int pre[MAX_TIEMPO] = {0,0,1,1,1,1,1,1,0,0,1,1,1,1,1,1,0,0,1,1,
                     1,1,1,1,0,0,1,1,1,1,1,1,0,0,1,1,1,1,1,1,
                     0,0,1,1,1,1,1,1,0,0,1,1,1,1,1,1,0,0,1,1,
                     1,1,1,1,0,0,1,1,1,1,1,1,0,0,1,1,1,1,1,1,
                     0,0,1,1,1,1,1,1,0,0,1,1,1,1,1,1,0,0,1,1,
                     1,1,1,1,0,0,1,1,1,1,1,1,0,0,1,1,1,1,1,1,
                     0,0,1,1,1,1,1,1,0,0,1,1,1,1,1,1,0,0,1,1};


    int q0[MAX_TIEMPO], q1[MAX_TIEMPO], q2[MAX_TIEMPO], q3[MAX_TIEMPO];
    int qs[MAX_TIEMPO], G[MAX_TIEMPO], P[MAX_TIEMPO];

    for (int i = 0; i < MAX_TIEMPO; i++) {
        q0[i] = q1[i] = q2[i] = q3[i] = 0;
        qs[i] = G[i] = P[i] = 0;
    }

    int Q3 = 0, Q2 = 1, Q1 = 1, Q0 = 1;
    int QS = 1;

    q0[0] = Q0;
    q1[0] = Q1;
    q2[0] = Q2;
    q3[0] = Q3;
    qs[0] = QS;

    G[0] = XOR_Gate(Q0, QS);
    P[0] = AND_Gate(Q0, QS);

    q0[1] = Q0;
    q1[1] = Q1;
    q2[1] = Q2;
    q3[1] = Q3;
    qs[1] = QS;

    G[1] = XOR_Gate(Q0, QS);
    P[1] = AND_Gate(Q0, QS);

    for (int i = 1; i < MAX_TIEMPO; i++) {
        def_flip_flop(&Q3, clk[i-1], clk[i], clr[i], 1, 1, G[i-1], &q3[i]);
        def_flip_flop(&Q2, clk[i-1], clk[i], clr[i], 1, 1, q3[i-1], &q2[i]);
        def_flip_flop(&Q1, clk[i-1], clk[i], clr[i], 1, 1, q2[i-1], &q1[i]);
        def_flip_flop(&Q0, clk[i-1], clk[i], clr[i], 1, 1, q1[i-1], &q0[i]);
        def_flip_flop(&QS, clk[i-1], clk[i], 1, pre[i], 1, P[i-1], &qs[i]);

        G[i] = XOR_Gate(q0[i], qs[i]);
        P[i] = AND_Gate(q0[i], qs[i]);
    }

    /* ================== FIND & REPLACE ================== */

    const int REDUCED_SIZE = MAX_TIEMPO / 2;

    int clk_red[REDUCED_SIZE];
    int clr_red[REDUCED_SIZE];
    int pre_red[REDUCED_SIZE];

    int q0_red[REDUCED_SIZE];
    int q1_red[REDUCED_SIZE];
    int q2_red[REDUCED_SIZE];
    int q3_red[REDUCED_SIZE];

    int qs_red[REDUCED_SIZE];
    int g_red[REDUCED_SIZE];
    int p_red[REDUCED_SIZE];

    find_replace(clk, MAX_TIEMPO, clk_red);
    find_replace(clr, MAX_TIEMPO, clr_red);
    find_replace(pre, MAX_TIEMPO, pre_red);

    find_replace(q0, MAX_TIEMPO, q0_red);
    find_replace(q1, MAX_TIEMPO, q1_red);
    find_replace(q2, MAX_TIEMPO, q2_red);
    find_replace(q3, MAX_TIEMPO, q3_red);

    find_replace(qs, MAX_TIEMPO, qs_red);
    find_replace(G, MAX_TIEMPO, g_red);
    find_replace(P, MAX_TIEMPO, p_red);

    /* ================== WaveDrom JSON ================== */

    printf("{ \"signal\": [\n");

    print_clock("clk", REDUCED_SIZE, 0);

    print_wave("clr", REDUCED_SIZE, clr_red, 0);
    print_wave("pre", REDUCED_SIZE, pre_red, 0);

    print_wave("Q0", REDUCED_SIZE, q0_red, 0);
    print_wave("Q1", REDUCED_SIZE, q1_red, 0);
    print_wave("Q2", REDUCED_SIZE, q2_red, 0);
    print_wave("Q3", REDUCED_SIZE, q3_red, 0);

    print_wave("QS", REDUCED_SIZE, qs_red, 0);
    print_wave("G", REDUCED_SIZE, g_red, 0);
    print_wave("P", REDUCED_SIZE, p_red, 1);

    printf("] }\n");

    return 0;
}

