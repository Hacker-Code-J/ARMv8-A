// src/main.s
.section .data
    num1: .word 10         // First operand (10)
    num2: .word 20         // Second operand (20)
    add_result: .word 0     // To store the result of addition
    mul_result: .word 0     // To store the result of multiplication

.section .text
    .global _start

_start:
    // Load the numbers into registers
    ldr x0, =num1         // Load address of num1 into x0 (64-bit register for address)
    ldr w1, [x0]          // Load the value at the address (num1) into w1 (32-bit value)
    ldr x0, =num2         // Load address of num2 into x0 (64-bit register for address)
    ldr w2, [x0]          // Load the value at the address (num2) into w2 (32-bit value)

    // Perform the addition
    add w3, w1, w2        // Add w1 and w2, store result in w3

    // Store the result of addition in memory
    ldr x0, =add_result   // Load address of add_result into x0 (64-bit register for address)
    str w3, [x0]          // Store the value of w3 at the add_result address

    // Perform the multiplication
    mul w4, w1, w2        // Multiply w1 and w2, store result in w4

    // Store the result of multiplication in memory
    ldr x0, =mul_result   // Load address of mul_result into x0 (64-bit register for address)
    str w4, [x0]          // Store the value of w4 at the mul_result address

    // Exit the program
    mov x8, #93           // syscall: exit
    mov x0, #0            // status: 0
    svc #0
