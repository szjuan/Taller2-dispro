#include <Arduino.h>

/**************************** Symbolic  Constants *****************************/

const int pinCLK = 7;
const int pinCLR = 6;   /* Asynchronous Clear  (active LOW) */
const int pinPRE = 5;   /* Asynchronous Preset (active LOW) */
const int pinENA = 4;
const int pinD   = 3;
const int pinQ   = 8;
const int pinQN  = 9;

const unsigned long DEBOUNCE_MS = 25;  /* Debounce window in milliseconds */

/**************** Definition and Initialization of Global Data ****************/

uint8_t Q              = 0;  /* Current flip-flop output state     */
uint8_t rawClkPrev     = 1;  /* Previous raw clock reading         */
uint8_t stableClk      = 1;  /* Debounced clock value              */
unsigned long lastClkChangeMs = 0;  /* Timestamp of last CLK edge  */

/*FN****************************************************************************
*
*   bool risingStable( uint8_t prevStable, uint8_t newStable )
*
*   Purpose: Detect a rising edge on the debounced clock signal.
*
*   Return:  true  - LOW-to-HIGH transition detected on stable clock
*            false - otherwise
*
*   Register of Revisions:
*
*   DATE       RESPONSIBLE  COMMENT
*   -----------------------------------------------------------------------
*   MAR 07/26  Sofia Vega   Initial implementation
*
*******************************************************************************/

bool risingStable(uint8_t prevStable, uint8_t newStable) {
  return (prevStable == 0 && newStable == 1);
}

/* ---- setup() ---------------------------------------------------------------
 *  Configure pins, sample initial clock state, drive outputs, start Serial.
 * --------------------------------------------------------------------------*/

void setup() {

/* Part 1: Configure input and output pins */

  pinMode(pinCLK, INPUT_PULLUP);
  pinMode(pinCLR, INPUT_PULLUP);
  pinMode(pinPRE, INPUT_PULLUP);
  pinMode(pinENA, INPUT_PULLUP);
  pinMode(pinD,   INPUT_PULLUP);
  pinMode(pinQ,   OUTPUT);
  pinMode(pinQN,  OUTPUT);

/* Part 2: Sample initial clock state */

  rawClkPrev = digitalRead(pinCLK);
  stableClk  = rawClkPrev;

/* Part 3: Drive initial Q and Q-bar outputs */

  digitalWrite(pinQ,  Q);
  digitalWrite(pinQN, !Q);

/* Part 4: Start serial monitor */

  Serial.begin(115200);
  Serial.println("---- D Flip Flop Debug ----");
}

/* ---- loop() ----------------------------------------------------------------
 *  Debounce clock, read inputs, evaluate DFF logic, update outputs, log state.
 * --------------------------------------------------------------------------*/

void loop() {

/* Part 1: Detect and debounce clock transitions */

  uint8_t rawClk = digitalRead(pinCLK);
  unsigned long now = millis();
  if (rawClk != rawClkPrev) {
    Serial.print("Raw CLK change detected -> ");
    Serial.println(rawClk);
    rawClkPrev = rawClk;
    lastClkChangeMs = now;
  }
  uint8_t prevStableClk = stableClk;
  if ((now - lastClkChangeMs) >= DEBOUNCE_MS) {
    stableClk = rawClkPrev;
  }

/* Part 2: Read all control inputs */

  uint8_t clr = digitalRead(pinCLR);
  uint8_t pre = digitalRead(pinPRE);
  uint8_t ena = digitalRead(pinENA);
  uint8_t d   = digitalRead(pinD);

/* Part 3: Evaluate flip-flop logic (CLR, PRE, rising edge + ENA) */

  uint8_t oldQ = Q;
  if (clr == 0) {
    Serial.println("CLR active -> Q = 0");
    Q = 0;
  }
  else if (pre == 0) {
    Serial.println("PRE active -> Q = 1");
    Q = 1;
  }
  else if (ena == 1 && risingStable(prevStableClk, stableClk)) {
    Serial.print("Rising edge detected, loading D = ");
    Serial.println(d);
    Q = d;
  }

/* Part 4: Update outputs if state changed */

  if (Q != oldQ) {
    Serial.print("Q changed from ");
    Serial.print(oldQ);
    Serial.print(" to ");
    Serial.println(Q);
  }

/* Part 5: Drive output pins and print debug state */

  digitalWrite(pinQ,  Q);
  digitalWrite(pinQN, !Q);
  Serial.print("CLK(raw)=");    Serial.print(rawClk);
  Serial.print(" CLK(stable)=");Serial.print(stableClk);
  Serial.print(" prevStable="); Serial.print(prevStableClk);
  Serial.print(" CLR=");        Serial.print(clr);
  Serial.print(" PRE=");        Serial.print(pre);
  Serial.print(" ENA=");        Serial.print(ena);
  Serial.print(" D=");          Serial.print(d);
  Serial.print(" Q=");          Serial.print(Q);
  Serial.print(" Qn=");         Serial.println(!Q);
  delay(1000);
}
