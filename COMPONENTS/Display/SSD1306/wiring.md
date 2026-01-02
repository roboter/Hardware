# Wiring — SSD1306 128x64 OLED

- Power:
  - Typical supply: 3.3V or 5V depending on module regulator. Verify module VCC voltage before connecting.
- Pins:
  - GND, VCC, SCL (I2C clock), SDA (I2C data).
  - Some modules expose SPI pins — check silkscreen.
- I2C addresses:
  - Common addresses: 0x3C or 0x3D — check module solder jumper or datasheet.
- Safety:
  - Do not apply >5V to logic pins on 3.3V-only modules. If in doubt, measure VCC with a multimeter before connecting to a microcontroller.

> Note: See the `sch.jpg` in this folder for a simple schematic reference and the NXP library links for example code.