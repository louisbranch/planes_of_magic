#include "camera.h"

#include <gtest/gtest.h>

TEST(CameraZoomIn, ReducesCameraSize) {
  camera::Camera cam = {.x = 800,
                        .y = 600,
                        .w = 1024,
                        .h = 768,
                        .map_w = 16000,
                        .map_h = 9000,
                        .tile_size = 50,
                        .zoom = 3,
                        .min_zoom = 1,
                        .max_zoom = 3};

  cam.ZoomIn();
  EXPECT_EQ(cam.zoom, 2);
  EXPECT_EQ(cam.x, 1538);
  EXPECT_EQ(cam.y, 1153);
  cam.ZoomIn();
  EXPECT_EQ(cam.zoom, 1);
  EXPECT_EQ(cam.x, 3588);
  EXPECT_EQ(cam.y, 2690);
  cam.ZoomIn();
  EXPECT_EQ(cam.zoom, 1);
  EXPECT_EQ(cam.x, 3588);
  EXPECT_EQ(cam.y, 2690);
}

TEST(CameraZoomOut, IncreasesCameraSize) {
  camera::Camera cam = {.x = 3588,
                        .y = 2690,
                        .w = 1024,
                        .h = 768,
                        .map_w = 16000,
                        .map_h = 9000,
                        .tile_size = 50,
                        .zoom = 1,
                        .min_zoom = 1,
                        .max_zoom = 3};

  cam.ZoomOut();
  EXPECT_EQ(cam.zoom, 2);
  EXPECT_EQ(cam.x, 1538);
  EXPECT_EQ(cam.y, 1153);
  cam.ZoomOut();
  EXPECT_EQ(cam.zoom, 3);
  EXPECT_EQ(cam.x, 800);
  EXPECT_EQ(cam.y, 599);
  cam.ZoomOut();
  EXPECT_EQ(cam.zoom, 3);
  EXPECT_EQ(cam.x, 800);
  EXPECT_EQ(cam.y, 599);
}
