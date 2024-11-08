#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>

typedef uint64_t    u64;
typedef __uint128_t u128;

// Declaration of the assembly function
void calculate_numbers2(u64 a_high, u64 a_low,
                       u64 b_high, u64 b_low,
                       u64 *result_high, u64 *result_low);

int main() {
    u64 a_high, a_low, b_high, b_low;
    u64 result_high = 0, result_low = 0;
    u64 c_result_high = 0, c_result_low = 0;
    
    // Initialize the random number generator
    srand(time(NULL));

    // Generate random 64-bit numbers (you can also input values if you like)
    a_high = (u64)rand();
    a_low = (u64)rand();
    b_high = (u64)rand();
    b_low = (u64)rand();

    // Print the input values
    printf("Adding two 128-bit numbers:\n");
    printf("A = 0x%016lx %016lx\n", a_high, a_low);
    printf("B = 0x%016lx %016lx\n", b_high, b_low);

    // Call the assembly function to calculate the sum
    calculate_numbers2(a_high, a_low, b_high, b_low, &result_high, &result_low);

    // Print the result as a 128-bit number
    printf("C = 0x%016lx %016lx\n", result_high, result_low);

    /* TEST */

    printf("Benchmarking 128-bit addition (1 million iterations):\n");
    const int iterations = 1000000;  // 1 million iterations for the benchmark

    // Measure time for Assembly addition
    clock_t start_asm = clock();
    for (int i = 0; i < iterations; i++) {
        calculate_numbers2(a_high, a_low, b_high, b_low, &result_high, &result_low);
    }
    clock_t end_asm = clock();
    double time_asm = ((double)(end_asm - start_asm)) / CLOCKS_PER_SEC;

    // Measure time for C addition
    clock_t start_c = clock();
    for (int i = 0; i < iterations; i++) {
        // Perform the same addition in C
        u128 a = ((u128)a_high << 64) | a_low;
        u128 b = ((u128)b_high << 64) | b_low;
        u128 c_result = a + b;
        c_result_high = (u64)(c_result >> 64);
        c_result_low = (u64)(c_result & 0xFFFFFFFFFFFFFFFF);
    }
    clock_t end_c = clock();
    double time_c = ((double)(end_c - start_c)) / CLOCKS_PER_SEC;

    // Print the results
    printf("Asm addition took: %f seconds\n", time_asm);
    printf("  C addition took: %f seconds\n", time_c);

    // Validate the results by comparing the assembly and C results
    if (result_high == c_result_high && result_low == c_result_low) {
        printf("The results match!\n");
    } else {
        printf("The results do not match!\n");
    }


    return 0;
}
