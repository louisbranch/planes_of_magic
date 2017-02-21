#include "platform.h"

enum UnitType { Hero };

struct Unit {
  V2 pos;
  V2 target_pos;
  UnitType type;
  s32 speed;
};
