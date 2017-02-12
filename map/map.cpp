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

      double e = noise_elevation(nx, ny);
      double m = noise_moisture(nx, ny);

      tiles[x + y * w] = {terrain : GRASS, elevation : e, moisture : m};
    }
  }
}

double noise_elevation(double nx, double ny) {
  // Rescale from -1.0:+1.0 to 0.0:1.0
  return gen_elevation.GetValue(nx, ny, 0) / 2.0 + 0.5;
}

double noise_moisture(double nx, double ny) {
  // Rescale from -1.0:+1.0 to 0.0:1.0
  return gen_moisture.GetValue(nx, ny, 0) / 2.0 + 0.5;
}
}
