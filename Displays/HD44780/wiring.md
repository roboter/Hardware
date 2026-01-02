# Wiring — HD44780 character LCD

- Power:
  - VCC: typically 5V. Contrast pin (VO) requires a potentiometer (approx 0–5V) to set contrast.
  - Backlight pins (A/K) may require a series resistor or specified supply depending on module.
- Interface:
  - 4-bit mode: connect D4–D7, RS, E (RW can be tied to GND for write-only usage).
  - 8-bit mode: connect D0–D7, RS, E.
- Notes:
  - Use a potentiometer for VO to set contrast. Some modules include an onboard potentiometer.
  - Initialize the display according to the HD44780 initialization sequence for 4-bit/8-bit modes.
- Safety:
  - Do not exceed backlight current rating; add a series resistor if necessary.

> Note: Refer to `an4032-interfacing-an-hd44780-2line-lcd-display-with-the-stm8svldiscovery-stmicroelectronics.pdf` for examples and wiring diagrams.