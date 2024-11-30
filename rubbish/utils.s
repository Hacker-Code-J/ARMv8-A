// src/utils.s
.section .text
.global add_two_numbers
add_two_numbers:
    // w0 = first number, w1 = second number
    add w0, w0, w1        // Perform addition
    ret                   // Return the result in w0
