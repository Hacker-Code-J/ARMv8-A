#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>

extern void bn_add_asm(uint64_t *res, const uint64_t *op1, const uint64_t *op2, int32_t n);

void bn_add_c(uint64_t *res, const uint64_t *op1, const uint64_t *op2, int32_t n) {
    uint64_t carry = 0;
    uint64_t temp = 0;

    for (int i = 0; i < n; i++) {
        temp = op1[i];
        temp += carry;
        carry = (temp < carry);
        temp += op2[i];
        carry += (temp < op2[i]);
        res[i] = temp;
    }
}

int main() {
    uint64_t op1[] = {1, 2, 3};
    uint64_t op2[] = {4, 0xFFFFFFFFFFFFFFFF, 6};
    uint64_t res_asm[3];
    uint64_t res_c[3];
    int n = sizeof(op1) / sizeof(op1[0]);

    bn_add_asm(res_asm, op1, op2, n);
    bn_add_c(res_c, op1, op2, n);

    for (int i = 0; i < n; i++) {
        printf("0x%" PRIx64 ":", i, res_asm[i]);
    } puts("");

    for (int i = 0; i < n; i++) {
        printf("0x%" PRIx64 ":", i, res_c[i]);
    } puts("");

    return 0;
}
