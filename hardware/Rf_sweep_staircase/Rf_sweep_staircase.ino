// =============================================================================
//  Configuration A (report Stage 2): staircase sweep of the FEEDBACK resistance R_F
//  R_F = 91 kOhm (fixed) + digital potentiometer (10 kOhm span), R_i = 47 kOhm.
//
//  One sweep cycle = 32 increments followed by 32 decrements, each held for
//  STEP_DELAY_MS. The X9C-type pot used here behaves as a 32-tap device
//  (31 resistance steps), so the last increment of each half hits the end stop:
//  the top and bottom taps are each held for two step times. Cycle period = 64 * STEP_DELAY_MS.
//
//  A 50 ms, 5 V pulse on TRIG_PIN (recorded on oscilloscope channel 2) marks t0:
//  the sweep starts at the falling edge of this pulse.
//
//  Nominal sweep rate convention used for the run labels:
//      lambda_nominal = 312.5 Ohm / (STEP_DELAY_MS / 1000 s)
//  (312.5 Ohm = 10 kOhm / 32). The true step is 10 kOhm / 31 = 322.6 Ohm, so the
//  true rate is about 3.2 % higher; the analysis notebooks always use the true rate.
//
//  Step delays used in the report (nominal rate in Ohm/s -> STEP_DELAY_MS):
//    100 -> 3125   150 -> 2083   200 -> 1562   250 -> 1250   300 -> 1041
//    350 -> 892    400 -> 781    450 -> 695    500 -> 625    750 -> 417
//    1000 -> 313   2000 -> 156   3000 -> 104   4000 -> 78    5000 -> 63
//    7500 -> 42    9000 -> 35
//
//  Library: DigiPotX9Cxxx (Arduino Library Manager).
// =============================================================================
#include <DigiPotX9Cxxx.h>

const int CS_PIN   = 8;    // Chip Select (active LOW)
const int INC_PIN  = 10;   // Increment pulse (falling edge)
const int UD_PIN   = 9;    // Up/Down direction
const int TRIG_PIN = 7;    // Trigger output for oscilloscope channel 2

const unsigned long STEP_DELAY_MS = 313;   // <-- INPUT: hold time per step in ms (see table above)

DigiPot pot(INC_PIN, UD_PIN, CS_PIN);

void setup() {
  Serial.begin(9600);
  pinMode(TRIG_PIN, OUTPUT);
  digitalWrite(TRIG_PIN, LOW);

  pot.decrease(1000);            // force the wiper to tap 0 (R_F = 91 kOhm)
  delay(2000);                   // let the circuit settle

  digitalWrite(TRIG_PIN, HIGH);  // 50 ms trigger pulse
  delay(50);
  digitalWrite(TRIG_PIN, LOW);   // t0 = this falling edge; the sweep starts immediately
}

void loop() {
  // Serial printing inside the loop is left out on purpose: it adds a delay to every step.
  for (int i = 0; i < 32; i++) { pot.increase(1); delay(STEP_DELAY_MS); }   // R_F rising
  for (int i = 0; i < 32; i++) { pot.decrease(1); delay(STEP_DELAY_MS); }   // R_F falling
}
