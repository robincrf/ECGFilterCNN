# ECG Arrhythmia Detection Pipeline (C++)

## Overview
This project implements an end-to-end ECG signal processing pipeline in C++ to prepare cardiac signals for automatic arrhythmia detection.

The objective is to transform raw ECG recordings into clean, normalized and structured datasets ready for machine learning and classification tasks.

This project highlights:
- Signal processing fundamentals  
- Biomedical data preprocessing  
- High-performance implementation in modern C++  

---

## Objectives
The pipeline automatically:
- Reads raw ECG signals from text/CSV files  
- Extracts metadata (sampling rate, label, signal length)  
- Applies advanced signal preprocessing  
- Organizes data for downstream ML models  

Typical arrhythmia classes:
- **N** — Normal beats  
- **V** — Ventricular ectopic beats  
- **S** — Supraventricular beats  

---

## Pipeline Architecture

### 1. Data Extraction & Storage

Each ECG window is encapsulated in a dedicated class:

```cpp
class ECGmetadata {
    std::vector<double> signal;
    std::string label;
    int fs;        // sampling frequency (Hz)
    int length;    // window size (samples)
};
Example raw file format:
fs=360,centered=R,length=256,label=N
0.02,0.05,0.12,0.35,...
...
fs=360,centered=R,length=256,label=V
...
Each block is parsed and stored in:
std::vector<ECGmetadata> allECG;
Signal Preprocessing Pipeline
ECG signals are noisy and non-stationary.
A multi-step preprocessing pipeline is applied to obtain robust and comparable signals.
2. Detrending — Baseline Removal
Removes slow baseline drift caused by respiration or electrode movement.
Steps

Mean subtraction (centering)
Optional linear trend removal
Effect
Stabilizes baseline
Prevents low-frequency bias
3. Savitzky–Golay Filtering (Zero-Phase)
A Savitzky–Golay smoothing filter reduces high-frequency noise while preserving ECG morphology.
Parameters

Window size: 11 samples (~30 ms at 360 Hz)
Polynomial order: 3
Forward + backward filtering (zero-phase)
Benefits
Preserves QRS complex shape
Avoids peak distortion
Maintains R-peak alignment
4. Z-Score Normalization
Signals are standardized to ensure comparability:
z = (x − μ) / σ
Two strategies:
Per-signal normalization
Dataset-level normalization
Dataset Organization
Signals are grouped by arrhythmia class:
std::map<std::string, std::vector<std::vector<double>>> signalsByClass;
Example:
signalsByClass["N"] → normal beats
signalsByClass["V"] → ventricular beats
Ready for:
Feature extraction
Machine learning
Deep learning
Visualization
Expected signal properties after preprocessing:
X-axis → sample index (0–255)
Y-axis → normalized amplitude
R-peak remains centered after filtering
Filtering Summary
Step	Filter Type	Purpose
Detrend	High-pass (~0 Hz)	Remove baseline drift
Savitzky–Golay	Soft low-pass (~15–20 Hz)	Remove high-frequency noise
Forward-Backward	Zero-phase	Preserve R-peak timing
Z-score	Statistical normalization	Signal comparability
