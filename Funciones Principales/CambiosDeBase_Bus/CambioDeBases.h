//
// Created by Juan Andres Sanchez on 21/02/26.
//

#ifndef DISPRO_CAMBIODEBASES_H
#define DISPRO_CAMBIODEBASES_H

void bus8_to_hex(int a7[], int a6[], int a5[], int a4[],int a3[], int a2[], int a1[], int a0[],int index,char out[3]);

void bus4_to_hex(int a3[], int a2[], int a1[], int a0[],int index, char out[2]);

void counter_to_hex2(const int cnt[], int index, char out[3]);

#endif //DISPRO_CAMBIODEBASES_H