# Wiring — Mini STM32F103C8T6

- Power:
  - USB Type-C port can be configured for power or USB/serial depending on populated components; verify jumpers and populated CH340N.
- Boot/Programming:
  - Use BOOT/RST sequence for serial bootloader entries; SWD header is available for debugging.
- Pins:
  - I/O pins are broken out on dual 2.54mm headers; check pin mappings in `readme.md`.
- Safety:
  - Confirm the CC resistor/population options and do not assume USB Type-C cable wiring without checking the board's configuration.