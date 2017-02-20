#ifndef CAMERA_H_
#define CAMERA_H_
#include <cmath>

#include "math.h"
#include "platform.h"

struct Camera {
  Point2D pos;
  Size win_size;
  Size max_size;
  Size map_size;
  s32 tile_size;
  s32 zoom;
  s32 min_zoom;
  s32 max_zoom;
  r32 speed;
};

inline void MoveCameraUp(Camera* cam) {
  cam->pos.y = Clamp(cam->pos.y - cam->speed, 0, cam->max_size.h);
}

inline void MoveCameraDown(Camera* cam) {
  cam->pos.y = Clamp(cam->pos.y + cam->speed, 0, cam->max_size.h);
}

inline void MoveCameraLeft(Camera* cam) {
  cam->pos.x = Clamp(cam->pos.x - cam->speed, 0, cam->max_size.w);
}

inline void MoveCameraRight(Camera* cam) {
  cam->pos.x = Clamp(cam->pos.x + cam->speed, 0, cam->max_size.w);
}

inline s32 ClipCamera(const Camera* cam, s32* width, s32* height) {
  r32 size = ceil(cam->tile_size / cam->zoom);

  s32 map_width = *width;
  s32 map_height = *height;

  // camera tile-based size
  s32 cam_w = Clamp(ceil(cam->win_size.w / size), 0, map_width);
  s32 cam_h = Clamp(ceil(cam->win_size.h / size), 0, map_height);

  // camera tile-based position
  s32 cam_x = Clamp(floor(cam->pos.x / size), 0, map_width - cam_w);
  s32 cam_y = Clamp(floor(cam->pos.y / size), 0, map_height - cam_h);

  *width = cam_w;
  *height = cam_h;

  return cam_x + (cam_y * map_width);
}

static void ChangeCameraZoom(Camera* cam, s32 zoom) {
  s32 old_size = cam->tile_size / cam->zoom;

  cam->zoom = Clamp(zoom, cam->min_zoom, cam->max_zoom);

  s32 mid_x = cam->pos.x + cam->win_size.w / 2;
  s32 mid_y = cam->pos.y + cam->win_size.h / 2;

  s32 new_size = cam->tile_size / cam->zoom;

  s32 new_w = cam->map_size.w * new_size;
  s32 new_h = cam->map_size.h * new_size;

  s32 new_x = (mid_x * new_size / old_size) - cam->win_size.w / 2;
  s32 new_y = (mid_y * new_size / old_size) - cam->win_size.h / 2;

  cam->pos.x = Clamp(new_x, 0, new_w - cam->win_size.w);
  cam->pos.y = Clamp(new_y, 0, new_h - cam->win_size.h);
}

inline void ZoomCameraIn(Camera* cam) { ChangeCameraZoom(cam, cam->zoom - 1); }
inline void ZoomCameraOut(Camera* cam) { ChangeCameraZoom(cam, cam->zoom + 1); }

#endif  // CAMERA_H_
