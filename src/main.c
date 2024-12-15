#include "config.h"
#include "arith.h"
#include "utils.h"
#include "test.h"
#include "measure.h"

#define PRIME   4294967291lu
#define LOG_Q   32

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

void
addmul_P32_into_64_C(uint64_t* a, const uint32_t b, const uint32_t c){
  uint64_t r=b;
  r *= c;
  *a += r;
  /* forces reduction to 33-bits ? */
  *a -= PRIME*((*a)>>LOG_Q);
}

extern void
addmul_P32_into_64_ARM(uint64_t* a, const uint32_t b, const uint32_t c);


int main() {
    // Seed random number generator
    srand((unsigned)time(NULL));
    
    uint64_t* a_vals = (uint64_t*)malloc(NUM_ITERATIONS * sizeof(uint64_t));
    uint32_t* b_vals = (uint32_t*)malloc(NUM_ITERATIONS * sizeof(uint32_t));
    uint32_t* c_vals = (uint32_t*)malloc(NUM_ITERATIONS * sizeof(uint32_t));

    if (!a_vals || !b_vals || !c_vals) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    generate_random_inputs(b_vals, c_vals, NUM_ITERATIONS);
    a_vals[0] = (uint64_t)(*b_vals * *c_vals) << 32;

    printf("Benchmarking addmul_P32_into_64 functions:\n\n");
    uint64_t test_a = a_vals[0]; uint32_t test_b = b_vals[0], test_c = c_vals[0];
    uint64_t test_a2 = a_vals[0]; uint32_t test_b2 = b_vals[0], test_c2 = c_vals[0];
    addmul_P32_into_64_C(&test_a, test_b, test_c);
    addmul_P32_into_64_ARM(&test_a2, test_b2, test_c2);

    if (test_a != test_a2) {
        fprintf(stderr, "Error: Function outputs do not match!\n");
        printf("b = 0x%08x\nc = 0x%08x\n", test_b, test_c);
        fprintf(stderr, "  C: 0x%016lx,\nARM: 0x%016lx,\n", test_a, test_a2);
        free(a_vals);
        free(b_vals);
        free(c_vals);
        return EXIT_FAILURE;
    }
    
    printf("a = 0x%016lx,\nb = 0x%08x\nc = 0x%08x\n", test_a, test_b, test_c);
    printf("a = 0x%016lx,\nb = 0x%08x\nc = 0x%08x\n", test_a2, test_b2, test_c2);
    printf("  C: 0x%016lx,\nARM: 0x%016lx,\n", test_a, test_a2);
        

    // // Allocate memory for random inputs
    // uint32_t* a_vals = malloc(NUM_ITERATIONS * sizeof(uint32_t));
    // uint32_t* b_vals = malloc(NUM_ITERATIONS * sizeof(uint32_t));

    // if (!a_vals || !b_vals) {
    //     fprintf(stderr, "Memory allocation failed\n");
    //     return EXIT_FAILURE;
    // }

    // // Generate random inputs
    // generate_random_inputs(a_vals, b_vals, NUM_ITERATIONS);

    // printf("Benchmarking multiplicationModuloP functions:\n\n");

    // // Verify correctness
    // uint32_t test_a = a_vals[0], test_b = b_vals[0];
    // // uint32_t test_a = 0x516dea09, test_b = 0x656b46b8;
    // uint64_t result0 = multiplicationModuloP0(test_a, test_b);
    // uint64_t result1 = multiplicationModuloP1(test_a, test_b);

    // if (result0 != result1) {
    //     fprintf(stderr, "Error: Function outputs do not match!\n");
    //     printf("a = 0x%08x\nb = 0x%08x\n", test_a, test_b);
    //     // fprintf(stderr, "P0: 0x%016lx,\nP1: 0x%016lx,\nP2: 0x%016lx,\nP3: 0x%016lx\n", result0, result1, result2, result3);
    //     fprintf(stderr, "P0: 0x%016lx,\nP1: 0x%016lx,\n", result0, result1);
    //     free(a_vals);
    //     free(b_vals);
    //     return EXIT_FAILURE;
    // }

    // // Benchmark each implementation with the same inputs
    // double time_basic = benchmark("multiplicationModuloP0", multiplicationModuloP0, a_vals, b_vals, NUM_ITERATIONS);
    // double time_optimized1 = benchmark("multiplicationModuloP1", multiplicationModuloP1, a_vals, b_vals, NUM_ITERATIONS);

    // // Compare performance
    // printf("\nPerformance Comparison:\n");
    // printf("Optimized1 is %.5fx faster than Basic.\n", time_basic / time_optimized1);

    // // Free allocated memory
    // free(a_vals);
    // free(b_vals);

    return EXIT_SUCCESS;
}