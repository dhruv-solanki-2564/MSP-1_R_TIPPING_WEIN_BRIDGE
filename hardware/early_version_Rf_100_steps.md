# Early version of the R_F sweep sketch (superseded)

This is the first sketch we used to sweep R_F. It is kept here only as a record; **no data in the
report were taken with it**. Two problems led to the final sketch in `Rf_sweep_staircase/`:

1. **The potentiometer has 32 effective taps, not 100.** The loop below makes 100 increments and
   100 decrements. Testing the Arduino and potentiometer alone on a resistive divider showed that the
   wiper reaches its end stop after about 31 steps and then stays there for the remaining ~69 steps of
   each half. The sweep was therefore a clipped triangle with long flat tops and bottoms, not the
   intended ramp. The final sketch uses 32 steps per half.
2. **Serial printing on every step adds lag.** Each `Serial.print` call costs time at 9600 baud, so
   the real step time was longer than `delay()` suggests. The final sketch prints only in `setup()`.

The final sketch also adds the 50 ms trigger pulse on pin 7, which marks t = 0 on the oscilloscope.

```cpp
#include <DigiPotX9Cxxx.h>

const int CS_PIN = 8;   // Chip Select (Active LOW)
const int INC_PIN = 10;   // Increment Pulse (Triggers on falling edge)
const int UD_PIN = 9;

DigiPot pot(INC_PIN, UD_PIN, CS_PIN);

void setup() {
  Serial.begin(9600);
  Serial.println("Initializing Potentiometer...");

  Serial.println("Setting to 0 RESISTANCE...");
  pot.decrease(1000);

  delay(2000); // Wait 2 seconds at zero resistance
  Serial.println("Setup complete. Starting loop...");

  // STEP 1: Force the potentiometer to FULL resistance (100% / Step 99)
  // The X9C has 100 steps. Moving 100 times UP guarantees it hits the maximum ceiling.
  Serial.println("Setting to INITIAL FULL RESISTANCE...");
  pot.increase(100);

  delay(2000); // Wait 2 seconds at full resistance

  // STEP 2: Force the potentiometer to 0 resistance (0% / Step 0)
  // Moving 100 times DOWN guarantees it hits the absolute floor.

  Serial.println("Setting to 0 RESISTANCE...");
  pot.decrease(1000);

  delay(2000); // Wait 2 seconds at zero resistance
  Serial.println("Setup complete. Starting loop...");
}

void loop() {
  Serial.println("Starting");

  for (int i=0; i<100; i++) {
    Serial.print("Increasing, i = ");
    Serial.println(i, DEC);
    pot.increase(1);
    delay(1);
  }
  delay(0);

  for (int i=0; i<100; i++) {
    Serial.print("Decreasing, i = ");
    Serial.println(i, DEC);
    pot.decrease(1);
    delay(1);
  }
  delay(0);
}
```
