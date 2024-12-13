#include "config.h"
#include "arith.h"
#include "utils.h"
#include "test.h"
#include "measure.h"

#define NUM_ITERATIONS 10000 // Number of iterations for benchmarking

uint64_t
multiplicationModuloP1(const uint32_t a, const uint32_t b) {
//   uint64_t r=a*(uint64_t)b;
//   r=r - (0xFFFFFFFB * (r>>32));
//   return r;
    uint64_t product = (uint64_t)a * b;
    return product % 0xFFFFFFFB;
}
extern uint64_t
multiplicationModuloP2(const uint32_t a, const uint32_t b);
extern uint64_t
multiplicationModuloP3(const uint32_t a, const uint32_t b);

int main() {

    // test1();
    // test2();

    // Seed random number generator
    srand((unsigned)time(NULL));

    // Allocate memory for random inputs
    uint32_t *a_vals = malloc(NUM_ITERATIONS * sizeof(uint32_t));
    uint32_t *b_vals = malloc(NUM_ITERATIONS * sizeof(uint32_t));

    if (!a_vals || !b_vals) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    // Generate random inputs
    generate_random_inputs(a_vals, b_vals, NUM_ITERATIONS);

    printf("Benchmarking multiplicationModuloP functions:\n\n");

    // Verify correctness
    uint32_t test_a = a_vals[0], test_b = b_vals[0];
    uint64_t result1 = multiplicationModuloP1(test_a, test_b);
    uint64_t result2 = multiplicationModuloP2(test_a, test_b);
    uint64_t result3 = multiplicationModuloP3(test_a, test_b);

    if (result1 != result2) {
        fprintf(stderr, "Error: Function outputs do not match!\n");
        printf("a = %08x b= %08x\n", test_a, test_b);
        fprintf(stderr, "P1: 0x%16lx,\nP2: 0x%16lx,\nP3: 0x%16lx\n", result1, result2, result3);
        free(a_vals);
        free(b_vals);
        return EXIT_FAILURE;
    }

    // Benchmark each implementation with the same inputs
    double time_basic = benchmark("multiplicationModuloP1", multiplicationModuloP1, a_vals, b_vals, NUM_ITERATIONS);
    double time_optimized = benchmark("multiplicationModuloP2", multiplicationModuloP2, a_vals, b_vals, NUM_ITERATIONS);

    // Compare performance
    printf("\nPerformance Comparison:\n");
    printf("Optimized is %.2fx faster than Basic.\n", time_basic / time_optimized);

    // Free allocated memory
    free(a_vals);
    free(b_vals);

    return EXIT_SUCCESS;
}
