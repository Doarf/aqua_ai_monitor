#pragma once
#include <Arduino.h>
#include <WiFiClient.h>
#include "esp_camera.h"
#include "config.h"

class Streamer {
public:
  Streamer();
  bool send(camera_fb_t* fb);

private:
  WiFiClient _client;
  bool       _connect();
};