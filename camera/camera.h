#ifndef CAMERA_H_
#define CAMERA_H_

namespace camera {
class Camera {
 public:
  int x;
  int y;
  int w;
  int h;
  int max_w;
  int max_h;
  int zoom;
  int min_zoom;
  int max_zoom;
  int speed;
  int tile_size;

  void MoveUp();
  void MoveDown();
  void MoveLeft();
  void MoveRight();
  void ZoomIn();
  void ZoomOut();

  int Clip(int* width, int* height);
};
}

#endif  // CAMERA_H_
