#include "ph_sensor.h"

PHSensor::PHSensor() : _lastReadTime(0) {}

void PHSensor::begin() {
  analogReadResolution(12);        // 12 bits → 0-4095
  analogSetAttenuation(ADC_11db); // plage 0-3.3V
  Serial.println("[pH] Capteur initialisé sur GPIO " + String(PH_PIN));
}

float PHSensor::read() {
  // Moyenne sur PH_SAMPLES lectures
  long sum = 0;
  for (int i = 0; i < PH_SAMPLES; i++) {
    sum += analogRead(PH_PIN);
    delay(10);
  }
  float raw     = sum / (float)PH_SAMPLES;
  float voltage = (raw / 4095.0f) * PH_VREF;
  float ph      = _voltageToPhValue(voltage);

  _lastReadTime = millis();
  Serial.printf("[pH] Raw: %.0f | Voltage: %.3fV | pH: %.2f\n", raw, voltage, ph);
  return ph;
}

bool PHSensor::isReady() {
  return (millis() - _lastReadTime) >= PH_READ_INTERVAL_MS;
}

// Conversion tension → pH (linéaire, à affiner avec calibration)
// pH neutre (7.0) ≈ 1.65V pour le PH-4502C alimenté en 3.3V
float PHSensor::_voltageToPhValue(float voltage) {
  // Courbe inversée + calibration 2 points
  // V=0.781 → pH=9.18  |  V=1.388 → pH=4.0
  float ph = 9.18f + (0.781f - voltage) * 8.5f + PH_OFFSET;
  return constrain(ph, 0.0f, 14.0f);
}