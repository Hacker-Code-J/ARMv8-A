#include "arith.h"

uint32_t bn_add_c(uint64_t *ret, uint64_t *opA, uint64_t *opB, int32_t len) {
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