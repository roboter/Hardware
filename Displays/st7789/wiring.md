# Wiring — ST7789 SPI TFT

- Power:
  - Typically 3.3V logic; many modules include a regulator for 5V.
- Pins:
  - GND, VCC, SCL (SCK), SDA (MOSI / Data), RESET, DC, CS, BACKLIGHT.
- Interface:
  - SPI — connect to MCU SPI pins or bit-banged SPI.
- Safety:
  - Ensure 3.3V logic or use level shifting when interfacing with 5V MCUs. Avoid applying >3.3V to 3.3V-only pins.

> Note: Use vendor/example libraries for initialization sequences and rotation handling.