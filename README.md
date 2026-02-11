# ECG Arrhythmia Detection Pipeline (C++)

High-performance ECG preprocessing pipeline written in **Modern C++**.  
Transforms raw ECG recordings into **clean, normalized datasets** ready for Machine Learning and Arrhythmia Classification.

---

## Table of Contents

- [Overview](#overview)
- [Pipeline Architecture](#pipeline-architecture)
- [Signal Processing Steps](#signal-processing-steps)
- [Project Structure](#project-structure)
- [Build](#build)
- [Dataset Output](#dataset-output)
- [Future Work](#future-work)

---

## Overview

Electrocardiogram recordings are noisy, heterogeneous and difficult to use directly for machine learning.  
This project focuses on building a **fast and reliable preprocessing pipeline** capable of converting raw ECG signals into ML-ready windows.

### Core Goals

- Noise reduction and baseline correction  
- Signal normalization and segmentation  
- Window extraction with labels  
- Dataset generation for deep learning models  

---

## Pipeline Architecture

### Data Extraction & Storage

Each ECG window is encapsulated in a dedicated metadata container to ensure **consistency and integrity** across the dataset.

#### ECG Window Class

```cpp
#pragma once
#include <vector>
#include <string>

class ECGmetadata {
public:
    std::vector<double> signal;  // ECG samples
    std::string label;           // Arrhythmia class label
    int fs;                      // Sampling frequency (Hz)
    int length;                  // Window size (samples)
};
```

### Why this structure?

- Separation between **signal** and **annotation**
- Easier export to ML frameworks
- Safe handling of large datasets
- Simple serialization to CSV / binary formats

---

## Signal Processing Steps

### 1. Bandpass Filtering

Removes:
- Baseline wander (low frequency)
- Powerline noise (50/60 Hz)
- High frequency artifacts

Typical ECG band:
```
0.5 Hz — 40 Hz
```

---

### 2. Normalization

Signals are normalized to remove amplitude variability between patients.

Common methods:
- Z-score normalization
- Min-max scaling
- Peak normalization

Goal: make the model focus on **morphology**, not amplitude.

---

### 3. Window Segmentation

Continuous ECG signals are split into fixed-length windows.

Example:
```
Sampling rate: 360 Hz
Window size:   5 seconds
Samples/window: 1800
```

Each window receives a label based on annotations.

---

### 4. Dataset Export

Processed windows are exported as:

- CSV datasets
- Binary datasets (faster loading)
- Ready for Python / PyTorch / TensorFlow

---

## Project Structure

```
ECGFilterCNN/
│
├── include/
│   └── ECGmetadata.hpp
│
├── src/
│   ├── filters.cpp
│   ├── normalization.cpp
│   ├── segmentation.cpp
│   └── dataset_export.cpp
│
├── data/
└── README.md
```

---

## Build

### Requirements

- C++17 or newer  
- CMake ≥ 3.15  

### Compile

```bash
mkdir build
cd build
cmake ..
make
```

---

## Dataset Output

Final dataset format:

| Field | Description |
|------|-------------|
| signal | ECG window samples |
| label | Arrhythmia class |
| fs | Sampling frequency |
| length | Number of samples |

This format is designed for seamless integration with ML pipelines.

---

## Future Work

- R-peak detection  
- Feature extraction (HRV, RR
