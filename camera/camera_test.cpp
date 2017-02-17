#include "camera.h"

#include <gtest/gtest.h>

TEST(CameraZoomIn, ReducesCameraSize) {
  auto cam = new camera::Camera();
  cam->ZoomIn();
  EXPECT_EQ(cam->w, 1024);
  EXPECT_EQ(cam->h, 768);
}
