#pragma once
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32

extern Adafruit_SSD1306 display;
extern int currentMenu;
extern const int totalMenus;

void initDisplay();
void showMenu(int menu);