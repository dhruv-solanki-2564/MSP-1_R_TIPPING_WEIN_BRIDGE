# Rate-induced tipping in a Wien-bridge oscillator

Code, circuits and sample data behind the M.Sc. project report **"Rate-Induced Tipping in a Wien-Bridge
Oscillator"** (PH 595: M.Sc. Project Stage I, Department of Physics, IIT Bombay, 2026), by
Dhruv Kumar Solanki, under the guidance of Prof. P. Parmananda.

We sweep the gain of a Wien-bridge oscillator back and forth across its oscillation threshold, on the bench
and in LTspice, and ask whether the **speed** of the sweep, and not only its range, decides the final state.
The switching lag grows as the square root of the sweep rate. Along one fixed gain path, the oscillation
re-ignites every cycle below a critical rate of about 6.1 kΩ/s and falls silent for good above it.

- **Report:** [`report/MSP1_Report_Rate_Induced_Tipping.pdf`](report/MSP1_Report_Rate_Induced_Tipping.pdf); LaTeX source in [`report/overleaf/`](report/overleaf/)
- **How every result was made:** [`docs/analysis_map.pdf`](docs/analysis_map.pdf), a flowchart from raw data through each notebook to each figure and equation of the report

## The physics in brief

The oscillator's amplifier gain is $G = 1 + R_F/R_i$. Above a threshold $G_c$ (ideally 3) the oscillation
grows, below it decays, at a rate $\sigma = \tfrac{\omega_0}{2}(G - G_c)$ with $\omega_0 = 1/RC$. When a
resistor is swept through its threshold value at rate $\lambda$, the circuit switches only after the growth
or decay accumulated since the crossing reaches a fixed amount, so the switching point lags the threshold by
an amount proportional to $\sqrt{\lambda}$. When the gain is swept back and forth, each pass above threshold
allows only a limited growth, which shrinks as $1/\lambda$: above a critical rate the oscillation can no
longer climb back from the noise floor, and it stays off although the gain still crosses the threshold every cycle.

## Repository layout

```
README.md               this file
LICENSE                 MIT
requirements.txt        Python packages
notebooks/              14 self-contained Jupyter notebooks (00-13), in the order the work was done
data/                   small sample inputs and result tables (see data/README.md)
ltspice/                LTspice schematics and netlists, with drawings (see ltspice/README.md)
hardware/               Arduino sketches and the circuit (see hardware/README.md)
docs/                   analysis_map.pdf and its LaTeX source
report/                 the report (PDF) and its Overleaf source
```

## Quick start

```bash
git clone https://github.com/dhruv-solanki-2564/MSP-1_R_TIPPING_WEIN_BRIDGE.git
cd MSP-1_R_TIPPING_WEIN_BRIDGE
pip install -r requirements.txt
jupyter notebook notebooks/
```

Open any notebook and run all cells: it analyses the included sample data and ends with a **check** cell
comparing its output with the numbers printed in the report. To use your own data, edit only the **INPUTS**
cell (each input is commented with its meaning, units, expected file format and the value used in the report).
Results are written to `notebooks/outputs/`.

Each notebook is self-contained: it imports nothing from the rest of the repository, so you can download a
single notebook, put your file path in its INPUTS cell, and run it.

## Notebooks

| # | Notebook | What it does | Report | Inputs |
|---|---|---|---|---|
| 00 | [`00_theory_numbers`](notebooks/00_theory_numbers.ipynb) | Natural frequency, square-root coefficients, growth budgets and critical rates from the component values | Ch. 2, Tables 2.2–2.3 | component values |
| 01 | [`01_stage1_ltspice_ramp_simulation`](notebooks/01_stage1_ltspice_ramp_simulation.ipynb) | Runs LTspice ramps of $R_F$ and finds each switching point | Ch. 4, Fig. 4.1 | schematic; or saved time series |
| 02 | [`02_stage1_switching_points_and_sqrt_fits`](notebooks/02_stage1_switching_points_and_sqrt_fits.ipynb) | $\sqrt{\lambda}$, fixed-delay and free-exponent fits; parameter-free $k_{\rm off}$ | Eqs. 4.1–4.3, Fig. 4.2 | summary of switching points |
| 03 | [`03_arduino_staircase_and_pot_model`](notebooks/03_arduino_staircase_and_pot_model.ipynb) | The resistance staircase of both sketches, true and nominal rates, the mid-step line | Sec. 3.2, Eq. 3.1 | step delay, circuit values |
| 04 | [`04_merge_raw_scope_channels`](notebooks/04_merge_raw_scope_channels.ipynb) | Merges two oscilloscope channel files and cuts at the trigger pulse | Sec. 3.3 (supplementary) | two Tektronix CSV files |
| 05 | [`05_stage2_switching_points_from_scope`](notebooks/05_stage2_switching_points_from_scope.ipynb) | Switch-on and switch-off resistance of every cycle of a recording; true rate; master table | Sec. 5.2, Table A.1 | three-column recording |
| 06 | [`06_stage2_sqrt_fits_and_hysteresis_loops`](notebooks/06_stage2_sqrt_fits_and_hysteresis_loops.ipynb) | Bench fits, AIC, real threshold $G_c$, first critical rate, hysteresis loops | Eqs. 5.1–5.4, Figs. 5.2–5.4 | master table; recordings |
| 07 | [`07_stage2_cycle_by_cycle_supplementary`](notebooks/07_stage2_cycle_by_cycle_supplementary.ipynb) | Output against resistance per cycle; lag drift from cycle to cycle | supplementary | master table; recordings |
| 08 | [`08_stage3_ltspice_staircase_simulation`](notebooks/08_stage3_ltspice_staircase_simulation.ipynb) | Simulates the bench staircase step for step in LTspice | Sec. 6.1 | schematic, rates |
| 09 | [`09_stage3_simulated_switching_and_min_amplitude`](notebooks/09_stage3_simulated_switching_and_min_amplitude.ipynb) | Simulated fits, bench comparison, minimum amplitude $e^{-\Gamma_-}$, second critical rate | Eqs. 6.1–6.3, Table 6.1 | simulated runs; master |
| 10 | [`10_stage4_bench_Ri_sweep_tipping`](notebooks/10_stage4_bench_Ri_sweep_tipping.ipynb) | Bench $R_i$ sweeps: cycle peaks, long-time state, cycle map, tipping diagram | Table 7.1, Figs. 7.1–7.4, Eq. 7.1 | two-column recordings |
| 11 | [`11_stage4_growth_budget_and_switchoff_law`](notebooks/11_stage4_growth_budget_and_switchoff_law.ipynb) | Switch-off law of an $R_i$ sweep, $G_c$, growth budget $\Gamma_+$, noise floor | Eqs. 7.2–7.4, Figs. 7.5–7.6 | per-run table |
| 12 | [`12_stage4_ltspice_Ri_simulation`](notebooks/12_stage4_ltspice_Ri_simulation.ipynb) | Simulates and analyses the $R_i$ protocol in LTspice | Eq. 7.5, Figs. 7.3b, 7.4 | netlist; simulated runs |
| 13 | [`13_stage4_single_sweep_control`](notebooks/13_stage4_single_sweep_control.ipynb) | A single sweep at any speed: never tips; switch-off against theory | Sec. 7.7, Fig. 7.7 | netlist; simulated sweeps |

Notebooks 01, 08, 12 and 13 can run LTspice. Their simulation cells are off by default (`RUN_SIMULATION = False`);
everything else runs without LTspice.

## Data

`data/` contains one small example input per notebook (each file under 5 MB) and the result tables from
which the report's figures are made. The full raw dataset (about 830 MB of oscilloscope records and
simulation outputs) is described in [`data/README.md`](data/README.md) and is available from the author on request.

## LTspice

The schematics and netlists are in [`ltspice/`](ltspice/README.md). They need the Texas Instruments LM741
PSpice model (`lm741.lib`, from the LM741 product page on ti.com), which is not redistributed here. Running
the simulations from Python needs LTspice 24 or later and `PyLTSpice`.

## Hardware

An LM741 Wien-bridge oscillator on a breadboard (±15 V supply, $R = 2.17$ kΩ, $C = 1$ µF), with the gain
set by an Arduino-driven digital potentiometer (32 taps over 10 kΩ, one step = 322.6 Ω) and recorded on a
Tektronix TBS2000-series oscilloscope. Configuration A sweeps $R_F$ (91–101 kΩ, $R_i$ = 47 kΩ); configuration B
sweeps $R_i$ (41–51 kΩ, $R_F$ = 90 kΩ). The sketches and wiring are in [`hardware/`](hardware/README.md).

## How to cite

> Dhruv Kumar Solanki, *Rate-Induced Tipping in a Wien-Bridge Oscillator*, M.Sc. Project Stage I report
> (PH 595), Department of Physics, Indian Institute of Technology Bombay, 2026.
> Code and data: https://github.com/dhruv-solanki-2564/MSP-1_R_TIPPING_WEIN_BRIDGE

## Licence

MIT; see [`LICENSE`](LICENSE).
