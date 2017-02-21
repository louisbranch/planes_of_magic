#ifndef MATH_H_
#define MATH_H_

#include "platform.h"

inline r32 Lerp(r32 a, r32 b, r32 t) { return (1.0f - t) * a + t * b; }

inline r32 Clamp(r32 x, r32 min, r32 max) {
  if (x < min) {
    return min;
  }
  if (x > max) {
    return max;
  }
  return x;
}

#endif  // MATH_H_
