# Wiring — CH582F

- CH582F is a BLE MCU from WCH — consult vendor docs for pinout and power specifics.
- Power:
  - Typical boards use 3.3V supply for BLE and peripherals.
  - Avoid supplying 5V directly to I/O pins.
- Programming:
  - Many WCH boards use SWD or a serial-based bootloader. Check repository links for exact programming instructions.
- Safety:
  - Verify Vcc and I/O voltage before connecting external peripherals.

> Note: See the linked WeActStudio repository in `readme.md` for board-specific programming and examples.