#include "arith.h"

#ifndef _TEST_H_
#define _TEST_H_

void test1();
void test2();

void generate_random_inputs(uint32_t *a_vals, uint32_t *b_vals, size_t count);
void generate_random_32bit(uint32_t* a_vals, size_t count);
double benchmark(const char* name, uint64_t (*func)(const uint32_t, const uint32_t),
                 const uint32_t* a_vals, const uint32_t* b_vals, size_t count);

#endif  // _TEST_H_