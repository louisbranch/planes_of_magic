#ifndef map_H_
#define map_H_

#include "platform.h"

#include <stdlib.h>
#include <time.h>
#include <cmath>

#include <noise/module/perlin.h>

noise::module::Perlin gen_elevation;
noise::module::Perlin gen_moisture;

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

struct Tile {
  TERRAIN terrain;
};

struct Map {
  Size size;
  Tile* tiles;
};

static inline r32 noise1(r32 nx, r32 ny) {
  // Rescale from -1.0:+1.0 to 0.0:1.0
  return gen_elevation.GetValue(nx, ny, 0) / 2.0 + 0.5;
}

static inline r32 noise2(r32 nx, r32 ny) {
  // Rescale from -1.0:+1.0 to 0.0:1.0
  return gen_moisture.GetValue(nx, ny, 0) / 2.0 + 0.5;
}

inline TERRAIN biome(r32 e, r32 m) {
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

inline void BuildMap(Map* map) {
  s32 size = map->size.w * map->size.h;
  map->tiles = new Tile[size];

  srand(time(NULL));

  gen_elevation.SetSeed(rand());
  gen_moisture.SetSeed(rand());

  for (int y = 0; y < map->size.h; y++) {
    for (int x = 0; x < map->size.w; x++) {
      r32 nx = x / r32(map->size.w) - 0.5;
      r32 ny = y / r32(map->size.h) - 0.5;

      r32 e =
          (1.00 * noise1(1 * nx, 1 * ny) + 0.50 * noise1(2 * nx, 2 * ny) +
           0.25 * noise1(4 * nx, 4 * ny) + 0.13 * noise1(8 * nx, 8 * ny) +
           0.06 * noise1(16 * nx, 16 * ny) + 0.03 * noise1(32 * nx, 32 * ny));
      e /= (1.00 + 0.50 + 0.25 + 0.13 + 0.06 + 0.03);
      e = pow(e, 5.00);

      r32 m =
          (1.00 * noise2(1 * nx, 1 * ny) + 0.75 * noise2(2 * nx, 2 * ny) +
           0.33 * noise2(4 * nx, 4 * ny) + 0.33 * noise2(8 * nx, 8 * ny) +
           0.33 * noise2(16 * nx, 16 * ny) + 0.50 * noise2(32 * nx, 32 * ny));
      m /= (1.00 + 0.75 + 0.33 + 0.33 + 0.33 + 0.50);

      TERRAIN t = biome(e, m);

      Tile tile = {.terrain = t};

      map->tiles[x + y * map->size.w] = tile;
    }
  }
}

#endif  // map_H_
