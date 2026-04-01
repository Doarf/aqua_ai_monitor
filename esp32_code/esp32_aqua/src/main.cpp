#include <Arduino.h>
#include "display.h"
#include "sensors.h"

#define BUTTON_PIN 15

unsigned long lastPress = 0;
unsigned long lastRead = 0;
const unsigned long debounce = 200;
const unsigned long readInterval = 2000;

void setup() {
  Serial.begin(115200);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  initSensors();
  initDisplay();
  readSensors();
  showMenu(currentMenu);
}

void loop() {
  unsigned long now = millis();

  if (now - lastRead >= readInterval) {
    lastRead = now;
    readSensors();

    Serial.println("--------------------");
    Serial.printf("Temperature : %.1f C\n", temperature);
    Serial.printf("Humidite    : %.1f %%\n", humidity);
    Serial.printf("Turbidite   : %.0f NTU (%s)\n", ntu, getTurbidityLabel(ntu).c_str());
    Serial.printf("Uptime      : %lu s\n", now / 1000);

    showMenu(currentMenu);
  }

  if (digitalRead(BUTTON_PIN) == LOW) {
    if (now - lastPress > debounce) {
      lastPress = now;
      currentMenu = (currentMenu + 1) % totalMenus;
      showMenu(currentMenu);
    }
  }
}