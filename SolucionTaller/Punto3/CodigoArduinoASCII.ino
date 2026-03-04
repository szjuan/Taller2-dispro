#include <EEPROM.h>

// =====================================================
// CONFIGURACIÓN DE EEPROM (ESP8266)
// =====================================================
// En ESP8266 la EEPROM es "emulada" en la memoria flash.
// Usamos 1024 para simular el límite de Arduino UNO (1 KB).
static const int TAM_EEPROM = 1024;
static const int DIR_MAGIC  = 0;  // donde guardamos la firma (4 bytes)
static const int DIR_DATOS  = 4;  // aquí empiezan los datos (IDs de líneas)

// =====================================================
// DICCIONARIO DE LÍNEAS (el ASCII completo está en FLASH)
// =====================================================
// Guardamos el ASCII como un arreglo de líneas.
// En EEPROM solo guardamos los IDs: 1,2,3,...,N y un 0 final.
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

// =====================================================
// FUNCIONES DE CONTROL (MAGIC / FIRMA)
// =====================================================
// Usamos 4 bytes de firma para saber si ya cargamos los datos en EEPROM.
// Si están, no volvemos a reescribir.
bool eeprom_tiene_firma() {
  return EEPROM.read(DIR_MAGIC + 0) == 'L' &&
         EEPROM.read(DIR_MAGIC + 1) == 'N' &&
         EEPROM.read(DIR_MAGIC + 2) == '1' &&
         EEPROM.read(DIR_MAGIC + 3) == '0';
}

void eeprom_escribir_firma() {
  EEPROM.write(DIR_MAGIC + 0, 'L');
  EEPROM.write(DIR_MAGIC + 1, 'N');
  EEPROM.write(DIR_MAGIC + 2, '1');
  EEPROM.write(DIR_MAGIC + 3, '0');
}

// =====================================================
// GUARDAR "CÓDIGO ASCII" EN EEPROM (COMPRIMIDO)
// =====================================================
// Clave: NO guardamos el ASCII completo.
// Guardamos una secuencia de IDs:
//   [1][2][3]...[CANT_LINEAS][0]
// El 0 marca "fin".
bool guardar_ids_lineas_en_eeprom() {
  int dir = DIR_DATOS;

  
  if (dir + CANT_LINEAS + 1 > TAM_EEPROM) return false;

  for (uint8_t i = 0; i < CANT_LINEAS; i++) {
    EEPROM.write(dir++, (uint8_t)(i + 1)); 
  }
  EEPROM.write(dir++, 0); 
  return true;
}

// =====================================================
// LEER EEPROM Y RECONSTRUIR ASCII POR SERIAL
// =====================================================
void imprimir_ascii_desde_eeprom() {
  int dir = DIR_DATOS;

  while (dir < TAM_EEPROM) {
    uint8_t id = EEPROM.read(dir++);

    if (id == 0) break; // fin

    if (id >= 1 && id <= CANT_LINEAS) {
      Serial.print(LINEAS[id - 1]);
    }
  }
}

// =====================================================
// SETUP / LOOP
// =====================================================
void setup() {
  Serial.begin(115200);
  delay(1200);
  Serial.println();

  // Inicializa EEPROM emulada en ESP8266
  EEPROM.begin(TAM_EEPROM);

  // Solo guardamos en EEPROM la primera vez
  if (!eeprom_tiene_firma()) {
    Serial.println("Guardando ASCII (IDs de lineas) en EEPROM emulada (ESP8266 1KB)...");
    eeprom_escribir_firma();

    bool ok = guardar_ids_lineas_en_eeprom();
    if (!ok) {
      Serial.println("ERROR: no cupo (muy raro con este metodo).");
      return;
    }

    EEPROM.commit();

    // Diagnóstico de memoria usada
    int usados = DIR_DATOS + CANT_LINEAS + 1;
    Serial.print("OK: guardado. Bytes usados: ");
    Serial.println(usados);
    Serial.print("Bytes libres: ");
    Serial.println(TAM_EEPROM - usados);
  }

  Serial.println("Imprimiendo desde EEPROM:");
  imprimir_ascii_desde_eeprom();
}

void loop() {
}