# ESP32 Custom firmware
[WIP]
Custom firmware to easily connect esp32 to wifi nethowrk without settings credentials in code and easily switch between network.

The goal is to setup a connection process, based on global wireless networks hardware:
- if no network connected -> open a web server to configure esp32 -> save credentials in eeprom and fallback to network then closed the local web server.
- if connected to a network -> implement something to reset current configuration.

After that, we can iterate on other custom things on esp32 easily.

## Hardware
Tested on:
- ESP32-S
- ESP-WROOM-32

## Pictures
![ESP32S](https://github.com/OlivierArgentieri/ESP32_Firmware/blob/main/img/ESP32S.jpg)

![ESP-WROOM-32-oled](https://github.com/OlivierArgentieri/ESP32_Firmware/blob/main/img/ESP-WROOM-32-oled.jpg)

## Actual Size
Sketch uses 760349 bytes (58%) of program storage space. Maximum is 1310720 bytes.
Global variables use 43136 bytes (13%) of dynamic memory, leaving 284544 bytes for local variables. Maximum is 327680 bytes.
