#include "config.h"
#include "arith.h"
#include "utils.h"
#include "test.h"
#include "measure.h"

#include <assert.h>

#define PRIME   4294967291lu
#define LOG_Q   32

#define NUM_ITERATIONS 10500 // Number of iterations for benchmarking

uint64_t
multiplicationModuloP_origin(const uint32_t a, const uint32_t b) {
  uint64_t r = a * (uint64_t)b;
//   printf("r                            : 0x%016lx\n", r);
//   printf("r >> 32                      : 0x%016lx\n", r >> 32);
//   printf("0xFFFFFFFB * (r >> 32)       : 0x%016lx\n", 0xFFFFFFFB * (r >> 32));
//   printf("r - (0xFFFFFFFB * (r >> 32)) : 0x%016lx\n", r - (0xFFFFFFFB * (r >> 32)));
  r = r - (0xFFFFFFFB * (r >> 32));
  return r;
}
extern uint64_t
multiplicationModuloP(const uint32_t a, const uint32_t b);

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

/* Modular reduction 61 to 32bits */
uint32_t
reductionModuloP_origin(const uint64_t a) {
  uint64_t r = a;
  r = r - PRIME * (r >> LOG_Q);
  r = r - PRIME * (r >> LOG_Q);
  return (uint32_t)r;
}
extern uint32_t
reductionModuloP(const uint64_t a);
extern uint32_t inversionModuloP(const uint32_t a);
uint32_t inversionModuloP_origin_test(const uint32_t a) {
  /* Takagi's algorithm (as advised by J.C Bajard) */
  uint32_t b0,b1,b2,b3;
  int i;
  printf("a: 0x%x\n", a);
  b0=reductionModuloP_origin(multiplicationModuloP_origin(a,a));
  printf("b0: 0x%x\n", b0);
  b0=reductionModuloP_origin(multiplicationModuloP_origin(b0,a));
  printf("b0: 0x%x\n", b0);

  b1=reductionModuloP_origin(multiplicationModuloP_origin(b0,b0));
  printf("\nb1: 0x%x\n", b1);
  b1=reductionModuloP_origin(multiplicationModuloP_origin(b1,b1));
  printf("b1: 0x%x\n", b1);
  b1=reductionModuloP_origin(multiplicationModuloP_origin(b1,b0));
  printf("b1: 0x%x\n", b1);

  b2=b1;
  printf("\nb2: 0x%x\n", b2);
  for(i=0;i<4;i++) {
    b2=reductionModuloP_origin(multiplicationModuloP_origin(b2,b2));
    printf("[%d] b2: 0x%x\n", i, b2);
  }
  b2=reductionModuloP_origin(multiplicationModuloP_origin(b2,b1));
  printf("b2: 0x%x\n", b2);
  b3=b2;
  printf("\nb3: 0x%x\n", b3);

  for(i=0;i<8;i++) {
    b3=reductionModuloP_origin(multiplicationModuloP_origin(b3,b3));
    printf("[%d] b3: 0x%x\n", i, b3);
  }
  b3=reductionModuloP_origin(multiplicationModuloP_origin(b3,b2));
  printf("b3: 0x%x\n", b3);

  for(i=0;i<8;i++) {
    b3=reductionModuloP_origin(multiplicationModuloP_origin(b3,b3));
    printf("[%d] b3: 0x%x\n", i, b3);
  }
  b3=reductionModuloP_origin(multiplicationModuloP_origin(b3,b2));
  printf("b3: 0x%x\n", b3);

  for(i=0;i<4;i++) {
    b3=reductionModuloP_origin(multiplicationModuloP_origin(b3,b3));
    printf("[%d] b3: 0x%x\n", i, b3);
  }
  b3=reductionModuloP_origin(multiplicationModuloP_origin(b3,b1));
  printf("b3: 0x%x\n", b3);

  b3=reductionModuloP_origin(multiplicationModuloP_origin(b3,b3));
  printf("\nb3: 0x%x\n", b3);
  b3=reductionModuloP_origin(multiplicationModuloP_origin(b3,a));
  printf("b3: 0x%x\n", b3);

  b3=reductionModuloP_origin(multiplicationModuloP_origin(b3,b3));
  printf("b3: 0x%x\n", b3);
  b3=reductionModuloP_origin(multiplicationModuloP_origin(b3,b3));
  printf("b3: 0x%x\n", b3);
  b3=reductionModuloP_origin(multiplicationModuloP_origin(b3,b3));
  printf("b3: 0x%x\n", b3);
  b3=reductionModuloP_origin(multiplicationModuloP_origin(b3,a));
  printf("b3: 0x%x\n", b3);
  
  printf("Final inverse: 0x%x\n", b3);
  return (b3);
}
uint32_t inversionModuloP_origin(const uint32_t a) {
  /* Takagi's algorithm (as advised by J.C Bajard) */
  uint32_t b0,b1,b2,b3;
  int i;
  b0=reductionModuloP_origin(multiplicationModuloP_origin(a,a));
  b0=reductionModuloP_origin(multiplicationModuloP_origin(b0,a));

  b1=reductionModuloP_origin(multiplicationModuloP_origin(b0,b0));
  b1=reductionModuloP_origin(multiplicationModuloP_origin(b1,b1));
  b1=reductionModuloP_origin(multiplicationModuloP_origin(b1,b0));

  b2=b1;
  for(i=0;i<4;i++) {
    b2=reductionModuloP_origin(multiplicationModuloP_origin(b2,b2));
  }
  b2=reductionModuloP_origin(multiplicationModuloP_origin(b2,b1));
  b3=b2;

  for(i=0;i<8;i++) {
    b3=reductionModuloP_origin(multiplicationModuloP_origin(b3,b3));
  }
  b3=reductionModuloP_origin(multiplicationModuloP_origin(b3,b2));

  for(i=0;i<8;i++) {
    b3=reductionModuloP_origin(multiplicationModuloP_origin(b3,b3));
  }
  b3=reductionModuloP_origin(multiplicationModuloP_origin(b3,b2));

  for(i=0;i<4;i++) {
    b3=reductionModuloP_origin(multiplicationModuloP_origin(b3,b3));
  }
  b3=reductionModuloP_origin(multiplicationModuloP_origin(b3,b1));

  b3=reductionModuloP_origin(multiplicationModuloP_origin(b3,b3));
  b3=reductionModuloP_origin(multiplicationModuloP_origin(b3,a));

  b3=reductionModuloP_origin(multiplicationModuloP_origin(b3,b3));
  b3=reductionModuloP_origin(multiplicationModuloP_origin(b3,b3));
  b3=reductionModuloP_origin(multiplicationModuloP_origin(b3,b3));
  b3=reductionModuloP_origin(multiplicationModuloP_origin(b3,a));
  return (b3);
}

void testInversionModuloP() {
    struct TestCase {
        uint32_t a;
        uint32_t expected;
    } testCases[] = {
        {0xFFFFFFF7U, 0xBFFFFFFCU},
        {0x1, 0x1},
        {0x3, 0x55555554U},
        {0x5, 0xccccccc9U},
        {0x7, 0x24924924U},
        {0x9, 0x1c71c71cU},
        {0xB, 0x1745d174U},
        {0xD, 0x3b13b13aU},
        {0xF, 0x44444443U},
        {0xFFFFFFFAU, 0xFFFFFFFAU},
        {0xFFFFFFF9U, 0x7FFFFFFDU},
        {0xFFFFFFF5U, 0xD5555551U},
        {0xFFFFFFF3U, 0x5FFFFFFEU},
        {0xFFFFFFEFU, 0xEAAAAAA6U},
        {0xFFFFFFEBU, 0x2FFFFFFFU},
        {0xFFFFFFE7U, 0x8CCCCCCAU},
    };
    // for (int i = 0; i < sizeof(testCases)/ sizeof(testCases[0]); i++)
    //   printf("0x%08x & 0x%08x \\\\ \n", testCases[i].a, testCases[i].expected);

    for (int i = 0; i < sizeof(testCases) / sizeof(testCases[0]); ++i) {
        uint32_t result = inversionModuloP_origin(testCases[i].a);
        uint32_t result2 = inversionModuloP(testCases[i].a);
        printf("\n\nTesting0 a = 0x%x => Expected: 0x%x, Got: 0x%x\n", testCases[i].a, testCases[i].expected, result);
        printf("Testing1 a = 0x%x => Expected: 0x%x, Got: 0x%x\n", testCases[i].a, testCases[i].expected, result2);
        assert(result == result2 && result == testCases[i].expected);
    }

    srand((unsigned int)time(NULL));
    for (int i = 0; i < 10; ++i) {
        uint32_t a = rand() % PRIME;
        if (a == 0) continue;

        uint32_t inverse = inversionModuloP(a);
        if (inverse != 0) {
            assert((uint64_t)a * inverse % PRIME == 1);
            printf("Random test: a = 0x%x, inverse = %x (a * inverse %% PRIME = 0x%lx)\n", a, inverse, (uint64_t)a * inverse % PRIME);
        } else {
            printf("Random test: a = 0x%x is not invertible modulo 0x%lx\n", a, PRIME);
        }
    }
}

// Benchmarking function
void benchmarkInversionFunctions() {
    uint32_t test_a = 0x00;
    uint64_t start, end;
    uint64_t totalCyclesP0 = 0, totalCyclesP = 0;
    for (int i = 0; i < 10500; i++) {
      srand((unsigned)time(NULL));
      if (i > 499) {
        generate_random_32bit(&test_a, 100);
        // printf("a=0x%08x\n",test_a);
        start = read_cycle_counter();
        for (int i = 0; i < NUM_ITERATIONS; i++) {
            volatile uint32_t result = inversionModuloP_origin(test_a);
        }
        end = read_cycle_counter();
        totalCyclesP0 = end - start;

        // Benchmark inversionModuloP
        start = read_cycle_counter();
        for (int i = 0; i < NUM_ITERATIONS; i++) {
            volatile uint32_t result = inversionModuloP(test_a);
        }
        end = read_cycle_counter();
        totalCyclesP = end - start;

        double cyclesPerTestP0 = (double)totalCyclesP0 / NUM_ITERATIONS;
        double cyclesPerTestP = (double)totalCyclesP / NUM_ITERATIONS;
    
        printf("%.5f\n", cyclesPerTestP0);
        printf("%.5f\n", cyclesPerTestP);
      }
    }
    

    // Print results
    // Print results
    // printf("Cycles per test for inversionModuloP0: %.5f\n", cyclesPerTestP0);
    // printf("Cycles per test for inversionModuloP: %.5f\n", cyclesPerTestP);
    // printf("Benchmark Results (over %d tests):\n", NUM_ITERATIONS);
    // printf("inversionModuloP1: %lu clock cycles\n", totalCyclesP0);
    // printf("inversionModuloP: %lu clock cycles\n", totalCyclesP);

    // Compare performance
    // if (totalCyclesP0 < totalCyclesP) {
    //     printf("inversionModuloP1 is faster by %.2f%%\n", ((double)(totalCyclesP - totalCyclesP0) / totalCyclesP) * 100);
    // } else if (totalCyclesP < totalCyclesP0) {
    //     printf("inversionModuloP is faster by %.2f%%\n", ((double)(totalCyclesP0 - totalCyclesP) / totalCyclesP0) * 100);
    // } else {
    //     printf("Both functions have similar performance.\n");
    // }
}

int main() {
    // Seed random number generator
    srand((unsigned)time(NULL));
    // testInversionModuloP();
    // printf("All tests passed!\n");
    benchmarkInversionFunctions();
    // uint64_t* a_vals = (uint64_t*)malloc(NUM_ITERATIONS * sizeof(uint64_t));
    // uint32_t* b_vals = (uint32_t*)malloc(NUM_ITERATIONS * sizeof(uint32_t));
    // uint32_t* c_vals = (uint32_t*)malloc(NUM_ITERATIONS * sizeof(uint32_t));

    // if (!a_vals || !b_vals || !c_vals) {
    //     fprintf(stderr, "Memory allocation failed\n");
    //     return EXIT_FAILURE;
    // }

    // generate_random_inputs(b_vals, c_vals, NUM_ITERATIONS);
    // a_vals[0] = (uint64_t)(*b_vals * *c_vals) << 32;

    // printf("Benchmarking addmul_P32_into_64 functions:\n\n");
    // uint64_t test_a = a_vals[0]; uint32_t test_b = b_vals[0], test_c = c_vals[0];
    // uint64_t test_a2 = a_vals[0]; uint32_t test_b2 = b_vals[0], test_c2 = c_vals[0];
    // addmul_P32_into_64_C(&test_a, test_b, test_c);
    // addmul_P32_into_64_ARM(&test_a2, test_b2, test_c2);

    // if (test_a != test_a2) {
    //     fprintf(stderr, "Error: Function outputs do not match!\n");
    //     printf("b = 0x%08x\nc = 0x%08x\n", test_b, test_c);
    //     fprintf(stderr, "  C: 0x%016lx,\nARM: 0x%016lx,\n", test_a, test_a2);
    //     free(a_vals);
    //     free(b_vals);
    //     free(c_vals);
    //     return EXIT_FAILURE;
    // }
    
    // printf("a = 0x%016lx,\nb = 0x%08x\nc = 0x%08x\n", test_a, test_b, test_c);
    // printf("a = 0x%016lx,\nb = 0x%08x\nc = 0x%08x\n", test_a2, test_b2, test_c2);
    // printf("  C: 0x%016lx,\nARM: 0x%016lx,\n", test_a, test_a2);
        
    // for (int i = 0; i <10000; i++) {
    //   srand((unsigned)time(NULL));
    // // Allocate memory for random inputs
    // uint32_t* a_vals = malloc(NUM_ITERATIONS * sizeof(uint32_t));
    // uint32_t* b_vals = malloc(NUM_ITERATIONS * sizeof(uint32_t));

    // if (!a_vals || !b_vals) {
    //     fprintf(stderr, "Memory allocation failed\n");
    //     return EXIT_FAILURE;
    // }

    // // Generate random inputs
    // generate_random_inputs(a_vals, b_vals, NUM_ITERATIONS);

    // // printf("Benchmarking multiplicationModuloP functions:\n\n");

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

    // Compare performance
    // printf("\nPerformance Comparison:\n");
    // printf("Optimized1 is %.5fx faster than Basic.\n", time_basic / time_optimized1);

    // Free allocated memory
    // free(a_vals);
    // free(b_vals);
    // }
    return EXIT_SUCCESS;
}