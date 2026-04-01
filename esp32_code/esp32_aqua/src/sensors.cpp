#include "sensors.h"
#include <Arduino.h>

float temperature = 0;
float humidity = 0;
float ntu = 0;

DHT dht(DHT_PIN, DHT_TYPE);

void initSensors() {
  dht.begin();
}

float readTurbidity() {
  int samples = 10;
  float sum = 0;
  for (int i = 0; i < samples; i++) {
    sum += analogRead(TURBIDITY_PIN);
    delay(10);
  }
  float avgADC = sum / samples;
  float voltage = (avgADC / ADC_RESOLUTION) * VREF;

  Serial.printf("ADC : %.0f | Tension : %.3f V\n", avgADC, voltage);

  float ntuVal;
  if (voltage < 1.0) {
    ntuVal = 4550;
  } else {
    ntuVal = -1120.4 * voltage * voltage + 5742.3 * voltage - 4352.9;
  }
  if (ntuVal < 0) ntuVal = 0;
  return ntuVal;
}

String getTurbidityLabel(float n) {
  if (n < 10)  return "Limpide";
  if (n < 100) return "Claire";
  if (n < 500) return "Trouble";
  return "Tres trouble";
}

void readSensors() {
  float t = dht.readTemperature();
  float h = dht.readHumidity();
  if (!isnan(t)) temperature = t;
  if (!isnan(h)) humidity = h;
  ntu = readTurbidity();
}