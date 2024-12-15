.section .text
.global multiplicationModuloP1

// uint64_t multiplicationModuloP(const uint32_t a, const uint32_t b) 
// Input:
// w0 = a (32-bit unsigned)
// w1 = b (32-bit unsigned)
// Output:
// x0 (64-bit unsigned)
multiplicationModuloP1:
    // Multiply a and b as 64-bit values
    mul x2, x0, x1            // x2 = a * b (full 64-bit result)

    // Calculate r >> LOG_Q
    lsr x3, x2, #32           // x3 = r >> LOG_Q 

    // Load PRIME (0xFFFFFFFB) into x4
    mov x4, #0xFFFB          // Load lower 16 bits of PRIME
    movk x4, #0xFFFF, lsl #16 // Load upper 16 bits of PRIME (middle word)
    // movk x4, #0xFFFF, lsl #32 // Load upper 16 bits of PRIME (top word)

    // Multiply (r >> LOG_Q) by PRIME
    mul x3, x3, x4            // x3 = PRIME * (r >> LOG_Q)

    // Subtract (r >> LOG_Q) * PRIME from r
    sub x0, x2, x3            // x2 = r - PRIME * (r >> LOG_Q)

    // Return the result
    ret


.global addmul_P32_into_64_ARM

// void addmul_P32_into_64(uint64_t* a, const uint32_t b, const uint32_t c)
// Input:
// w0 = a (pointer) 
// w1 = b 
// w2 = c
addmul_P32_into_64_ARM:
    // Load *a into x3
    ldr x3, [x0]             // x3 = *a

    // Multiply b and c to produce a 64-bit result
    mul x4, x1, x2           // x4 = (uint64_t)b * c

    // Add r (x4) to *a (x3)
    add x3, x3, x4           // x3 = *a + r

    // Calculate (*a) >> LOG_Q
    lsr x5, x3, #32          // x5 = (*a) >> LOG_Q

    // Load PRIME (0xFFFFFFFB) into x6
    mov x6, #0xFFFB          // Load lower 16 bits of PRIME
    movk x6, #0xFFFF, lsl #16 // Load upper 16 bits of PRIME

    // Multiply (r >> LOG_Q) by PRIME
    mul x5, x5, x6           // x5 = PRIME * ((*a) >> LOG_Q)

    // Subtract PRIME * ((*a) >> LOG_Q) from (*a + r)
    sub x3, x3, x5           // x3 = *a + r - PRIME * ((*a) >> LOG_Q)

    // Store the result back to *a
    str x3, [x0]             // *a = x3

    // Return
    ret
