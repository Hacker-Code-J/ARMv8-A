#include <stdio.h>
#include <inttypes.h>

extern void bn_add_asm(uint64_t *res, const uint64_t *op1, const uint64_t *op2, int n);

int main() {
    uint64_t op1[] = {1, 2, 3};
    uint64_t op2[] = {4, 5, 6};
    uint64_t res[3];
    int n = sizeof(op1) / sizeof(op1[0]);

    bn_add_asm(res, op1, op2, n);

    for (int i = 0; i < n; i++) {
        printf("Result[%d] = %" PRIu64 "\n", i, res[i]);
    }

    return 0;
}
