# Data

This folder holds **small samples**, enough for every notebook to run out of the box, plus the small
result tables from which the report's figures and numbers are computed. The full raw dataset is
described at the end; it is not uploaded because of its size (about 830 MB).

## What is included

| Folder | File(s) | Format | Used by |
|---|---|---|---|
| `stage1/` | `simulation_summary_master.csv` | `Lambda` (Ω/s; > 0 ramp up, < 0 ramp down), `R0`, `Schematic`, `R_threshold_reached` (Ω); all 64 Stage 1 runs | 01, 02 |
| `stage1/` | `time_series_lambda_1000.csv`, `time_series_lambda_-1000.csv` | header `time,V(vout)`; time (s), output (V) | 01 |
| `stage2/` | `newexpdata - 1kohms.csv` | three columns by position: time (s), trigger CH2 (V), output CH1 (V); one bench run, 1 kΩ/s nominal | 04, 05, 06, 07 |
| `stage2/raw_scope/` | `TEK00022.CSV` (trigger), `TEK00023.CSV` (output) | Tektronix TBS2000 export: header block, then `TIME,<channel>` rows | 04 |
| `stage2/` | `Masteranalysis2.csv` | master table of all 17 bench runs, one row per cycle (written by notebook 05) | 06, 07, 09 |
| `stage3/` | `simdata - 1000ohms.csv.gz` | `TIME, CH2 - Trigger, CH1 - Vout, Rf_kohm`; one simulated run, 0.25 ms sampling | 08, 09 |
| `stage3/` | `rctl_lam1000.pwl` | LTspice PWL file of that run's staircase (time s, V = kΩ) | 08 |
| `stage3/` | `Masteranalysis_SIM.csv`, `sim_runlog.csv` | master of all 43 simulated rates; simulation log | 09 |
| `stage4/bench/` | `time_series_cropped_55a.csv`, `..._50a.csv` | two columns, no header: time from the trigger's rising edge (s), output (V); the number before `a` is the step delay in ms | 10 |
| `stage4/simulation/` | `time_series_sim_15a.csv`, `..._10a.csv` | same format, simulated, 0.3 ms sampling | 12 |
| `stage4/single_sweep/gain_falling/`, `gain_rising/` | `time_series_single_<rate>.csv` (2000 and 20000) | same format; the number is the nominal rate in Ω/s | 13 |
| `stage4/results/` | `bench_runs.csv`, `bench_cycles.csv` | per-run and per-cycle results of all 19 bench runs (made by notebook 10) | 10, 11 |
| `stage4/results/` | `sim_runs.csv`, `sim_cycles.csv` | the same for all 31 simulated step times (made by notebook 12) | 12 |
| `stage4/results/` | `single_sweep_summary.csv` | switching points and final amplitudes of all 26 single sweeps (made by notebook 13) | 13 |

In the master tables, `R_sat_*` is the switch-on point $R_{\rm on}$ and `R_decay_*` the switch-off point
$R_{\rm off}$ (column names kept from the original analysis code).

## The full dataset (not uploaded)

| Stage | Content | Files | Size |
|---|---|---|---|
| 1 | LTspice ramp simulations, `time_series_lambda_<±rate>.csv` | 64 | 256 MB |
| 2 | Raw oscilloscope channel files, `TEK000nn.CSV` (even = trigger, odd = output) | 38 | 124 MB |
| 2 | Merged bench runs, `newexpdata - <rate>ohms.csv` | 17 | 33 MB |
| 3 | Simulated staircase runs, `simdata - <rate>ohms.csv.gz`, PWL files and run log | 43 runs | 221 MB |
| 4 | Bench $R_i$ sweeps, `time_series_cropped_<delay>a.csv` | 19 | 40 MB |
| 4 | Simulated $R_i$ staircase runs, `time_series_sim_<delay>a.csv` | 31 | 120 MB |
| 4 | Simulated single sweeps (both directions), `time_series_single_<rate>.csv` | 26 | 32 MB |

Each notebook's INPUTS cell takes a folder or file path, so pointing it at the full data reproduces
every result in the report; the shipped result tables in `stage4/results/` were produced exactly that way.
The full data are available from the author on request.
