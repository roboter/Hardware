# Wiring — NUCLEO-F303K8

- Power:
  - USB provides 5V which is regulated to 3.3V for MCU and peripherals.
- Crystal:
  - Some Nucleo boards may have unpopulated crystal footprints (see `readme.md`).
- Debugging:
  - Use the on-board ST-Link or SWD headers for programming.
- Safety:
  - Confirm which Arduino header pins are 5V-tolerant before connecting 5V peripherals.

> Note: Check the board's schematic for detailed pin mappings and jumper configurations.