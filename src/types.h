#ifndef TYPES_H
#define TYPES_H

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define i16 int16_t
#define i32 int32_t
#define i64 long long
#define u8 unsigned char
#define u64 unsigned long long
#define f32 float
#define f64 double

#ifdef DEBUG
#define LOG(...) printf(__VA_ARGS__)
#else
#define LOG(...)
#endif

#endif // TYPES_H
