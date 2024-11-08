// add_fn.s

.global calculate_numbers  // Make the function accessible from the C file
.align 4                   // Ensure proper alignment

// Function: calculate_numbers
// Parameters: 
// - X0: pointer to store high part
// - X1: pointer to store low part
calculate_numbers:
    // First 64-bit number is 0x0003000000000000 FFFFFFFFFFFFFFFF
    MOVZ    X2, #0x0003, LSL #48  // Load 0x0003 0000 0000 0000 into X2
    MOVN    X3, #0                // Load 0xFFFF FFFF FFFF FFFF into X3 (MOVN sets all bits to 1)

    // Second 64-bit number is 0x0005000000000000 0000000000000001
    MOVZ    X4, #0x0005, LSL #48  // Load 0x0005 0000 0000 0000 into X4
    MOVZ    X5, #1                // Load 0x0000 0000 0000 0001 into X5

    // Perform addition
    ADDS    X6, X3, X5            // Lower-order word addition with carry
    ADC     X7, X2, X4            // Higher-order word addition with carry

    // Store the result
    STR     X6, [X1]              // Store the low result at the address in X1
    STR     X7, [X0]              // Store the high result at the address in X0

    RET                            // Return to caller
