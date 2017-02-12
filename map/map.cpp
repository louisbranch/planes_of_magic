#include "map.h"

namespace map {
void Map::Build() {
  int size = w * h;
  tiles = new Tile[size];

  for (int y = 0; y < h; y++) {
    for (int x = 0; x < w; x++) {
      if (x % 2 == 0) {
        tiles[x + y * w] = {terrain : GRASS};
      } else {
        tiles[x + y * w] = {terrain : WATER};
      }
    }
  }
}
}
