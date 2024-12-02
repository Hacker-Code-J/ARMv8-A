#include "config.h"

#ifndef _MEASURE_H_
#define _MEASURE_H_

// static inline uint64_t read_cycle_counter() {
//     uint64_t value;
//     // For ARMv8, use:
//     asm volatile("mrs %0, PMCCNTR_EL0" : "=r" (value));
//     return value;
// }

static inline uint64_t read_cycle_counter() {
    uint64_t value;
    asm volatile("isb");
    asm volatile("mrs %0, CNTVCT_EL0" : "=r" (value));
    return value;
}

void
measure_clock_cycles(u32 (*func)(u64*, u64*, u64*, i32),
                     u64* ret, u64* op1, u64* op2, i32 len);


#endif  // _MEASURE_H_