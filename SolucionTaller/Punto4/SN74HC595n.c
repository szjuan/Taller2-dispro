#include <stdio.h>
#include "Run_Punto3.h"


int SN74HC595(void) {
    const char *figura[] = {
        "  SN74HC595 - Registro de desplazamiento 8 bits (DIP-16)",
        "",
        "               +----( )----+",
        "    QB  [ 1] --|           |-- [16]  VCC",
        "    QC  [ 2] --|           |-- [15]  QA",
        "    QD  [ 3] --|           |-- [14]  ~SER",
        "    QE  [ 4] --|           |-- [13]  ~OE",
        "    QF  [ 5] --|           |-- [12]  RCLK",
        "    QG  [ 6] --|           |-- [11]  ~SRCLK",
        "    QH  [ 7] --|           |-- [10]  ~SRCLR",
        "   GND  [ 8] --|           |-- [ 9]  QH'",
        "               +-----------+",
        "",
        NULL
    };

    for (const char **linea = figura; *linea != NULL; linea++) {
        puts(*linea);
    }

    return 0;
}
