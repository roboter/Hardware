# Wiring — Wemos-32 with OLED

- Power:
  - ESP32 boards use 3.3V logic — ensure the board is powered with 3.3V supply or USB that provides 5V regulated to 3.3V on the board.
- OLED I2C pins:
  - SDA: pin 5
  - SCL: pin 4
  - I2C address: commonly 0x3C
- Libraries:
  - Use `SSD1306Wire` or compatible library; initialize with `SSD1306 display(0x3c, 5, 4);` as noted in `readme.md`.
- Safety:
  - Verify the board's I2C pin wiring and do not exceed 3.3V on these pins.

> Note: Check folder `ESP32_Wemos_with_display/` for example projects.