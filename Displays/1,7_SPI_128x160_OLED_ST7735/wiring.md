# Wiring — ST7735 128x160 SPI display

- Power:
  - Typical module supply: 3.3V to 5V (many modules include an on-board regulator). Verify VCC with a multimeter.
- Pins (common):
  - GND, VCC, SCL (SPI SCK), SDA (SPI MOSI / Data), RST, DC (Data/Command), CS, Backlight.
- Interface:
  - SPI: connect SCK/MOSI/CS and DC/RST lines to MCU SPI pins or bit-banged SPI.
- Safety:
  - Confirm logic level compatibility; use level shifting for 3.3V-only modules when using 5V MCUs.

> Note: See `ST7735.pdf` and pinout image in this folder for reference.