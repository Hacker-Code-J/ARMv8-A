#include "utils.h"

void bn_print(char* str, uint64_t *data, int32_t len) {
	int32_t cnt_i;
	
	printf("\n[%s]\n", str);
	for(cnt_i = len-1; cnt_i >= 0; cnt_i--)
	{
		printf("%lx ", data[cnt_i]);
	}
	printf("\n");
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