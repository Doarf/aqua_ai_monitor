#include "display.h"
#include "sensors.h"
#include <Arduino.h>

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
int currentMenu = 0;
const int totalMenus = 4;

void initDisplay() {
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("Écran non trouvé !");
    while (true);
  }
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(20, 12);
  display.println("Demarrage...");
  display.display();
  delay(2000);
}

void showMenu(int menu) {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);

  switch (menu) {
    case 0:
      display.setCursor(0, 0);
      display.println("=== TEMPERATURE ===");
      display.setTextSize(2);
      display.setCursor(10, 14);
      if (isnan(temperature)) display.println("Erreur");
      else display.printf("%.1f C", temperature);
      break;

    case 1:
      display.setCursor(0, 0);
      display.println("==== HUMIDITE ====");
      display.setTextSize(2);
      display.setCursor(10, 14);
      if (isnan(humidity)) display.println("Erreur");
      else display.printf("%.1f %%", humidity);
      break;

    case 2:
      display.setCursor(0, 0);
      display.println("==== TURBIDITE ===");
      display.setTextSize(1);
      display.setCursor(0, 12);
      display.printf("%.0f NTU\n", ntu);
      display.println(getTurbidityLabel(ntu));
      break;

    case 3:
      display.setCursor(0, 0);
      display.println("===== RESUME =====");
      display.setTextSize(1);
      display.setCursor(0, 10);
      display.printf("Temp : %.1f C\n", temperature);
      display.printf("Humi : %.1f %%\n", humidity);
      display.printf("Turb : %.0f NTU", ntu);
      break;
  }

  display.setTextSize(1);
  display.setCursor(100, 24);
  display.printf("%d/%d", currentMenu + 1, totalMenus);
  display.display();
}