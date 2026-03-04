#include "LogicGates.h"

int XOR_Gate(int A, int B) {
    return (A && !B) || (!A && B);
}