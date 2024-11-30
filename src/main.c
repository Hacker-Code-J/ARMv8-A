#include "config.h"

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
    uint64_t op1[3] = {0xFFFFFFFFFFFFFFFF, 0x99aabbccddeeff00, 0x1122334455667788};
    uint64_t op2[3] = {0x0000000000000001, 0x1122334455667788, 0x99aabbccddeeff00};
    uint64_t res_asm[3];
    uint64_t res_c[3];
    int n = sizeof(op1) / sizeof(op1[0]);

    bn_add_asm(res_asm, op1, op2, n);
    bn_add_c(res_c, op1, op2, n);

    // printf("%02x %02x %02x\n", op1[0], op1[1], op1[2]);
    // printf("%02x %02x %02x\n", op2[0], op2[1], op2[2]);
    // printf("%02x %02x %02x\n", res_asm[0], res_asm[1], res_asm[2]);
    // printf("%02x %02x %02x\n", res_c[0], res_c[1], res_c[2]);

    for (int i = 0; i < n; i++) {
        printf("0x%016" PRIx64 ":", res_asm[i]);
    } puts("");

    for (int i = 0; i < n; i++) {
        printf("0x%016" PRIx64 ":", res_c[i]);
    } puts("");

    return 0;
}
