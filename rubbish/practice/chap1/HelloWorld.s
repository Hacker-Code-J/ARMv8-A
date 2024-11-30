//
// Assembler program to print "Hello World!"
// to stdout on AArch64 architecture.
//
.global _start           // Provide program starting address to linker
.align 4                 // Make sure everything is aligned properly

// Setup the parameters to print hello world
// and then call the Kernel to do it.
_start: 
    mov     X0, #1              // 1 = StdOut (file descriptor)
    adr     X1, helloworld      // X1 = pointer to string
    mov     X2, #13             // X2 = length of string
    mov     X8, #64             // syscall number for write (AArch64)
    svc     #0                  // Call kernel to output the string

// Setup the parameters to exit the program
// and then call the kernel to do it.
    mov     X0, #0              // X0 = exit code
    mov     X8, #93             // syscall number for exit (AArch64)
    svc     #0                  // Call kernel to terminate the program

helloworld: 
    .ascii  "Hello World!\n"