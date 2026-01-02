# Wiring — GM12864 128x64 graphic display

- Controller: ST7567S (or similar) depending on module variant — check images and labels.
- Power: Many modules support 3.3V logic; some include regulator for 5V — verify before connecting.
- Interface: I2C or SPI variants exist — check module pins and example code.
- Safety: Use level shifting for logic-level mismatches and verify VCC before connecting to a microcontroller.

> Note: Example sketch in this folder demonstrates usage with ESP32 and 3.3V logic.