#ifndef PLATFORM_H_
#define PLATFORM_H_

#include <stdint.h>

typedef int8_t s8;
typedef int16_t s16;
typedef int32_t s32;
typedef int64_t s64;

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;
typedef float r32;
typedef double r64;

struct V2 {
  r64 x, y;
};

struct V3 {
  r64 x, y, z;
};

struct Point2D {
  s32 x, y;
};

struct Size {
  s32 w, h;
};

#endif  // PLATFORM_H_
