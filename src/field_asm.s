
.section .text
.global multiplicationModuloP2

multiplicationModuloP2:
    // Input:
    // w0 = a (32-bit unsigned)
    // w1 = b (32-bit unsigned)

    // Multiply a and b as 64-bit values
    mul x2, x0, x1            // x2 = a * b (full 64-bit result)

    // Calculate r >> LOG_Q (LOG_Q = 32)
    lsr x3, x2, #32           // x3 = r >> 32

    // Load PRIME (0xFFFFFFFB) directly into x4
    movz x4, #0xFFFB          // Load lower 16 bits
    movk x4, #0xFFFF, lsl #16 // Load middle 16 bits
    movk x4, #0xFFFF, lsl #32 // Load upper 16 bits

    // Multiply (r >> LOG_Q) by PRIME
    mul x3, x3, x4            // x3 = (r >> LOG_Q) * PRIME

    // Subtract (r >> LOG_Q) * PRIME from r
    sub x0, x2, x3            // x0 = r - (r >> LOG_Q) * PRIME

    // Return the result in x0
    ret

.type    multiplicationModuloP3, %function
.global  multiplicationModuloP3

multiplicationModuloP3:
    // Input: w0 = a, w1 = b
    // Output: x0 = result (a * b) % PRIME

    // Full 128-bit product: (a * b)
    mul x2, x0, x1            // x2 = low 64 bits of (a * b)
    umulh x3, x0, x1          // x3 = high 64 bits of (a * b)

    // Precomputed μ = floor(2^64 / PRIME)
    mov x4, #0xFFFFFFFC       // μ (precomputed constant)

    // Compute q = (r * μ) >> 64
    mul x5, x3, x4            // High 64 bits of (r * μ)
    umulh x6, x3, x4          // x6 = high 64 bits of (r * μ)

    // r = r - q * PRIME
    mul x5, x5, x4            // x5 = q * PRIME
    sub x0, x2, x5            // x0 = r - q * PRIME

    // Final reduction (if r >= PRIME)
    cmp x0, x4
    csel x0, x0, x4, lo       // If r >= PRIME, subtract PRIME

    ret
	.size multiplicationModuloP3, (. - multiplicationModuloP3)
