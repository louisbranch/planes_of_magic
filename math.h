#ifndef MATH_H_
#define MATH_H_

#include "platform.h"

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
