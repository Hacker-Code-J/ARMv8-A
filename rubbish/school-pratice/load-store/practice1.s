    .text
    .global _start        // Declare _start as a global symbol

_start:
    // Call main
    bl      main               // Branch with link to main
    // Exit the program by calling the exit system call
    mov     w0, #0            // Exit code 0
    mov     x8, #93           // syscall number for exit on ARM64
    svc     #0                // Make the system call

    .type main, %function
    .global main

main:
    mov     x4, #0x7fff  
    ldr     w8, [x4]   
    stp     x29, x30, [sp, #-0x10]!   // Store x29 and x30 on the stack, adjust stack pointer
    mov     x29, #0x0                 // Set x29 as the new frame pointer
    mov     x0, #0x0                  // (Optional) Set return value in x0
    ldp     x29, x30, [sp], #0x10     // Restore x29 and x30, adjust stack pointer back
    ret                         // Return from main
    .size main, (. - main)
