#include "config.h"

#ifndef _ARITH_H_
#define _ARITH_H_

/* My Code */
u32 bn_add_c(u64* res, u64* op1, u64* op2, i32 len);

/* Sample Code */

uint32_t
bn_add_c_sample(uint64_t *ret, uint64_t *opA, uint64_t *opB, int32_t len);

extern int32_t
add_asm(int32_t dataA, int32_t dataB);

extern int64_t
add_shift_asm(int32_t dataA, int32_t dataB);

extern uint32_t
bn_add_asm(uint64_t *ret, uint64_t *opA, uint64_t *opB, int32_t len);

#endif  // _ARITH_H_