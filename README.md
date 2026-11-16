# Vitis HLS Sigmoid Activation Function

An optimized, hardware-friendly implementation of the Sigmoid activation function for Xilinx Vitis HLS. 

Standard floating-point exponential functions (`1 / (1 + exp(-x))`) consume excessive DSP blocks and Look-Up Tables (LUTs) on FPGAs. This repository solves that by using a **Piecewise Linear (PLAN) approximation** mapped to arbitrary precision fixed-point data types (`ap_fixed`). This reduces latency to a single clock cycle and minimizes logic footprint while maintaining sufficient accuracy for most CNN inference tasks.

## Repository Structure
* `sigmoid.h`: Type definitions and function prototypes.
* `sigmoid.cpp`: The core HLS implementation using piecewise linear approximation.
* `sigmoid_tb.cpp`: C++ test bench that verifies hardware accuracy against a standard `<cmath>` floating-point golden model.

## Approximation Math
The exact sigmoid function is approximated using the following piecewise conditions:
* `f(x) = 1.0` (for `x >= 4.0`)
* `f(x) = 0.0` (for `x <= -4.0`)
* `f(x) = 0.5 + 0.125 * x` (for `-4.0 < x < 4.0`)

*Note: The synthesizer automatically maps the `0.125` multiplication to a highly efficient 3-bit right-shift operation.*

<img width="1024" height="572" alt="image" src="https://github.com/user-attachments/assets/28bae319-4e0b-4c6a-a386-82151f7c657b" />
-> AI gen. Infographic outlining the repository and its implementation details 


## Usage
1. Create a new Vitis HLS project.
2. Add `sigmoid.cpp` to the **Source Files**.
3. Add `sigmoid_tb.cpp` to the **Test Bench Files**.
4. Set the Top Function to `sigmoid`.
5. Run C Simulation, C Synthesis, and Co-Simulation.
