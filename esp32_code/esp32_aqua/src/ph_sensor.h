#pragma once
#include <Arduino.h>
#include "config.h"

class PHSensor {
public:
  PHSensor();
  void  begin();
  float read();          // retourne la valeur pH
  bool  isReady();

private:
  unsigned long _lastReadTime;
  float _voltageToPhValue(float voltage);
};