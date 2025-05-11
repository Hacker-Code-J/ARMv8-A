#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>         // for uint8_t
#include <inttypes.h>       // for PRIx64
#include <time.h>

#ifndef _CONFIG_H_
#define _CONFIG_H_

typedef int8_t      i8;
typedef int32_t     i32;
typedef int64_t     i64;
typedef uint8_t     u8;

#ifdef _WIN32               // Windows-specific definitions
#include <windows.h>
typedef DWORD       u32;
typedef DWORDLONG   u64;
#elif defined(__linux__)    // Linux-specific definitions
typedef uint32_t    u32;
typedef uint64_t    u64;
#else
#error "Unsupported platform"
#endif

#define P256_64BIT_WORD_LEN	4   // 256-bit = 64-bit x 4
#define P256_32BIT_WORD_LEN	8   // 256-bit = 32-bit x 8

#endif  // _CONFIG_H_
