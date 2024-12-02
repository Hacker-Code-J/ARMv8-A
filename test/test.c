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
	uint64_t opA1[P256_64BIT_WORD_LEN] = {0, }, opB1[P256_64BIT_WORD_LEN] = {0, }, ret1[P256_64BIT_WORD_LEN] = {0, };
	uint64_t opA2[P256_64BIT_WORD_LEN] = {0, }, opB2[P256_64BIT_WORD_LEN] = {0, }, ret2[P256_64BIT_WORD_LEN] = {0, };
	uint32_t carry1 = 0, carry2 = 0;

	srand(time(NULL));

	for(cnt_i = 0; cnt_i < P256_64BIT_WORD_LEN; cnt_i++)
	{
		opA1[cnt_i] = (generate_random_64bit());
		// opA1[cnt_i] <<= 16;
		// opA1[cnt_i] |= (generate_random_64bit());
		// opA1[cnt_i] <<= 16;
		// opA1[cnt_i] |= (generate_random_64bit());
		// opA1[cnt_i] <<= 16;
		// opA1[cnt_i] |= (generate_random_64bit());

		opA2[cnt_i] = opA1[cnt_i];

		opB1[cnt_i] = (generate_random_64bit());
		// opB1[cnt_i] <<= 16;
		// opB1[cnt_i] |= (generate_random_64bit());
		// opB1[cnt_i] <<= 16;
		// opB1[cnt_i] |= (generate_random_64bit());
		// opB1[cnt_i] <<= 16;
		// opB1[cnt_i] |= (generate_random_64bit());

		opB2[cnt_i] = opB1[cnt_i];
	}

	carry1 = bn_add_c_sample(ret1, opA1, opB1, P256_64BIT_WORD_LEN);
	carry2 = bn_add_asm(ret2, opA2, opB2, P256_64BIT_WORD_LEN);

	bn_print("opA", opA1, P256_64BIT_WORD_LEN);
	bn_print("opB", opB1, P256_64BIT_WORD_LEN);

	bn_print("ret1", ret1, P256_64BIT_WORD_LEN);
	bn_print("ret2", ret2, P256_64BIT_WORD_LEN);

	measure_clock_cycles(bn_add_c_sample, ret1, opA1, opB1, P256_64BIT_WORD_LEN);
	measure_clock_cycles(bn_add_asm, ret1, opA1, opB1, P256_64BIT_WORD_LEN);
}