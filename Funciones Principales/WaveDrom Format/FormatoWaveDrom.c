#include <stdio.h>
#include <string.h>

#include "FormatoWaveDrom.h"


void print_wave(const char *signal_name,const int max,const int *signal_values,int is_last_signal){
    printf("  { \"name\": \"%s\", \"wave\": \"", signal_name);

    int previous_value;
    if (signal_values[0] != 0)
        previous_value = 1;
    else
        previous_value = 0;

    printf("%d", previous_value);

    for (int time_index = 1; time_index < max; time_index++) {

        int current_value;

        if (signal_values[time_index] != 0)
            current_value = 1;
        else
            current_value = 0;


        if (current_value == previous_value) {
            printf(".");
        } else {
            printf("%d", current_value);
            previous_value = current_value;
        }
    }

    printf("\" }%s\n", is_last_signal ? "" : ",");
}

void print_clock(const char *name,const int max, int is_last) {
    printf("  { \"name\": \"%s\", \"wave\": \"P", name);
    for (int i = 1; i < max; i++) printf(".");
    printf("\" }%s\n", is_last ? "" : ",");
}

void find_replace(const int *input_values,int input_size,int *output_values)
{
    int reduced_length = input_size / 2;

    for (int pair_index = 0; pair_index < reduced_length; pair_index++) {
        // 00 -> 0
        // 11 -> 1
        // Basta tomar el primer valor del par
        output_values[pair_index] = input_values[2 * pair_index];
    }
}

void print_bus_hex(const char *name, int size, char hexData[][3], int is_last)
{
    printf("  { \"name\": \"%s\", \"wave\": \"", name);

    // Construir wave
    for (int t = 0; t < size; t++)
    {
        if (t == 0) putchar('=');
        else
        {
            if (strncmp(hexData[t], hexData[t - 1], 2) == 0) putchar('.');
            else putchar('=');
        }
    }

    printf("\", \"data\": [");

    // Imprimir data SOLO cuando la wave puso '='
    int first = 1;
    for (int t = 0; t < size; t++)
    {
        int emit = (t == 0) || (strncmp(hexData[t], hexData[t - 1], 2) != 0);
        if (emit)
        {
            if (!first) printf(", ");
            printf("\"%s\"", hexData[t]);
            first = 0;
        }
    }

    printf("] }%s\n", is_last ? "" : ",");
}

void counter_to_decimal(int *cnt_array, int size, char dec_array[][3]) {
    for (int i = 0; i < size; i++) {
        snprintf(dec_array[i], 3, "%d", cnt_array[i]);
    }
}