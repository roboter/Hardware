# Wiring — Nokia 5110 (PCD8544)

- Power:
  - Module typically expects 3.3V VCC (do not apply 5V to logic pins).
  - Use a level shifter when interfacing with 5V microcontrollers.
- Pins (common): RST (Reset), CE (Chip Enable / CS), DC (Data/Command), DIN (MOSI), CLK (SCK), VCC, GND.
- Interface:
  - SPI-like serial interface — can be driven with hardware SPI or bit-banged GPIO.
- Safety:
  - Use 3.3V logic levels or level shifting. Verify contrast settings and backlight supply before enabling them.

> Note: See `5110-Nokia.pdf` and `Nokia5110.pdf` in this folder for datasheet and examples.