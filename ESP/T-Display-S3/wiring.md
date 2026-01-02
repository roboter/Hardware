# Wiring — T-Display-S3 (Lilygo)

- Power:
  - Board uses 3.3V logic and a 3.3V supply; do not apply 5V to GPIOs or display lines unless the board has level shifters.
- Display:
  - Integrated ST7789 1.9" TFT (8-bit parallel interface on some variants) — consult `T_Display_S3.pdf` for pinout and configuration.
- Programming:
  - Use USB or external serial/boot mode as described in `readme.md` and `esptool` examples.
- Safety:
  - Verify JST connectors and battery detection pins before connecting external peripherals.

> Note: The board supports Arduino and MicroPython; consult the BSP for exact pin mappings.