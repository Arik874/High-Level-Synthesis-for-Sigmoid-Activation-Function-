#ifndef SIGMOID_H
#define SIGMOID_H

#include "ap_fixed.h"

// Define fixed-point data types
// Total bits: 16, Integer bits: 6 (leaves 10 bits for fractional precision)
// Adjust these parameters based on your specific model quantization requirements.
typedef ap_fixed<16, 6, AP_TRN, AP_WRAP> data_t;

// Function prototype
data_t sigmoid(data_t x);

#endif // SIGMOID_H
