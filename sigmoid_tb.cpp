#include <iostream>
#include <cmath>
#include <iomanip>
#include "sigmoid.h"

int main() {
    bool pass = true;
    
    // Define an acceptable error threshold for the piecewise approximation
    // Note: The maximum absolute error of this specific PLAN approximation is ~0.06
    float epsilon = 0.07f; 

    std::cout << "=================================================" << std::endl;
    std::cout << " Starting Vitis HLS Sigmoid Test Bench" << std::endl;
    std::cout << "=================================================" << std::endl;
    std::cout << std::left << std::setw(10) << "Input" 
              << std::setw(15) << "Golden (Float)" 
              << std::setw(15) << "HW (Fixed)" 
              << std::setw(15) << "Error" 
              << "Status" << std::endl;
    std::cout << "-------------------------------------------------" << std::endl;

    // Sweep through a range of input values covering all piecewise conditions
    for (float i = -5.0f; i <= 5.0f; i += 0.25f) {
        
        // 1. Calculate Golden Model (True floating point sigmoid)
        float golden_val = 1.0f / (1.0f + std::exp(-i));
        
        // 2. Calculate Hardware Model
        data_t hw_in = (data_t)i;
        data_t hw_out = sigmoid(hw_in);
        float hw_val = (float)hw_out; // Cast back to float for comparison
        
        // 3. Calculate Error
        float error = std::abs(golden_val - hw_val);
        
        // 4. Print and Verify
        std::cout << std::left << std::setw(10) << i 
                  << std::setw(15) << golden_val 
                  << std::setw(15) << hw_val 
                  << std::setw(15) << error;

        if (error > epsilon) {
            pass = false;
            std::cout << "[FAIL]" << std::endl;
        } else {
            std::cout << "[PASS]" << std::endl;
        }
    }

    std::cout << "=================================================" << std::endl;
    
    // Vitis HLS Test Benches must return 0 on success, non-zero on failure
    if (pass) {
        std::cout << ">>> TEST BENCH PASSED <<<" << std::endl;
        return 0; 
    } else {
        std::cout << ">>> TEST BENCH FAILED <<<" << std::endl;
        return 1; 
    }
}
