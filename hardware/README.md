# Hardware

## The circuit

A Wien-bridge oscillator built on a breadboard around an **LM741** operational amplifier with a
**±15 V** supply.

| Part | Value |
|---|---|
| Wien-network resistors (series and parallel arm) | R = 2.17 kΩ |
| Wien-network capacitors (series and parallel arm) | C = 1 µF |
| Natural frequency | ω₀ = 1/RC = 460.8 s⁻¹, f₀ = 73.3 Hz (measured on the bench: 72.4 Hz) |
| Amplifier gain | G = 1 + R_F / R_i (non-inverting) |
| Ideal threshold | G_c = 3 (measured on the bench: G_c ≈ 3.07–3.08) |

The gain is changed by a digital potentiometer (X9C family, driven with the `DigiPotX9Cxxx` library).
In our tests it behaves as a **32-tap** device, i.e. 31 resistance steps over its 10 kΩ span, so one step
is 10 kΩ / 31 = **322.6 Ω**. The run labels use the nominal step 10 kΩ / 32 = 312.5 Ω (see below).

| | Configuration A (report Stage 2) | Configuration B (report Stage 4) |
|---|---|---|
| Swept resistor | R_F = 91 kΩ + pot (91 → 101 kΩ) | R_i = 41 kΩ + pot (41 → 51 kΩ) |
| Fixed resistor | R_i = 47 kΩ | R_F = 90 kΩ |
| Gain range | 2.94 → 3.15 | 3.20 → 2.76 |
| Sketch | [`Rf_sweep_staircase/`](Rf_sweep_staircase/Rf_sweep_staircase.ino) | [`Ri_sweep_staircase/`](Ri_sweep_staircase/Ri_sweep_staircase.ino) |
| Step delays used | 3125 … 35 ms (17 rates) | 100 … 37 ms (19 runs) |

Arduino pins: CS = 8, INC = 10, U/D = 9, trigger output = 7.

## Recording

The oscillator output (channel 1) and the Arduino trigger pulse (channel 2) are recorded on a
Tektronix TBS2000-series oscilloscope and exported as CSV. The sampling interval is chosen per run so
that the whole record covers several sweep cycles. Notebook
[`04_merge_raw_scope_channels.ipynb`](../notebooks/04_merge_raw_scope_channels.ipynb) turns the two
exported channel files into the three-column file the analysis expects.

## Sweep rate

The sketch holds every step for `STEP_DELAY_MS`. The **true** sweep rate is

    lambda = 322.6 Ohm / (STEP_DELAY_MS / 1000 s)

The file names of configuration A use the **nominal** rate 312.5 Ω / step time, which is about 3 % lower.
Every fit and figure in the report uses the true rate, measured from the recording itself (notebook 05).
Notebook [`03_arduino_staircase_and_pot_model.ipynb`](../notebooks/03_arduino_staircase_and_pot_model.ipynb)
shows the exact resistance–time staircase that both sketches produce.

## Files

- `Rf_sweep_staircase/Rf_sweep_staircase.ino`: configuration A sketch (32 steps up, 32 down).
- `Ri_sweep_staircase/Ri_sweep_staircase.ino`: configuration B sketch (32-step hold, then 32 up, 32 down).
- `early_version_Rf_100_steps.md`: the first, superseded sketch, and why it was replaced.
