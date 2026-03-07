#include <Arduino.h>

const int pinCLK = 7;
const int pinCLR = 6;   // active LOW
const int pinPRE = 5;   // active LOW
const int pinENA = 4;
const int pinD   = 3;

const int pinQ   = 8;
const int pinQN  = 9;

uint8_t Q = 0;

const unsigned long DEBOUNCE_MS = 25;

uint8_t rawClkPrev = 1;
uint8_t stableClk  = 1;
unsigned long lastClkChangeMs = 0;

bool risingStable(uint8_t prevStable, uint8_t newStable) {
  return (prevStable == 0 && newStable == 1);
}

void setup() {
  pinMode(pinCLK, INPUT_PULLUP);
  pinMode(pinCLR, INPUT_PULLUP);
  pinMode(pinPRE, INPUT_PULLUP);
  pinMode(pinENA, INPUT_PULLUP);
  pinMode(pinD,   INPUT_PULLUP);

  pinMode(pinQ, OUTPUT);
  pinMode(pinQN, OUTPUT);

  rawClkPrev = digitalRead(pinCLK);
  stableClk  = rawClkPrev;

  digitalWrite(pinQ, Q);
  digitalWrite(pinQN, !Q);

  Serial.begin(115200);
  Serial.println("---- D Flip Flop Debug ----");
}

void loop() {

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

  uint8_t clr = digitalRead(pinCLR);
  uint8_t pre = digitalRead(pinPRE);
  uint8_t ena = digitalRead(pinENA);
  uint8_t d   = digitalRead(pinD);

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

  if (Q != oldQ) {
    Serial.print("Q changed from ");
    Serial.print(oldQ);
    Serial.print(" to ");
    Serial.println(Q);
  }

  digitalWrite(pinQ, Q);
  digitalWrite(pinQN, !Q);

  Serial.print("CLK(raw)="); Serial.print(rawClk);
  Serial.print(" CLK(stable)="); Serial.print(stableClk);
  Serial.print(" prevStable="); Serial.print(prevStableClk);
  Serial.print(" CLR="); Serial.print(clr);
  Serial.print(" PRE="); Serial.print(pre);
  Serial.print(" ENA="); Serial.print(ena);
  Serial.print(" D="); Serial.print(d);
  Serial.print(" Q="); Serial.print(Q);
  Serial.print(" Qn="); Serial.println(!Q);

  delay(1000);
}