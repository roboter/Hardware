# Wiring — Arduino Nano v3

- Power:
  - USB Micro provides 5V (typically fused to ~500mA). VIN accepts 6–9V (up to 12V peak).
  - On-board regulator provides regulated 5V output.
- Logic level: 5V (CH340 USB-TTL).
- Pins:
  - Standard Arduino Nano pinout; extra analog pins A6/A7 available on some boards.
- Programming:
  - Uses CH340 USB-UART converter for uploading via bootloader.
- Safety:
  - Do not supply VIN and USB at the same time from conflicting power sources.
  - Verify the board's regulator and fuse if using high current loads.

> Note: See `official-arduino-schematics.pdf` in this folder for reference.