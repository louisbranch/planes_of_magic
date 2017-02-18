#include "camera.h"

#include <gtest/gtest.h>

TEST(CameraZoomIn, ReducesCameraSize) {
  camera::Camera cam = {.x = 400,
                        .y = 300,
                        .w = 800,
                        .h = 600,
                        .map_w = 2000,
                        .map_h = 1600,
                        .tile_size = 60,
                        .zoom = 3,
                        .min_zoom = 1,
                        .max_zoom = 3};
  cam.ZoomIn();
  EXPECT_EQ(cam.zoom, 2);
  EXPECT_EQ(cam.x, 800);
  EXPECT_EQ(cam.y, 600);
  cam.ZoomIn();
  EXPECT_EQ(cam.zoom, 1);
  EXPECT_EQ(cam.x, 2000);
  EXPECT_EQ(cam.y, 1500);
  cam.ZoomIn();
  EXPECT_EQ(cam.zoom, 1);
  EXPECT_EQ(cam.x, 2000);
  EXPECT_EQ(cam.y, 1500);
}

TEST(CameraZoomOut, IncreasesCameraSize) {
  camera::Camera cam = {.x = 400,
                        .y = 300,
                        .w = 800,
                        .h = 600,
                        .map_w = 1000,
                        .map_h = 800,
                        .tile_size = 60,
                        .zoom = 1,
                        .min_zoom = 1,
                        .max_zoom = 3};
  cam.ZoomOut();
  EXPECT_EQ(cam.x, 0);
  EXPECT_EQ(cam.y, 0);
  EXPECT_EQ(cam.zoom, 2);
  cam.ZoomOut();
  EXPECT_EQ(cam.zoom, 3);
  EXPECT_EQ(cam.x, 0);
  EXPECT_EQ(cam.y, 0);
  cam.ZoomOut();
  EXPECT_EQ(cam.zoom, 3);
  EXPECT_EQ(cam.x, 0);
  EXPECT_EQ(cam.y, 0);
}
