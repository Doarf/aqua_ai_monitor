#include <Arduino.h>
#include <WiFi.h>
#include "config.h"
#include "camera.h"
#include "streamer.h"

Camera   cam;
Streamer streamer;

void setup() {
  Serial.begin(115200);
  delay(500);
  Serial.println("\n=== ESP32-CAM Stream ===");

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("[WiFi] Connexion");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\n[WiFi] Connecté ✓ IP : " + WiFi.localIP().toString());

  if (!cam.begin()) {
    Serial.println("[CAM] Échec — redémarrage dans 3s");
    delay(3000);
    ESP.restart();
  }
}

void loop() {
  camera_fb_t* fb = cam.capture();
  if (!fb) {
    Serial.println("[CAM] Échec capture");
    delay(100);
    return;
  }
  streamer.send(fb);
  cam.release(fb);
}