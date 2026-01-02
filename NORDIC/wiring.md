# Wiring — Nordic nRF52 series boards

- Power:
  - nRF52 series expects 3.3V supply; do not apply 5V to I/O pins.
- Programming & Debugging:
  - Use SWD (SWDIO, SWCLK) to program and debug; tools include nrfjprog and Segger J-Link.
- Notes:
  - Check UICR APPROTECT and other fuses — some boards may have read-protection/encryption enabled.
- Safety:
  - Use proper decoupling capacitors and avoid hot-plugging sensitive RF front-ends.

> Note: See `nRF52810/` and `nRF52833/` subfolders for board-specific resources.