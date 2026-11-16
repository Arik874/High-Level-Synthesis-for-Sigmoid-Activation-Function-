#include "sigmoid.h"

/**
 * @brief Hardware-optimized Sigmoid activation function
 * @param x Input feature value (fixed-point)
 * @return Mapped activation value between 0.0 and 1.0 //Sigmoid fn 
 */
data_t sigmoid(data_t x) {
    // INLINE directive allows this function to be seamlessly integrated 
    // into outer loops (like convolutional or dense layer loops) without function call overhead.
    #pragma HLS INLINE
    
    data_t result;
    
    // Piecewise Linear Approximation
    if (x >= (data_t)4.0) {
        result = (data_t)1.0;
    } 
    else if (x <= (data_t)-4.0) {
        result = (data_t)0.0;
    } 
    else {
        // HLS synthesis will automatically optimize the 0.125 multiplication 
        // into a highly efficient bit-shift right by 3 (>> 3).
        result = (data_t)0.5 + (x * (data_t)0.125);
    }
    
    return result;
}
