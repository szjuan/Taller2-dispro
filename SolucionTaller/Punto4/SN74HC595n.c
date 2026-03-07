#include <stdio.h>
#include "Run_Punto3.h"

/*FN****************************************************************************
*
*   int SN74HC595( void )
*
*   Purpose: Print an ASCII-art pinout diagram of the SN74HC595 8-bit
*            shift register (DIP-16) to standard output, line by line,
*            using a NULL-terminated array of strings.
*
*   Return:  0 - always (success)
*
*   Register of Revisions:
*
*   DATE           RESPONSIBLE
*   -----------------------------------------------------------------------
*   MAR 07/26  Andrés Felipe Trujillo
*
*******************************************************************************/

int SN74HC595(void) {

/* Part 1: Define the ASCII pinout as a NULL-terminated array of strings */

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

/* Part 2: Print each line until the NULL sentinel is reached */

    for (const char **linea = figura; *linea != NULL; linea++) {
        puts(*linea);
    }

    return 0;
}
