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