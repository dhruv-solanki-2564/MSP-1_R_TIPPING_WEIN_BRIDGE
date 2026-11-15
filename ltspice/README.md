# LTspice circuits

| Folder | File | Used by | Report |
|---|---|---|---|
| `stage1_ramp/` | `wien_bridge_ramp.asc` | notebook 01 | Stage 1 (Ch. 4) |
| `stage3_staircase/` | `wien_bridge_staircase.asc`, `.net` | notebook 08 | Stage 3 (Ch. 6) |
| `stage4_Ri/` | `wien_bridge_Ri_staircase.net` | notebooks 12, 13 | Stage 4 simulations (Ch. 7) |

Each folder also holds `schematic.png`, a drawing of the circuit made from the netlist (source in
`schematic_sources/`, LaTeX/circuitikz). The drawings are redrawn, not exported from LTspice.

## The op-amp model

All circuits use the Texas Instruments LM741 PSpice model, `lm741.lib`. It is not included here.
Download it from the LM741 product page on ti.com (design resources, "PSpice model"; the archive
is called `snom211b`), and place `lm741.lib` next to the schematic, or edit the `.inc` line or the
`LM741_LIB` input of the notebook.

## How the swept resistor is modelled

- **Stage 1:** a behavioural resistor `R='{R0} + ({lam} * time)'`; the notebook sets `R0`, `lam`
  and `Tstop` through `.param`.
- **Stages 3 and 4:** a behavioural resistor `R=1k*V(rctl)`. The control voltage source `Vr` is a
  piecewise-linear (PWL) source whose file the notebook writes: 1 V on `rctl` = 1 kΩ. Each potentiometer
  step is a 10 µs ramp. A pulse source `Vtrig` imitates the Arduino's 50 ms trigger.
- **Noise:** a behavioural voltage source `0.001*white(5e2*time + nseed)` in series with R_i (about
  1 mV peak to peak, changing on a 2 ms time scale). Without it the simulated oscillator would never start.

## Requirements

LTspice 24 or later (Windows or macOS) and the Python package `PyLTSpice` (which installs `spicelib`).
All analysis cells of the notebooks run without LTspice, on the included sample outputs.
