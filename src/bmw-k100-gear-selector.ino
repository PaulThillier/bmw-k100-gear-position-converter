/*
 * BMW K100 Gear Position Converter
 *
 * Converts the BMW K100 3-wire V+ gear position signal to 6 discrete
 * GND-referenced outputs (one per gear + neutral) for use with
 * aftermarket speedometers and displays.
 *
 * Signal Logic (analog threshold 500):
 *   Pin1 LOW, Pin2 LOW, PinN LOW -- Neutral
 *   Pin1 LOW, Pin2 LOW, PinN HIGH -- 1st gear
 *   Pin1 HIGH, Pin2 LOW, PinN LOW -- 2nd gear
 *   Pin1 LOW, Pin2 HIGH, PinN LOW -- 4th gear
 *   Pin1 HIGH, Pin2 LOW, PinN HIGH -- 3rd gear
 *   Pin1 LOW, Pin2 HIGH, PinN HIGH -- 5th gear
 *
 * Creative Commons Attribution-NonCommercial 4.0 International (CC BY-NC 4.0)
 * https://creativecommons.org/licenses/by-nc/4.0/
 * Copyright (c) 2021 Paul Thillier
 */

// ── Pin Definitions ───────────────────────────────────────────────────────────
const int PIN_GEAR_1 = 3;   // K100 gear signal wire 1
const int PIN_GEAR_2 = 4;   // K100 gear signal wire 2
const int PIN_GEAR_N = 5;   // K100 neutral signal wire

const int PIN_IND_N  = 8;   // Neutral indicator output
const int PIN_IND_1  = 9;   // 1st gear indicator output
const int PIN_IND_2  = 10;  // 2nd gear indicator output
const int PIN_IND_3  = 11;  // 3rd gear indicator output
const int PIN_IND_4  = 12;  // 4th gear indicator output
const int PIN_IND_5  = 13;  // 5th gear indicator output

const int THRESHOLD  = 500; // ADC threshold -- below = LOW signal

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

  pinMode(PIN_IND_N, OUTPUT);
  pinMode(PIN_IND_1, OUTPUT);
  pinMode(PIN_IND_2, OUTPUT);
  pinMode(PIN_IND_3, OUTPUT);
  pinMode(PIN_IND_4, OUTPUT);
  pinMode(PIN_IND_5, OUTPUT);

  allIndicatorsOff();
}

// ── Main Loop ─────────────────────────────────────────────────────────────────
void loop() {
  pin1Val = analogRead(PIN_GEAR_1);
  pin2Val = analogRead(PIN_GEAR_2);
  pinNVal = analogRead(PIN_GEAR_N);

  allIndicatorsOff();

  if      (pin1Val < THRESHOLD && pin2Val < THRESHOLD && pinNVal < THRESHOLD) { setGear(PIN_IND_N, "Neutral"); }
  else if (pin1Val < THRESHOLD && pin2Val < THRESHOLD && pinNVal >= THRESHOLD) { setGear(PIN_IND_1, "1st Gear"); }
  else if (pin1Val >= THRESHOLD && pin2Val < THRESHOLD && pinNVal < THRESHOLD) { setGear(PIN_IND_2, "2nd Gear"); }
  else if (pin1Val >= THRESHOLD && pin2Val < THRESHOLD && pinNVal >= THRESHOLD) { setGear(PIN_IND_3, "3rd Gear"); }
  else if (pin1Val < THRESHOLD && pin2Val >= THRESHOLD && pinNVal < THRESHOLD) { setGear(PIN_IND_4, "4th Gear"); }
  else if (pin1Val < THRESHOLD && pin2Val >= THRESHOLD && pinNVal >= THRESHOLD) { setGear(PIN_IND_5, "5th Gear"); }
  // all HIGH -- signal not present, all outputs off
}

// ── Set Single Gear Output ────────────────────────────────────────────────────
void setGear(int pin, const char* label) {
  digitalWrite(pin, HIGH);
  Serial.println(label);
}

// ── Turn All Indicators Off ───────────────────────────────────────────────────
void allIndicatorsOff() {
  digitalWrite(PIN_IND_N, LOW);
  digitalWrite(PIN_IND_1, LOW);
  digitalWrite(PIN_IND_2, LOW);
  digitalWrite(PIN_IND_3, LOW);
  digitalWrite(PIN_IND_4, LOW);
  digitalWrite(PIN_IND_5, LOW);
}