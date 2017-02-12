#ifndef map_H_
#define map_H_

namespace map {

enum TERRAIN { WATER, GRASS };

typedef struct Tile {
  TERRAIN terrain;
  double elevation;
  double moisture;
} Tile;

class Map {
 public:
  int w;
  int h;
  Tile* tiles;

  void Build();
};

double noise_elevation(double, double);
double noise_moisture(double, double);

TERRAIN biome(double, double);
}

#endif  // map_H_
