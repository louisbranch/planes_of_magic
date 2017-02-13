#ifndef map_H_
#define map_H_

namespace map {

enum TERRAIN {
  OCEAN,
  BEACH,
  SCORCHED,
  BARE,
  TUNDRA,
  SNOW,
  TEMPERATE_DESERT,
  SHRUBLAND,
  TAIGA,
  GRASSLAND,
  TEMPERATE_DECIDUOUS_FOREST,
  TEMPERATE_RAIN_FOREST,
  SUBTROPICAL_DESERT,
  TROPICAL_SEASONAL_FOREST,
  TROPICAL_RAIN_FOREST
};

typedef struct Tile {
  TERRAIN terrain;
} Tile;

class Map {
 public:
  int w;
  int h;
  Tile* tiles;

  void Build();
};

double noise1(double, double);
double noise2(double, double);

TERRAIN biome(double, double);
}

#endif  // map_H_
