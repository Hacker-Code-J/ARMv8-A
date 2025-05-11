#include "arith.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void bn_print(char* str, u64* data, i32 len) {
    printf("\n[%s]\n", str);
    for (i32 idx = len - 1; idx >= 0; idx--)
        printf("%lx ", data[idx]);
    puts("");
}

int main() {
    test1();
    // test2();
    // test3();
    // test4();
    // test5();
    // test6();
    // test7();
    // test8();
    // test9();
    // test10();
    // test11_1();
    // test11_2();
    // test12();
    // test13();
    // test14();
    // test15();
    // test16();
    return 0;
}

void test1() {
    i32 data1 = 10;
    i32 data2 = 20;
    i32 res1 = 0;
    i64 res2 = 0;

    res1 = add_asm(data1, data2);
    printf("%2d = %2d + %2d\n", res1, data1, data2);
    res2 = add_shift_asm(data1, data2);
    printf("%2ld = %2d + %2d\n", res2, data1, data2);
}
// void test2();
// void test3();
// void test4();
// void test5();
// void test6();
// void test7();
// void test8();
// void test9();
// void test10();
// void test11_1();
// void test11_2();
// void test12();
// void test13();
// void test14();
// void test15();
// void test16();


// EOF
