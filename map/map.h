#ifndef map_H_
#define map_H_

namespace map {

enum TERRAIN { WATER, GRASS };

typedef struct Tile { TERRAIN terrain; } Tile;

class Map {
 public:
  int w;
  int h;
  Tile* tiles;

  void Build();
};
}

#endif  // map_H_
