#include "../../Funciones Principales/Compuertas Logicas/LogicGates.h"
#include "../Clocks/Clocks.h"

int def_flip_flop(int *state, int prev_clk, int clk,int clear, int pre, int ena, int d, int *q ) {

    if (clear == 0)
        *state = 0;

    else if (pre == 0)
        *state = 1;

    else if (rising_edge_clock(prev_clk, clk) && ena == 1)
        *state = d;

    *q = *state;
    return 1;

}