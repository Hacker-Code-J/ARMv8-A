// add_fn.c

#include <stdio.h>

// Declaration of the assembly function
void calculate_numbers(unsigned long *high, unsigned long *low);

int main() {
    unsigned long result_high = 0, result_low = 0;

    // Call the assembly function
    calculate_numbers(&result_high, &result_low);

    // Print the result as a 128-bit number
    printf("Result: 0x%016lx%016lx\n", result_high, result_low);

    return 0;
}