#include "measure.h"

void 
measure_clock_cycles(uint32_t (*func)(uint64_t*, uint64_t*, uint64_t*, int),
                     uint64_t* ret, uint64_t* op1, uint64_t* op2, int len) {
    
    puts("==============clock-cycle-start==============");
    uint64_t start1, end1;
    uint64_t start2, end2; 
    uint64_t res1, res2; 
    const int num = 10000;

    // Measure the function
    start1 = read_cycle_counter();
    for(int i = 0; i < num; i++) {
        func(ret, op1, op2, len);
    }
    end1 = read_cycle_counter();
    res1 = end1 - start1;
    printf("%lu cycles\n", res1);

    // Measure the overhead of an empty loop
    start2 = read_cycle_counter();
    for(int i = 0; i < num; i++) {
        asm volatile(""); // prevent loop from being optimized out
    }
    end2 = read_cycle_counter();
    res2 = end2 - start2;
    printf("%lu cycles for overhead\n", res2);
    
    printf("Average cycles per call: %.4f\n", (double)(res1 - res2) / num);

    puts("==============clock-cycle-end================");
    puts("");
}