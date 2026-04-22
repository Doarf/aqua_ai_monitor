#pragma once
#include <DHT.h>
#include "config.h"

struct SensorData {
  float temperature;
  float humidity;
  bool  valid;
};

class DHTSensor {
public:
  DHTSensor();
  void       begin();
  SensorData read();
  bool       isReady();
private:
  DHT           _dht;
  unsigned long _lastReadTime;
};