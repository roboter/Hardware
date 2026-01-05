# Wiring — Raspberry RP2040 boards

- Power:
  - RP2040 boards typically use 3.3V logic; ensure you power them with a 3.3V regulator or USB.
- Bootloader & Programming:
  - Some boards use UF2 bootloader for drag-and-drop programming; others can be programmed via SWD or USB serial.
- Pins:
  - Use PIO and GPIO according to RP2040 pin mappings; check board-specific schematics for exact pinouts.
- Safety:
  - Observe power and IO voltage limits; use level shifting when interfacing with 5V peripherals.

> Note: See each board's README and schematics for full wiring details.