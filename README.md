# 🚗 Automotive Small Demo Features

## 🎯 Overview
This repository contains modular demo implementations of **smart vehicle features**.  
Each folder represents an independent automotive subsystem or functionality prototype.  
All files are created and managed in **VS Code**, then pushed directly to GitHub — no external packages used.

---

## 📂 Folder Structure
| Folder | Description |
|---------|--------------|
| `EV_Sensor_feature` | Electric Vehicle sensor simulation demos |
| `EV_features` | Core EV control and monitoring features |
| `adaptive_features` | Adaptive driving and environment response demos |
| `advanced_features` | High‑level smart automation prototypes |
| `automatic_features` | Auto‑control and assist systems |
| `battery_features` | Battery management and power monitoring |
| `blind_spot_features` | Blind‑spot detection and alert logic |
| `driver_features` | Driver behavior and assist modules |
| `ecu_features` | ECU simulation and communication |
| `emergency_features` | Safety and emergency response demos |
| `intelligent_features` | AI‑based smart decision modules |
| `lane_features` | Lane detection and assist demos |
| `protocol_features` | Communication and protocol handling |
| `scheduler_features` | Task scheduling and timing control |

---

## 🧩 Demo File Pattern
Each folder contains **one `.cpp` file** demonstrating its feature logic.  
Example:
```cpp
#include <iostream>
using namespace std;

int main() {
    cout << "Battery Feature Demo\n";
    float voltage = 12.6, current = 1.8;
    cout << "Battery Power: " << voltage * current << " W\n";
    return 0;
}

## 🚀 How to Run
Compile and run any demo individually:
```Bash
g++ battery_features/battery_features.cpp -o battery_demo
./battery_demo

```
