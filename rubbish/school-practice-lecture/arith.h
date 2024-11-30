#include <stdint.h>

#ifndef _ARITH_H_
#define _ARITH_H_

typedef uint8_t     u8;
typedef uint32_t    u32;
typedef uint64_t    u64;

typedef int8_t      i8;
typedef int32_t     i32;
typedef int64_t     i64;

void test1();
void test2();
void test3();
void test4();
void test5();
void test6();
void test7();
void test8();
void test9();
void test10();
void test11_1();
void test11_2();
void test12();
void test13();
void test14();
void test15();
void test16();

extern i32 add_asm(i32 data1, i32 data2);
extern i64 add_shift_asm(i32 data1, i32 data2);

#endif  // _ARITH_H_