#include "arith.h"

/* My Code */
u32 bn_add_c(u64* res, u64* op1, u64* op2, i32 len) {
    u64 tmp;
    u64 carry = 0;

    /* ret = op1 + op2 mod 2^32 
    *
    * 
    */
    for (int idx = 0; idx < len; idx++) {
        tmp = op1[idx] + carry;
        carry = (tmp < carry);
        tmp += op2[idx];
        res[idx] = tmp;
    }
    return carry;
}

/* Sample Code */
uint32_t bn_add_c_sample(uint64_t *ret, uint64_t *opA, uint64_t *opB, int32_t len) {
    int32_t cnt_i;
    uint64_t carry = 0, temp = 0;

    for(cnt_i = 0; cnt_i < len; cnt_i++) {
        temp = opA[cnt_i];
        temp += carry;
        carry = (temp < carry);
        temp += opB[cnt_i];
        carry += (temp < opB[cnt_i]);
        ret[cnt_i] = temp;
    }
    return carry;
}