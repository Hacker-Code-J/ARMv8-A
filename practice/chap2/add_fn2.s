// add_fn2.s

.global calculate_numbers2      // Make the function accessible from the C file
.align 4                       // Ensure proper alignment

// Function: calculate_numbers
// Parameters: 
// - X0: high part of first number
// - X1: low part of first number
// - X2: high part of second number
// - X3: low part of second number
// - X4: pointer to store high part of result
// - X5: pointer to store low part of result

calculate_numbers2:
    // Perform 128-bit addition:
    ADDS    X6, X1, X3          // Add the low parts (X1 + X3), store result in X6, set carry
    ADC     X7, X0, X2          // Add the high parts with carry (X0 + X2 + carry), store result in X7

    // Store the result in memory:
    STR     X6, [X5]            // Store the low part of the result in the address pointed by X5
    STR     X7, [X4]            // Store the high part of the result in the address pointed by X4

    RET                         // Return to caller
