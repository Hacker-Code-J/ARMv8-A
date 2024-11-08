/* ADD 1 */
//
// Example of 128-Bit addition with the ADD/ADC instructions.
//   0x 0003 0000 0000 0000 FFFF FFFF FFFF FFFF
// + 0x 0005 0000 0000 0000 0000 0000 0000 0001
// = 0x 0008 0000 0000 000010000 0000 0000 0000
//
.global _start               // Provide program starting address to linker
.align 4                     // Ensure proper alignment

// First 64-bit number is 0x0003000000000000 FFFFFFFFFFFFFFFF
_start: 
    MOVZ    X2, #0x0003, LSL #48  // Load 0x0003 0000 0000 0000 into X2
    MOVN    X3, #0                // Load 0xFFFF FFFF FFFF FFFF into X3 (MOVN sets all bits to 1)

// Second 64-bit number is 0x0005000000000000 0000000000000001
    MOVZ    X4, #0x0005, LSL #48  // Load 0x0005 0000 0000 0000 into X4
    MOVZ    X5, #1                // Load 0x0000 0000 0000 0001 into X5

    ADDS    X1, X3, X5            // Lower-order word addition with carry
    ADC     X0, X2, X4            // Higher-order word addition with carry

// Setup the parameters to exit the program
// W0 is the return code and will be what we calculated above.
    MOV     X0, #0                // Set exit code to 0 (successful exit)
    MOV     X8, #93               // System call number for exit (93)
    SVC     #0                    // Call kernel to terminate the program


//
// This file contains the various code snippets
// from Chapter 2, corrected for AArch64.
//

/* ADD 3
.global _start
.align 4

_start: 
l1:	
    MOV     X1, #0x1           // Initialize X1 (just an example)
    ADD     X0, XZR, X1
    MOV     X0, X1
    ORR     X0, XZR, X1 

// Load X2 with 0x1234FEDC4F5D6E3A using MOV and MOVK
l2:	
    MOV     X2, #0x6E3A
    MOVK    X2, #0x4F5D, LSL #16
    MOVK    X2, #0xFEDC, LSL #32
    MOVK    X2, #0x1234, LSL #48

l3:	
    LSL     X1, X2, #1   // Logical shift left
    LSR     X1, X2, #1   // Logical shift right
    ASR     X1, X2, #1   // Arithmetic shift right
    ROR     X1, X2, #1   // Rotate right

l4:	
    LSL     X1, X2, #1   // Logical shift left
    LSR     X1, X2, #1   // Logical shift right
    ASR     X1, X2, #1   // Arithmetic shift right
    ROR     X1, X2, #1   // Rotate right

l5:	
    // Load large immediate value using MOVZ and MOVK
    MOVZ    X1, #0xAB00, LSL #16

l6:	
    // Immediate value can be 12 bits (0-4095)
    // X2 = X1 + 4000
    ADD     X2, X1, #4000
    // Immediate shift by 12 is valid
    // X2 = X1 + 0x20000
    ADD     X2, X1, #0x20, LSL #12
    // Simple addition of two registers
    // X2 = X1 + X0
    ADD     X2, X1, X0
    // Addition of a register with a shifted register
    // X2 = X1 + (X0 * 4)
    ADD     X2, X1, X0, LSL #2
    // Register extension options
    // X2 = X1 + signed extended byte(X0)
    ADD     X2, X1, W0, SXTB
    // X2 = X1 + zero extended halfword(X0) * 4
    ADD     X2, X1, W0, UXTH #2

l8:	
    ADDS    X0, X0, #1

l9:	
    ADDS    X1, X3, X5  // Lower-order 64-bits
    ADC     X0, X2, X4  // Higher-order 64-bits

// Setup the parameters to exit the program
// W0 is the return code and will be what we calculated above.
    MOV     X0, #0        // Use 0 as the return code
    MOV     X8, #93       // Correct system call number for exit (93)
    SVC     #0            // Call kernel to terminate the program

.data
helloworld:	
    .ascii "Hello World!"
*/