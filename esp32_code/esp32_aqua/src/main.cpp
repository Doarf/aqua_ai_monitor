#include <Arduino.h>
#include "config.h"
#include "dht_sensor.h"
#include "ph_sensor.h"
#include "screen_oled.h"

DHTSensor  dhtSensor;
PHSensor   phSensor;
ScreenOLED screen;

SensorData lastData;
float      lastPh = 7.0f;

void setup() {
  Serial.begin(9600);
  Serial.println("\n=== SPI Aquaculture ===");

  if (!screen.begin())
    Serial.println("[OLED] Écran KO !");
  screen.showSplash();

  dhtSensor.begin();
  phSensor.begin();
}

void loop() {
  if (dhtSensor.isReady())
    lastData = dhtSensor.read();

  if (phSensor.isReady())
    lastPh = phSensor.read();

  if (lastData.valid)
    screen.showData(lastData, lastPh);
  else
    screen.showError("DHT22 KO");
}