#include "WMOLED.h"
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width,  in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels

void WMOLED::Setup()
{
  display = new Adafruit_SSD1306(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
  if (!display->begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    //LOG_WARNING("SSD1306 allocation failed");
    Serial.println("SSD1306 allocation failed");
    return;
  }
}

void WMOLED::DisplayMessage(const String& message) const
{
  if (!display)
    return;

  display->clearDisplay();
  display->setTextSize(1);
  display->setTextColor(WHITE);
  display->setCursor(0, 10);
  display->println(message);
  display->display();
}