/*
 * BMW K100 Gear Position Converter -- 7-Segment Display Test Version
 *
 * Bench testing version of the gear selector that drives a common-cathode
 * 7-segment display directly instead of the 6-wire indicator outputs.
 * Used during development to verify gear signal decoding visually.
 *
 * 7-Segment Mapping:
 *      _
 *     |_|
 *     |_| .
 *
 *   A  = top bar
 *   B  = top right
 *   C  = bottom right
 *   D  = bottom bar
 *   E  = bottom left
 *   F  = top left
 *   G  = middle bar
 *   DP = decimal point
 *
 * Creative Commons Attribution-NonCommercial 4.0 International (CC BY-NC 4.0)
 * https://creativecommons.org/licenses/by-nc/4.0/
 * Copyright (c) 2021 Paul Thillier
 */

// ── Pin Definitions -- Gear Inputs ────────────────────────────────────────────
const int PIN_GEAR_1 = 3;
const int PIN_GEAR_2 = 4;
const int PIN_GEAR_N = 5;

// ── Pin Definitions -- 7-Segment Outputs ─────────────────────────────────────
const int PIN_SEG_DP = 6;
const int PIN_SEG_A  = 11;
const int PIN_SEG_B  = 10;
const int PIN_SEG_C  = 7;
const int PIN_SEG_D  = 8;
const int PIN_SEG_E  = 9;
const int PIN_SEG_F  = 12;
const int PIN_SEG_G  = 13;

const int THRESHOLD  = 500;

// ── State Variables ───────────────────────────────────────────────────────────
int pin1Val = 0;
int pin2Val = 0;
int pinNVal = 0;

// ── Setup ─────────────────────────────────────────────────────────────────────
void setup() {
  Serial.begin(115200);

  pinMode(PIN_GEAR_1, INPUT);
  pinMode(PIN_GEAR_2, INPUT);
  pinMode(PIN_GEAR_N, INPUT);

  pinMode(PIN_SEG_DP, OUTPUT);
  pinMode(PIN_SEG_A,  OUTPUT);
  pinMode(PIN_SEG_B,  OUTPUT);
  pinMode(PIN_SEG_C,  OUTPUT);
  pinMode(PIN_SEG_D,  OUTPUT);
  pinMode(PIN_SEG_E,  OUTPUT);
  pinMode(PIN_SEG_F,  OUTPUT);
  pinMode(PIN_SEG_G,  OUTPUT);

  // DP always on as power indicator
  digitalWrite(PIN_SEG_DP, HIGH);
  allSegmentsOff();
}

// ── Main Loop ─────────────────────────────────────────────────────────────────
void loop() {
  pin1Val = analogRead(PIN_GEAR_1);
  pin2Val = analogRead(PIN_GEAR_2);
  pinNVal = analogRead(PIN_GEAR_N);

  allSegmentsOff();

  if      (pin1Val < THRESHOLD && pin2Val < THRESHOLD && pinNVal < THRESHOLD)   { displayN(); Serial.println("Neutral"); }
  else if (pin1Val < THRESHOLD && pin2Val < THRESHOLD && pinNVal >= THRESHOLD)   { display1(); Serial.println("1st Gear"); }
  else if (pin1Val >= THRESHOLD && pin2Val < THRESHOLD && pinNVal < THRESHOLD)   { display2(); Serial.println("2nd Gear"); }
  else if (pin1Val >= THRESHOLD && pin2Val < THRESHOLD && pinNVal >= THRESHOLD)  { display3(); Serial.println("3rd Gear"); }
  else if (pin1Val < THRESHOLD && pin2Val >= THRESHOLD && pinNVal < THRESHOLD)   { display4(); Serial.println("4th Gear"); }
  else if (pin1Val < THRESHOLD && pin2Val >= THRESHOLD && pinNVal >= THRESHOLD)  { display5(); Serial.println("5th Gear"); }
}

// ── Segment Control ───────────────────────────────────────────────────────────
void allSegmentsOff() {
  digitalWrite(PIN_SEG_A, LOW); digitalWrite(PIN_SEG_B, LOW);
  digitalWrite(PIN_SEG_C, LOW); digitalWrite(PIN_SEG_D, LOW);
  digitalWrite(PIN_SEG_E, LOW); digitalWrite(PIN_SEG_F, LOW);
  digitalWrite(PIN_SEG_G, LOW);
}

// Neutral -- displays "n" shape
void displayN() {
  digitalWrite(PIN_SEG_A, HIGH); digitalWrite(PIN_SEG_B, HIGH);
  digitalWrite(PIN_SEG_C, HIGH); digitalWrite(PIN_SEG_E, HIGH);
  digitalWrite(PIN_SEG_F, HIGH);
}

void display1() {
  digitalWrite(PIN_SEG_E, HIGH);
  digitalWrite(PIN_SEG_F, HIGH);
}

void display2() {
  digitalWrite(PIN_SEG_A, HIGH); digitalWrite(PIN_SEG_B, HIGH);
  digitalWrite(PIN_SEG_D, HIGH); digitalWrite(PIN_SEG_E, HIGH);
  digitalWrite(PIN_SEG_G, HIGH);
}

void display3() {
  digitalWrite(PIN_SEG_A, HIGH); digitalWrite(PIN_SEG_B, HIGH);
  digitalWrite(PIN_SEG_C, HIGH); digitalWrite(PIN_SEG_D, HIGH);
  digitalWrite(PIN_SEG_G, HIGH);
}

void display4() {
  digitalWrite(PIN_SEG_B, HIGH); digitalWrite(PIN_SEG_C, HIGH);
  digitalWrite(PIN_SEG_F, HIGH); digitalWrite(PIN_SEG_G, HIGH);
}

void display5() {
  digitalWrite(PIN_SEG_A, HIGH); digitalWrite(PIN_SEG_C, HIGH);
  digitalWrite(PIN_SEG_D, HIGH); digitalWrite(PIN_SEG_F, HIGH);
  digitalWrite(PIN_SEG_G, HIGH);
}