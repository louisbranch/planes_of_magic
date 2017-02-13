#include "map.h"

#include <stdlib.h>
#include <time.h>

#include <noise/module/perlin.h>

noise::module::Perlin gen_elevation;
noise::module::Perlin gen_moisture;

namespace map {

void Map::Build() {
  int size = w * h;
  tiles = new Tile[size];

  srand(time(NULL));

  gen_elevation.SetSeed(rand());
  gen_moisture.SetSeed(rand());

  for (int y = 0; y < h; y++) {
    for (int x = 0; x < w; x++) {
      double nx = x / double(w) - 0.5;
      double ny = y / double(h) - 0.5;

      double e =
          (1.00 * noise1(1 * nx, 1 * ny) + 0.50 * noise1(2 * nx, 2 * ny) +
           0.25 * noise1(4 * nx, 4 * ny) + 0.13 * noise1(8 * nx, 8 * ny) +
           0.06 * noise1(16 * nx, 16 * ny) + 0.03 * noise1(32 * nx, 32 * ny));
      e /= (1.00 + 0.50 + 0.25 + 0.13 + 0.06 + 0.03);
      e = pow(e, 5.00);

      double m =
          (1.00 * noise2(1 * nx, 1 * ny) + 0.75 * noise2(2 * nx, 2 * ny) +
           0.33 * noise2(4 * nx, 4 * ny) + 0.33 * noise2(8 * nx, 8 * ny) +
           0.33 * noise2(16 * nx, 16 * ny) + 0.50 * noise2(32 * nx, 32 * ny));
      m /= (1.00 + 0.75 + 0.33 + 0.33 + 0.33 + 0.50);

      TERRAIN t = biome(e, m);

      tiles[x + y * w] = {terrain : t};
    }
  }
}

double noise1(double nx, double ny) {
  // Rescale from -1.0:+1.0 to 0.0:1.0
  return gen_elevation.GetValue(nx, ny, 0) / 2.0 + 0.5;
}

double noise2(double nx, double ny) {
  // Rescale from -1.0:+1.0 to 0.0:1.0
  return gen_moisture.GetValue(nx, ny, 0) / 2.0 + 0.5;
}

TERRAIN biome(double e, double m) {
  if (e < 0.02) return OCEAN;
  if (e < 0.03) return BEACH;

  if (e > 0.8) {
    if (m < 0.1) return SCORCHED;
    if (m < 0.2) return BARE;
    if (m < 0.5) return TUNDRA;
    return SNOW;
  }

  if (e > 0.6) {
    if (m < 0.33) return TEMPERATE_DESERT;
    if (m < 0.66) return SHRUBLAND;
    return TAIGA;
  }

  if (e > 0.3) {
    if (m < 0.16) return TEMPERATE_DESERT;
    if (m < 0.50) return GRASSLAND;
    if (m < 0.83) return TEMPERATE_DECIDUOUS_FOREST;
    return TEMPERATE_RAIN_FOREST;
  }

  if (m < 0.16) return SUBTROPICAL_DESERT;
  if (m < 0.33) return GRASSLAND;
  if (m < 0.66) return TROPICAL_SEASONAL_FOREST;
  return TROPICAL_RAIN_FOREST;
}
}
