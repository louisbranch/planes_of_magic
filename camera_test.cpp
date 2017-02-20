#include "camera.h"

#include <gtest/gtest.h>

TEST(CameraZoomIn, ReducesCameraSize) {
  Camera cam = {.pos.x = 800,
                .pos.y = 600,
                .win_size.w = 1024,
                .win_size.h = 768,
                .map_size.w = 16000,
                .map_size.h = 9000,
                .tile_size = 50,
                .zoom = 3,
                .min_zoom = 1,
                .max_zoom = 3};

  ZoomCameraIn(&cam);
  EXPECT_EQ(cam.zoom, 2);
  EXPECT_EQ(cam.pos.x, 1538);
  EXPECT_EQ(cam.pos.y, 1153);
  ZoomCameraIn(&cam);
  EXPECT_EQ(cam.zoom, 1);
  EXPECT_EQ(cam.pos.x, 3588);
  EXPECT_EQ(cam.pos.y, 2690);
  ZoomCameraIn(&cam);
  EXPECT_EQ(cam.zoom, 1);
  EXPECT_EQ(cam.pos.x, 3588);
  EXPECT_EQ(cam.pos.y, 2690);
}

TEST(CameraZoomOut, IncreasesCameraSize) {
  Camera cam = {.pos.x = 3588,
                .pos.y = 2690,
                .win_size.w = 1024,
                .win_size.h = 768,
                .map_size.w = 16000,
                .map_size.h = 9000,
                .tile_size = 50,
                .zoom = 1,
                .min_zoom = 1,
                .max_zoom = 3};

  ZoomCameraOut(&cam);
  EXPECT_EQ(cam.zoom, 2);
  EXPECT_EQ(cam.pos.x, 1538);
  EXPECT_EQ(cam.pos.y, 1153);
  ZoomCameraOut(&cam);
  EXPECT_EQ(cam.zoom, 3);
  EXPECT_EQ(cam.pos.x, 800);
  EXPECT_EQ(cam.pos.y, 599);
  ZoomCameraOut(&cam);
  EXPECT_EQ(cam.zoom, 3);
  EXPECT_EQ(cam.pos.x, 800);
  EXPECT_EQ(cam.pos.y, 599);
}
