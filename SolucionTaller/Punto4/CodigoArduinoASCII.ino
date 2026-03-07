#include <EEPROM.h>

/**************************** Symbolic Constants *****************************/

static const int TAM_EEPROM = 1024; /* EEPROM emulada en flash (ESP8266, 1 KB) */
static const int DIR_MAGIC  = 0;    /* Dirección de la firma de validación (4 bytes) */
static const int DIR_DATOS  = 4;    /* Dirección donde inician los IDs de líneas     */

/**************** Definition and Initialization of Global Data ****************/

/* ASCII del Arduino UNO almacenado en Flash como arreglo de punteros.
 * En EEPROM solo se guardan los IDs: 1, 2, 3, ..., N seguidos de un 0 final. */
const char* LINEAS[] = {
  "               _______                                   _________\n",
  "           +--|  12V  |---------------------------------|   USB   |---------+\n",
  "           |  |       |   ------          -------       |         |  -----   |\n",
  "           |  |       |  | VReg |        |       |      |         | | --- |  |\n",
  "           |   -------    ------          -------       |         | ||   ||  |\n",
  "           |                                             ---------  | --- |  |\n",
  "           |     -----                     ----                      -----   |\n",
  "           |    | --- |           ---     | 16 |                   -----     |\n",
  "           |    ||16V||          |   |    | MH |         ------   |  |  |    |\n",
  "           |    | --- |     --    ---     | z  |        | micr |   -----     |\n",
  "           |     -----     |  |            ----         | cont |  |  |  |    |\n",
  "           |     -----      --                           ------    -----  [ ]|\n",
  "           |    | --- |          ----   --  - -   -  -  ----  -   |  |  | [ ]|\n",
  "           |    ||16V||         |    | |  || | | | || ||    || |   -----  [ ]|\n",
  "           |    | --- |          ----   --  - -   -  -  ----  -        GND[ ]|\n",
  "           | [ ] -----                                          |       13[ ]|\n",
  "           | [ ] IOREF  +-------+                               |       12[ ]|\n",
  "           | [ ] RESET  |       |                   A   ---     |       11[ ]|\n",
  "           | [ ] 3.3V   |       |                   R  | | |    |       10[ ]|\n",
  "           | [ ] 5V     |       |                   D   \\ /     |        9[ ]|\n",
  "           | [ ] GND    |       |                   U   / \\     |        8[ ]|\n",
  "           | [ ] GND    |       |                   I  | + |    |            |\n",
  "           | [ ] Vin    |       |                   N   ---     |        7[ ]|\n",
  "           |            |       |                   O           |        6[ ]|\n",
  "           | [ ] A0     |       |                      |   |    |        5[ ]|\n",
  "           | [ ] A1     |       |                      |   |    |        4[ ]|\n",
  "           | [ ] A2     |       |                      +---+    |        3[ ]|\n",
  "           | [ ] A3     |       |                      |\\  |    |        2[ ]|\n",
  "           | [ ] A4     |       |                      | \\_|    |        1[ ]|\n",
  "           | [ ] A5     +-------+       --------       +---+    |        0[ ]|\n",
  "           |                           |  |  |  |      |   |    |            |\n",
  "           |                           |  |  |  |      +---+    |            |\n",
  "           |                            --------                |            |\n",
  "           |                                                _________________|\n",
  "            \\______________________________________________/\n"
};

const uint8_t CANT_LINEAS = sizeof(LINEAS) / sizeof(LINEAS[0]);

/*FN****************************************************************************
*
*   bool eeprom_tiene_firma( void )
*
*   Purpose: Check whether the validation magic 'LN10' is already stored
*            at the beginning of the emulated EEPROM.
*
*   Return:  true  - magic bytes match 'L','N','1','0'
*            false - otherwise (first boot or erased flash)
*
*   Register of Revisions:
*
*   DATE           RESPONSIBLE
*   -----------------------------------------------------------------------
*   MAR 07/26  Andrés Felipe Trujillo
*
*******************************************************************************/

bool eeprom_tiene_firma() {
  return EEPROM.read(DIR_MAGIC + 0) == 'L' &&
         EEPROM.read(DIR_MAGIC + 1) == 'N' &&
         EEPROM.read(DIR_MAGIC + 2) == '1' &&
         EEPROM.read(DIR_MAGIC + 3) == '0';
}

/*FN****************************************************************************
*
*   void eeprom_escribir_firma( void )
*
*   Purpose: Write the 4-byte magic 'L','N','1','0' at DIR_MAGIC to mark
*            the EEPROM as already initialised.
*
*   Return:  Nothing
*
*   Register of Revisions:
*
*   DATE           RESPONSIBLE
*   -----------------------------------------------------------------------
*   MAR 07/26  Andrés Felipe Trujillo
*
*******************************************************************************/

void eeprom_escribir_firma() {
  EEPROM.write(DIR_MAGIC + 0, 'L');
  EEPROM.write(DIR_MAGIC + 1, 'N');
  EEPROM.write(DIR_MAGIC + 2, '1');
  EEPROM.write(DIR_MAGIC + 3, '0');
}

/*FN****************************************************************************
*
*   bool guardar_ids_lineas_en_eeprom( void )
*
*   Purpose: Write the compressed line-ID sequence 1,2,...,CANT_LINEAS,0
*            starting at DIR_DATOS. The trailing 0 acts as end-of-data
*            sentinel. Verifies that the data fits within TAM_EEPROM.
*
*   Return:  true  - IDs written successfully
*            false - not enough space (should not occur with this method)
*
*   Register of Revisions:
*
*   DATE           RESPONSIBLE
*   -----------------------------------------------------------------------
*   MAR 07/26  Andrés Felipe Trujillo
*
*******************************************************************************/

bool guardar_ids_lineas_en_eeprom() {
  int dir = DIR_DATOS;

  if (dir + CANT_LINEAS + 1 > TAM_EEPROM) return false;

  for (uint8_t i = 0; i < CANT_LINEAS; i++) {
    EEPROM.write(dir++, (uint8_t)(i + 1)); /* IDs: 1-based */
  }
  EEPROM.write(dir++, 0); /* end-of-data sentinel */
  return true;
}

/*FN****************************************************************************
*
*   void imprimir_ascii_desde_eeprom( void )
*
*   Purpose: Read line IDs sequentially from EEPROM starting at DIR_DATOS
*            and print the corresponding string from LINEAS[] to Serial
*            until the sentinel value 0 is found.
*
*   Return:  Nothing
*
*   Register of Revisions:
*
*   DATE           RESPONSIBLE
*   -----------------------------------------------------------------------
*   MAR 07/26  Andrés Felipe Trujillo
*
*******************************************************************************/

void imprimir_ascii_desde_eeprom() {
  int dir = DIR_DATOS;

  while (dir < TAM_EEPROM) {
    uint8_t id = EEPROM.read(dir++);

    if (id == 0) break; /* end-of-data sentinel */

    if (id >= 1 && id <= CANT_LINEAS) {
      Serial.print(LINEAS[id - 1]);
    }
  }
}

/* ---------------------------------------------------------------------------
 *  Initialise EEPROM, write data on first boot, print ASCII art to Serial.
 * --------------------------------------------------------------------------*/

void setup() {
  Serial.begin(115200);
  delay(1200);
  Serial.println();

/* Part 1: Initialise emulated EEPROM (ESP8266 flash) */

  EEPROM.begin(TAM_EEPROM);

/* Part 2: Write signature + line IDs only on first boot */

  if (!eeprom_tiene_firma()) {
    Serial.println("Guardando ASCII (IDs de lineas) en EEPROM emulada (ESP8266 1KB)...");
    eeprom_escribir_firma();

    bool ok = guardar_ids_lineas_en_eeprom();
    if (!ok) {
      Serial.println("ERROR: no cupo (muy raro con este metodo).");
      return;
    }

    EEPROM.commit();

/* Part 3: Report memory usage after writing */

    int usados = DIR_DATOS + CANT_LINEAS + 1;
    Serial.print("OK: guardado. Bytes usados: ");
    Serial.println(usados);
    Serial.print("Bytes libres: ");
    Serial.println(TAM_EEPROM - usados);
  }

/* Part 4: Reconstruct and print ASCII art from EEPROM */

  Serial.println("Imprimiendo desde EEPROM:");
  imprimir_ascii_desde_eeprom();
}

void loop() {

}
