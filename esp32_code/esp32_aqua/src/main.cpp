#include <Arduino.h>
#include "config.h"
#include "dht_sensor.h"
#include "screen_oled.h"

DHTSensor  dhtSensor;
ScreenOLED screen;

void setup() {
  Serial.begin(115200);
  if (!screen.begin())
    Serial.println("Écran KO, vérifiez le câblage.");
  screen.showSplash();
  dhtSensor.begin();
}

void loop() {
  if (dhtSensor.isReady()) {
    SensorData data = dhtSensor.read();
    if (data.valid)
      screen.showData(data);
    else
      screen.showError("DHT22 KO");
  }
}