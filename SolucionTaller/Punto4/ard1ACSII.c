#include <stdio.h>
#include "Run_Punto3.h"

/*FN****************************************************************************
*
*   int Arduino1_ASCII( void )
*
*   Purpose: Print an ASCII-art representation of an Arduino UNO board
*            to standard output, line by line, using a NULL-terminated
*            array of strings.
*
*   Return:  0 - always (success)
*
*   Register of Revisions:
*
*   DATE           RESPONSIBLE
*   -----------------------------------------------------------------------
*   MAR 07/26  Andrés Felipe Trujillo
*******************************************************************************/

int Arduino1_ASCII(void) {

/* Part 1: Define the ASCII figure as a NULL-terminated array of strings */

    const char *figura[] = {
        "Arduino UNO en ASCII",
        "               _______                                   _________",
        "           +--|  12V  |---------------------------------|   USB   |---------+",
        "           |  |       |   ------          -------       |         |  -----   |",
        "           |  |       |  | VReg |        |       |      |         | | --- |  |",
        "           |   -------    ------          -------       |         | ||   ||  |",
        "           |                                             ---------  | --- |  |",
        "           |     -----                     ----                      -----   |",
        "           |    | --- |           ---     | 16 |                   -----     |",
        "           |    ||16V||          |   |    | MH |         ------   |  |  |    |",
        "           |    | --- |     --    ---     | z  |        | micr |   -----     |",
        "           |     -----     |  |            ----         | cont |  |  |  |    |",
        "           |     -----      --                           ------    -----  [ ]|",
        "           |    | --- |          ----   --  - -   -  -  ----  -   |  |  | [ ]|",
        "           |    ||16V||         |    | |  || | | | || ||    || |   -----  [ ]|",
        "           |    | --- |          ----   --  - -   -  -  ----  -        GND[ ]|",
        "           | [ ] -----                                          |       13[ ]|",
        "           | [ ] IOREF  +-------+                               |       12[ ]|",
        "           | [ ] RESET  |       |                   A   ---     |       11[ ]|",
        "           | [ ] 3.3V   |       |                   R  | | |    |       10[ ]|",
        "           | [ ] 5V     |       |                   D   \\ /     |        9[ ]|",
        "           | [ ] GND    |       |                   U   / \\     |        8[ ]|",
        "           | [ ] GND    |       |                   I  | + |    |            |",
        "           | [ ] Vin    |       |                   N   ---     |        7[ ]|",
        "           |            |       |                   O           |        6[ ]|",
        "           | [ ] A0     |       |                      |   |    |        5[ ]|",
        "           | [ ] A1     |       |                      |   |    |        4[ ]|",
        "           | [ ] A2     |       |                      +---+    |        3[ ]|",
        "           | [ ] A3     |       |                      |\\  |    |        2[ ]|",
        "           | [ ] A4     |       |                      | \\_|    |        1[ ]|",
        "           | [ ] A5     +-------+       --------       +---+    |        0[ ]|",
        "           |                           |  |  |  |      |   |    |            |",
        "           |                           |  |  |  |      +---+    |            |",
        "           |                            --------                |            |",
        "           |                                                _________________|",
        "            \\______________________________________________/",
        NULL
    };

/* Part 2: Print each line until the NULL sentinel is reached */

    for (const char **linea = figura; *linea != NULL; linea++) {
        puts(*linea);
    }

    return 0;
}
