#include "arith.h"

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
