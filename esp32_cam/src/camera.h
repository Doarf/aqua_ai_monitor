#pragma once
#include <Arduino.h>
#include "esp_camera.h"
#include "config.h"

class Camera {
public:
  Camera();
  bool         begin();
  camera_fb_t* capture();
  void         release(camera_fb_t* fb);
};