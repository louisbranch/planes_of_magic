#include "camera.h"

#include <math.h>

#include "../math/math.h"

namespace camera {
void Camera::MoveUp() { y = math::Clamp(y - speed, 0, max_h); }
void Camera::MoveDown() { y = math::Clamp(y + speed, 0, max_h); }
void Camera::MoveLeft() { x = math::Clamp(x - speed, 0, max_w); }
void Camera::MoveRight() { x = math::Clamp(x + speed, 0, max_w); }
void Camera::ZoomIn() { zoom = math::Clamp(zoom - 1, min_zoom, max_zoom); }
void Camera::ZoomOut() { zoom = math::Clamp(zoom + 1, min_zoom, max_zoom); }

int Camera::Clip(int* width, int* height) {
  int size = ceil(tile_size / zoom);

  // camera tile-based size
  *width = math::Clamp(ceil(w / size), 0, *width);
  *height = math::Clamp(ceil(h / size), 0, *height);

  // camera tile-based position
  int x = math::Clamp(floor(x / size), 0, *width - w);
  int y = math::Clamp(floor(y / size), 0, *height - h);

  return x + (y * *width);
}
}
