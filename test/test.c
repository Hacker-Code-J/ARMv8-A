#include "utils.h"
#include "test.h"
#include "measure.h"

void test1() {
	int32_t dataA = 10;
	int32_t dataB = 20;
	int32_t result = 0;
	int64_t result2 = 0;
	
	result = add_asm(dataA, dataB);
	
	printf("%d = %d + %d\n", result, dataA, dataB);

	result2 = add_shift_asm(dataA, dataB);
	
	printf("%ld = %d + %d\n", result2, dataA, dataB);
}

void test2() {
	int32_t cnt_i;
	uint64_t opA[P256_64BIT_WORD_LEN] = {0, },
			 opB[P256_64BIT_WORD_LEN] = {0, },
			 ret1[P256_64BIT_WORD_LEN] = {0, },
			 ret2[P256_64BIT_WORD_LEN] = {0, },
			 ret3[P256_64BIT_WORD_LEN] = {0, };

	srand(time(NULL));

	for(cnt_i = 0; cnt_i < P256_64BIT_WORD_LEN; cnt_i++) {
		opA[cnt_i] = (generate_random_64bit());
		opB[cnt_i] = (generate_random_64bit());
	}

	u32 carry1 = bn_add_c(ret1, opA, opB, P256_64BIT_WORD_LEN);
	u32 carry2 = bn_add_c_sample(ret2, opA, opB, P256_64BIT_WORD_LEN);
	u32 carry3 = bn_add_asm(ret3, opA, opB, P256_64BIT_WORD_LEN);

	printf("%d %d %d\n", carry1, carry2, carry3);

	bn_print("opA", opA, P256_64BIT_WORD_LEN);
	bn_print("opB", opB, P256_64BIT_WORD_LEN);

	bn_print("ret1", ret1, P256_64BIT_WORD_LEN);
	bn_print("ret2", ret2, P256_64BIT_WORD_LEN);
	bn_print("ret2", ret3, P256_64BIT_WORD_LEN);

	measure_clock_cycles(bn_add_c_sample, ret1, opA, opB, P256_64BIT_WORD_LEN);
	measure_clock_cycles(bn_add_c_sample, ret1, opA, opB, P256_64BIT_WORD_LEN);
	measure_clock_cycles(bn_add_asm, ret1, opA, opB, P256_64BIT_WORD_LEN);
}

// Pre-generate random inputs
void generate_random_inputs(uint32_t *a_vals, uint32_t *b_vals, size_t count) {
    for (size_t i = 0; i < count; ++i) {
        a_vals[i] = rand() % 0xFFFFFFFB;
        b_vals[i] = rand() % 0xFFFFFFFB;
    }
}

// Utility function for benchmarking
double benchmark(const char* name, uint64_t (*func)(const uint32_t, const uint32_t),
                 const uint32_t* a_vals, const uint32_t* b_vals, size_t count) {
    uint64_t start_cycles, end_cycles, total_cycles;
    uint64_t result = 0;

    // Record start cycles
    start_cycles = read_cycle_counter();

    // Run the function for each input pair
    for (size_t i = 0; i < count; ++i) {
        result += func(a_vals[i], b_vals[i]);
    }

    // Record end cycles
    end_cycles = read_cycle_counter();

    // Calculate total clock cycles
    total_cycles = end_cycles - start_cycles;

    // Read counter frequency (number of ticks per second)
    uint64_t counter_frequency = read_counter_frequency();

    // Calculate cycles per clock (CPC)
    double cycles_per_clock = (double)total_cycles / count;

    // Calculate time in seconds
    double time_seconds = (double)total_cycles / counter_frequency;

    // printf("%s: Total Clock Cycles = %lu, Cycles per Clock = %.5f, Total Time = %.6f seconds, Result = %lu\n",
    //        name, total_cycles, cycles_per_clock, time_seconds, result);
	
    printf("%.5f\n", cycles_per_clock);
	return 0;
	// uint64_t start_cycles, end_cycles, total_cycles = 0;
    // uint64_t result = 0;

    // // Record start cycles
    // start_cycles = read_cycle_counter();

    // // Run the function for each input pair
    // for (size_t i = 0; i < count; ++i) {
    //     result += func(a_vals[i], b_vals[i]);
    // }

    // // Record end cycles
    // end_cycles = read_cycle_counter();

    // // Calculate total clock cycles
    // total_cycles = end_cycles - start_cycles;

    // printf("%s: Total Clock Cycles = %lu, Result = %lu\n", name, total_cycles, result);
    // return total_cycles;
	
	// struct timespec start, end, start2, end2;
    // uint64_t result = 0;

    // clock_gettime(CLOCK_MONOTONIC, &start); // Start timing

    // for (size_t i = 0; i < count; ++i) {
    //     result += func(a_vals[i], b_vals[i]);
    // }

    // clock_gettime(CLOCK_MONOTONIC, &end); // End timing

    // double time_taken = (end.tv_sec - start.tv_sec) +
    //                     (end.tv_nsec - start.tv_nsec) / 1e9;

    // printf("%s: Total Time = %.6f seconds, Result = %lu\n", name, time_taken, result);
    // return time_taken;
}