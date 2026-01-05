# Wiring — CH32V003 Signal Generator (Si5351 + SSD1306)

- Power:
  - Ensure 3.3V supply for CH32V003 and peripherals; some Si5351 modules may expect 5V (use level shifting or 3.3V regulator where necessary).
- I2C:
  - Si5351 and SSD1306 typically use I2C (SDA/SCL) — connect to MCU I2C pins and ensure pull-up resistors are present.
- Display:
  - SSD1306 128x64 connections (VCC, GND, SCL, SDA) — verify voltage and address (0x3C/0x3D).
- Safety:
  - Use current-limited bench power when testing unknown builds.

> Note: See `documentation/` and `source/` for wiring examples and driver code.