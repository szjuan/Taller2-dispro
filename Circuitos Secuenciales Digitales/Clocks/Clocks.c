

int rising_edge_clock(int prev_clck,int clk) {
    return (prev_clck == 0 && clk == 1);
}

