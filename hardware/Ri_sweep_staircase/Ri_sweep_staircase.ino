// =============================================================================
//  Configuration B (report Stage 4): staircase sweep of the INPUT resistance R_i
//  R_i = 41 kOhm (fixed) + digital potentiometer (10 kOhm span), R_F = 90 kOhm.
//
//  After setup() the wiper sits at tap 0 (R_i = 41 kOhm, highest gain G = 3.20,
//  the circuit oscillates). loop() starts with 32 decrements: the wiper is already
//  at tap 0, so this first block is a hold of 32 step times. Then 32 increments raise
//  R_i to 51 kOhm (gain falls to 2.76) and the next 32 decrements bring it back.
//  The sweep therefore repeats with period 64 * STEP_DELAY_MS, and the first change of
//  R_i happens 32 * STEP_DELAY_MS after the trigger pulse.
//
//  A 50 ms, 5 V pulse on TRIG_PIN marks the start; the recorded files start at the
//  pulse's rising edge.
//
//  Step delays used in the report (ms): 37, 38, 40, 41, 42, 43, 45, 50, 52, 53, 54,
//  55, 56, 58, 66, 67, 70, 75, 100   (true rate = 322.6 Ohm / step time).
//
//  Library: DigiPotX9Cxxx (Arduino Library Manager).
// =============================================================================
#include <DigiPotX9Cxxx.h>

const int CS_PIN   = 8;     // Chip Select (Active LOW)
const int INC_PIN  = 10;    // Increment Pulse (Triggers on falling edge)
const int UD_PIN   = 9;     // Up/Down direction
const int TRIG_PIN = 7;     // Dedicated trigger pin for DSO Channel 2

const unsigned long STEP_DELAY_MS = 750;   // <-- INPUT: hold time per step in ms

DigiPot pot(INC_PIN, UD_PIN, CS_PIN);

void setup() {
  Serial.begin(115200);

  // Initialize the trigger pin and keep it LOW (0V)
  pinMode(TRIG_PIN, OUTPUT);
  digitalWrite(TRIG_PIN, LOW);

  Serial.println("Initializing Potentiometer...");
  Serial.println("Setting to 0 RESISTANCE baseline...");

  // Calibration: Force the potentiometer to absolute 0 resistance
  pot.decrease(1000);
  delay(2000); // Wait 2 seconds for the circuit to stabilize at 0 ohms

  Serial.println("Calibration complete. Firing DSO Trigger...");

  // DSO trigger: a sharp 5V pulse to mark t=0 on the oscilloscope
  digitalWrite(TRIG_PIN, HIGH);
  delay(50);                     // 50ms width is easily visible on a DSO
  digitalWrite(TRIG_PIN, LOW);

  // The main sweep loop begins immediately after this pulse drops.
  Serial.println("Starting sweep loops...");
}

void loop() {
  // Serial printing is commented out during data collection: it adds lag to every step.

  for (int i = 0; i < 32; i++) {   // decrements: R_i falls (gain rises); a hold on the first pass
    // Serial.print("Decreasing, i = ");
    // Serial.println(i, DEC);
    pot.decrease(1);
    delay(STEP_DELAY_MS);
  }

  for (int i = 0; i < 32; i++) {   // increments: R_i rises (gain falls)
    // Serial.print("Increasing, i = ");
    // Serial.println(i, DEC);
    pot.increase(1);
    delay(STEP_DELAY_MS);
  }
}
