#include "utils.h"

void bn_print(char* str, u64* data, i32 len) {
	printf("\n[%s] ", str);
	for(i32 idx = len-1; idx >= 0; idx--)
		printf("%lx ", data[idx]);
	puts("");
}

uint64_t generate_random_64bit() {
    uint64_t random_value = 0;
    uint8_t* p = (uint8_t*)&random_value;

    // Loop through each byte of uint64_t
    for (size_t i = 0; i < 1024; i++) {
		random_value += (*p ^ rand());
		p++;
    }

    return random_value;
}