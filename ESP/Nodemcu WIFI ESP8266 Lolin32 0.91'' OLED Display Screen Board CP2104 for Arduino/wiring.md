# TTGO/Heltec ESP8266 with 0.91" OLED Wiring

This board is an ESP8266-based development board with an integrated 0.91" OLED (SSD1306).

## Board Features
- **MCU**: ESP8266 (typically ESP-12E/F module)
- **Display**: 0.91" OLED (128x32, SSD1306)
- **USB-to-Serial**: CP2104 or similar.
- **Power**: 5V via Micro-USB or Vin.

## Programming
- **IDE**: Arduino IDE.
- **Board Selection**: `NodeMCU 1.0 (ESP-12E Module)`.
- **Note**: Some versions may require the `TTGO-WIFI-OLED` hardware definition.

## OLED Wiring (Internal I2C)
- **SDA**: GPIO4 (D2)
- **SCL**: GPIO5 (D1)
- **Address**: 0x3c
- **Reset**: Some versions use a reset pin for the OLED; check your code if it fails to initialize.

## On-board Peripherals
- **User LED**: Typically GPIO2 (Blue LED on module) or GPIO16.

## Pinout
Refer to the images in this folder for visual identification:
- [Board Front](513majnYp8L._SL1000_.jpg)
- [Alternative View](TTGO-ESP8266-0-91-inch-OLED-for-arduino-nodemcu-4.jpg)
