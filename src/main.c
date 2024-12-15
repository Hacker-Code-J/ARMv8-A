#include "config.h"
#include "arith.h"
#include "utils.h"
#include "test.h"
#include "measure.h"

#define NUM_ITERATIONS 10000000 // Number of iterations for benchmarking

uint64_t
multiplicationModuloP0(const uint32_t a, const uint32_t b) {
  uint64_t r = a * (uint64_t)b;
//   printf("r                            : 0x%016lx\n", r);
//   printf("r >> 32                      : 0x%016lx\n", r >> 32);
//   printf("0xFFFFFFFB * (r >> 32)       : 0x%016lx\n", 0xFFFFFFFB * (r >> 32));
//   printf("r - (0xFFFFFFFB * (r >> 32)) : 0x%016lx\n", r - (0xFFFFFFFB * (r >> 32)));
  r = r - (0xFFFFFFFB * (r >> 32));
  return r;
}

extern uint64_t
multiplicationModuloP1(const uint32_t a, const uint32_t b);
extern uint64_t
multiplicationModuloP2(const uint32_t a, const uint32_t b);

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
    // uint32_t test_a = a_vals[0], test_b = b_vals[0];
    uint32_t test_a = 0x516dea09, test_b = 0x656b46b8;
    uint64_t result0 = multiplicationModuloP0(test_a, test_b);
    uint64_t result1 = multiplicationModuloP1(test_a, test_b);
    uint64_t result2 = multiplicationModuloP2(test_a, test_b);
    // uint64_t result3 = multiplicationModuloP3(test_a, test_b);

    if (result0 != result1 || result1 != result2) {
        fprintf(stderr, "Error: Function outputs do not match!\n");
        printf("a = 0x%08x\nb = 0x%08x\n", test_a, test_b);
        // fprintf(stderr, "P0: 0x%016lx,\nP1: 0x%016lx,\nP2: 0x%016lx,\nP3: 0x%016lx\n", result0, result1, result2, result3);
        fprintf(stderr, "P0: 0x%016lx,\nP1: 0x%016lx,\nP2: 0x%016lx,", result0, result1, result2);
        free(a_vals);
        free(b_vals);
        return EXIT_FAILURE;
    }

    // Benchmark each implementation with the same inputs
    double time_basic = benchmark("multiplicationModuloP0", multiplicationModuloP0, a_vals, b_vals, NUM_ITERATIONS);
    double time_optimized1 = benchmark("multiplicationModuloP1", multiplicationModuloP1, a_vals, b_vals, NUM_ITERATIONS);
    double time_optimized2 = benchmark("multiplicationModuloP2", multiplicationModuloP2, a_vals, b_vals, NUM_ITERATIONS);

    // Compare performance
    printf("\nPerformance Comparison:\n");
    printf("Optimized1 is %.5fx faster than Basic.\n", time_basic / time_optimized1);
    printf("Optimized1 is %.5fx faster than Optimized2.\n", time_optimized1 / time_optimized2);

    // Free allocated memory
    free(a_vals);
    free(b_vals);

    return EXIT_SUCCESS;
}
