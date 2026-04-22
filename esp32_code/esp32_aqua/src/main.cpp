#include <Arduino.h>
#include <WiFi.h>
#include "config.h"
#include "dht_sensor.h"
#include "ph_sensor.h"
#include "turbidity_sensor.h"
#include "screen_oled.h"
#include "http_sender.h"

// ── WiFi ──────────────────────────────────
#define WIFI_SSID     "Arthur"
#define WIFI_PASSWORD "mister95570"

DHTSensor       dhtSensor;
PHSensor        phSensor;
TurbiditySensor turbSensor;
ScreenOLED      screen;
HttpSender      sender;

SensorData lastData;
float      lastPh  = 7.0f;
float      lastNtu = 0.0f;

void setup() {
  Serial.begin(115200);
  Serial.println("\n=== SPI Aquaculture ===");

  // Connexion WiFi
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("[WiFi] Connexion");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\n[WiFi] Connecté ✓ IP : " + WiFi.localIP().toString());

  if (!screen.begin())
    Serial.println("[OLED] Écran KO !");
  screen.showSplash();

  dhtSensor.begin();
  phSensor.begin();
  turbSensor.begin();
  sender.begin();
}

void loop() {
  if (dhtSensor.isReady())
    lastData = dhtSensor.read();

  if (phSensor.isReady())
    lastPh = phSensor.read();

  if (turbSensor.isReady())
    lastNtu = turbSensor.read();

  if (lastData.valid) {
    screen.showData(lastData, lastPh, lastNtu);
    if (sender.isReady())
      sender.send(lastData, lastPh, lastNtu);
  } else {
    screen.showError("DHT22 KO");
  }
}