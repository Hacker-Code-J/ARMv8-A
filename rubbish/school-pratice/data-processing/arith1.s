        .data
fmt:    .asciz    "The sum is %d\n"
        .align    2
x:      .word     5
y:      .word     8
        .text
        .type     main, %function
        .global   main
        .extern   printf               // Declare printf as an external function

main:
        stp     x29, x30, [sp, #-16]!  // Push FP, LR onto the stack
        // mov     x29, sp                // Set up the frame pointer
        // sum = x + y
        adr     x14, x                 // Load address of x
        adr     x15, y                 // Load address of y 
        ldr     x4, [x14]              // Load x as a 32-bit signed integer
        ldr     x5, [x15]              // Load y as a 32-bit signed integer
        add     x1, x4, x5             // x1 = x4 + x5 (sum of x and y)

        // printf("The sum is %d\n", sum)
        adr     x0, fmt                // Load address of fmt
        bl      printf                 // Call printf

        // return 0
        mov     w0, #0
        ldp     x29, x30, [sp], #16    // Pop FP and LR from the stack
        ret                            // Return from main
        .size   main, (. - main)
