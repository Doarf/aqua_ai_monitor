#include "dht_sensor.h"
#include <Arduino.h>

DHTSensor::DHTSensor()
  : _dht(DHTPIN, DHTTYPE), _lastReadTime(0) {}

void DHTSensor::begin() {
  _dht.begin();
  Serial.println("[DHT22] Init GPIO " + String(DHTPIN));
}

SensorData DHTSensor::read() {
  SensorData data;
  data.temperature = _dht.readTemperature();
  data.humidity    = _dht.readHumidity();
  data.valid       = !isnan(data.temperature) && !isnan(data.humidity);
  _lastReadTime    = millis();

  if (data.valid)
    Serial.printf("[DHT22] Temp: %.1f °C | Hum: %.1f %%\n", data.temperature, data.humidity);
  else
    Serial.println("[DHT22] Erreur lecture !");

  return data;
}

bool DHTSensor::isReady() {
  return (millis() - _lastReadTime) >= DHT_READ_INTERVAL_MS;
}