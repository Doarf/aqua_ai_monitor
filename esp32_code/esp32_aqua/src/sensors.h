#pragma once
#include <DHT.h>

#define DHT_PIN 4
#define DHT_TYPE DHT22
#define TURBIDITY_PIN 35
#define VREF 3.3
#define ADC_RESOLUTION 4095.0

extern float temperature;
extern float humidity;
extern float ntu;
extern DHT dht;

void initSensors();
void readSensors();
float readTurbidity();
String getTurbidityLabel(float n);