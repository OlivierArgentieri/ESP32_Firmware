#include "WMOLED.h"

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

void WMOLED::Setup()
{
  //Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, OLED_MOSI, OLED_CLK, OLED_DC, OLED_RESET, OLED_CS);
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    //LOG_WARNING("SSD1306 allocation failed");
    Serial.Print("SSD1306 allocation failed")
    return;
  }

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 28);
  display.println("Hello world!");
}