# ESP (ESP32 / ESP8266) Wiring and Programming

This guide provides general notes for the ESP family of microcontrollers available in this directory.

## Common Programming Methods
- **USB-to-Serial**: Most dev boards include an on-board CP210x or CH340 bridge.
- **Bootloader Mode**: 
    - Hold **BOOT (GPIO0)** button.
    - Press **RESET (EN)** button.
    - Release **BOOT**.
- **Auto-Reset**: Modern boards (NodeMCU, DevKitV1, Wemos) typically handle this automatically via DTR/RTS signals.

## Power Requirements
- **Voltage**: ESP modules operate at **3.3V**. 
- **Current**: ESP chips are power-hungry (up to 500mA during WiFi bursts). Ensure your power source (especially USB-to-serial adapters) can provide enough current.
- **5V Input**: Only connect to 5V if the board has an integrated voltage regulator (most dev boards do).

## Pinout Overview
- **ESP8266 (ESP-12E)**:
    - GPIO0: Boot Mode
    - GPIO2: Internal LED (Blue)
    - GPIO15: Must be Pulled Low for run mode
- **ESP32**:
    - GPIO0: Boot Mode
    - GPIO2: Internal LED
    - GPIO5/18/19/23: Standard SPI (VSPI)

For specific board pinouts, refer to the `wiring.md` in individual subfolders:
- [T-Display-S3/wiring.md](T-Display-S3/wiring.md)
- [Wemos-32-With-OLED/wiring.md](Wemos-32-With-OLED/wiring.md)
- [ESP32TTGO-OLED-18650/wiring.md](ESP32TTGO-OLED-18650/wiring.md)
- ...and many others.
