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

.global reductionModuloP1
reductionModuloP1:
    // Load PRIME (0xFFFFFFFB) into x4
    mov x4, #0xFFFB            // Load lower 16 bits of PRIME
    movk x4, #0xFFFF, lsl #16  // Load upper 16 bits of PRIME

    // Compare input value (x0) with PRIME
    cmp x0, x4                 // Compare x0 with PRIME
    blt return_original        // If x0 < PRIME, branch to return_original

    // First reduction
    lsr x3, x0, #32            // x3 = r >> LOG_Q (logical shift right by 32 bits)
    mul x3, x3, x4             // x3 = PRIME * (r >> LOG_Q)
    sub x0, x0, x3             // x0 = r - PRIME * (r >> LOG_Q)

    // Second reduction
    // Uncomment if further reduction is needed:
    // lsr x2, x0, #32          // x2 = r >> LOG_Q (logical shift right by 32 bits)
    // mul x2, x2, x1           // x2 = PRIME * (r >> LOG_Q)
    // sub x0, x0, x2           // x0 = r - PRIME * (r >> LOG_Q)
return_original:
    // Return the lower 32 bits of r
    uxtw w0, w0                // w0 = (uint32_t)x0

    // Return
    ret

/*
reductionModuloP1:
    // Load PRIME (0xFFFFFFFB) into x1
    mov x1, #0xFFFB          // Load lower 16 bits of PRIME
    movk x1, #0xFFFF, lsl #16 // Load upper 16 bits of PRIME

    // First reduction
    lsr x2, x0, #32          // x2 = r >> LOG_Q (logical shift right by 32 bits)
    mul x2, x2, x1           // x2 = PRIME * (r >> LOG_Q)
    sub x0, x0, x2           // x0 = r - PRIME * (r >> LOG_Q)

    // Second reduction
    // lsr x2, x0, #32          // x2 = r >> LOG_Q (logical shift right by 32 bits)
    // mul x2, x2, x1           // x2 = PRIME * (r >> LOG_Q)
    // sub x0, x0, x2           // x0 = r - PRIME * (r >> LOG_Q)

    // Return the lower 32 bits of r
    uxtw w0, w0              // w0 = (uint32_t)r

    // Return
    ret
 */
.global inversionModuloP1

// Compute modular inverse of a modulo p using Takagi's algorithm
inversionModuloP1:
    // Save callee-saved registers (x19-x28) and align stack
    stp x29, x30, [sp, #-16]!      // Save frame pointer and link register
    // mov x29, sp                    // Set up frame pointer
    stp x19, x20, [sp, #-16]!      // Save x19 and x20
    stp x21, x22, [sp, #-16]!      // Save x21 and x22
    stp x23, x24, [sp, #-16]!      // Save x23 and x24
    stp x25, x26, [sp, #-16]!      // Save x25 and x26
    stp x27, x28, [sp, #-16]!      // Save x27 and x28

    // x19 = a (input)
    mov x19, x0

    // Compute b0 = a^3 mod p
    mov x1, x19              // x1 = a
    bl multiplicationModuloP // b0 = a^2 mod p
    bl reductionModuloP1
    mov x21, x0              // x21 = a^2 mod p
    mov x1, x19              // x1 = a
    bl multiplicationModuloP // b0 = a^3 mod p
    bl reductionModuloP1
    mov x22, x0              // x22 = b0 = a^3 mod p

    // Compute b1 = a^15 mod p
    mov x1, x22              // x1 = b0
    bl multiplicationModuloP // b1 = (a^3)^2 mod p (a^6 mod p)
    bl reductionModuloP1
    mov x23, x0              // x23 = a^6 mod p
    mov x1, x0              // x23 = a^6 mod p
    bl multiplicationModuloP // b1 = (a^6)^2 mod p (a^12 mod p)
    bl reductionModuloP1
    mov x1, x22              // x1 = a^3
    bl multiplicationModuloP // b1 = a^12 * a^3 mod p (a^15 mod p)
    bl reductionModuloP1
    mov x24, x0              // x24 = b1 = a^15 mod p

    // Compute b2 = a^255 mod p
    mov x0, x24              // x0 = b1
    mov x25, #4              // Loop counter for 2^4 squaring
1:
    mov x1, x0               // x1 = b2
    bl multiplicationModuloP // b2 = b2^2 mod p
    bl reductionModuloP1
    sub x25, x25, #1         // Decrement counter
    cbnz x25, 1b             // Repeat if counter != 0

    mov x1, x24              // x1 = b1
    bl multiplicationModuloP // b2 = b2 * b1 mod p
    bl reductionModuloP1
    mov x26, x0              // x26 = b2 = a^255 mod p

    // Compute b3 = a^(2^32 - 7) mod p
    mov x0, x26              // x0 = b2
    mov x27, #8              // Loop counter for 2^8 squaring
2:
    mov x1, x0               // x1 = b3
    bl multiplicationModuloP // b3 = b3^2 mod p
    bl reductionModuloP1
    sub x27, x27, #1         // Decrement counter
    cbnz x27, 2b             // Repeat if counter != 0

    mov x1, x26              // x1 = b2
    bl multiplicationModuloP // b3 = b3 * b2 mod p
    bl reductionModuloP1
    
    // Further squaring and multiplication steps for b3
    mov x27, #8              // Loop counter for 2^8 squaring
3:
    mov x1, x0               // x1 = b3
    bl multiplicationModuloP // b3 = b3^2 mod p
    bl reductionModuloP1
    sub x27, x27, #1         // Decrement counter
    cbnz x27, 3b             // Repeat if counter != 0

    mov x1, x26              // x1 = b2
    bl multiplicationModuloP // b3 = b3 * b2 mod p
    bl reductionModuloP1

    mov x27, #4              // Loop counter for 2^4 squaring
4:
    mov x1, x0               // x1 = b3
    bl multiplicationModuloP // b3 = b3^2 mod p
    bl reductionModuloP1
    sub x27, x27, #1         // Decrement counter
    cbnz x27, 4b             // Repeat if counter != 0

    mov x1, x24              // x1 = b1
    bl multiplicationModuloP // b3 = b3 * b1 mod p
    bl reductionModuloP1

    // Final squaring and multiplication steps
    mov x1, x0               // x1 = b3
    bl multiplicationModuloP // b3 = b3^2 mod p
    bl reductionModuloP1
    mov x1, x19              // x1 = a
    bl multiplicationModuloP // b3 = b3 * a mod p
    bl reductionModuloP1

    mov x1, x0               // x1 = b3
    bl multiplicationModuloP // b3 = b3^2 mod p
    bl reductionModuloP1

    mov x1, x0
    bl multiplicationModuloP
    bl reductionModuloP1

    mov x1, x0
    bl multiplicationModuloP
    bl reductionModuloP1

    mov x1, x19
    bl multiplicationModuloP
    bl reductionModuloP1
    // mov x0, x1

    // Restore callee-saved registers
    ldp x27, x28, [sp], #16
    ldp x25, x26, [sp], #16
    ldp x23, x24, [sp], #16
    ldp x21, x22, [sp], #16
    ldp x19, x20, [sp], #16
    ldp x29, x30, [sp], #16   // Restore frame pointer and link register
    ret
