# Wiring — LORAWAN LR1262 Project

- Power:
  - Ensure the module receives proper 3.3V supply (common for LoRa radios and associated MCUs).
- Antenna:
  - Use a matched antenna and verify SMA connector wiring; do not transmit without an antenna attached unless specified.
- Programming:
  - MCU (ATmega328P) programming via ISP; ensure correct voltage levels for the programmer.
- Safety:
  - Follow RF regulations in your region and avoid high-power transmissions without proper licensing.

> Note: See the KiCad schematic and PCB files included in this project folder for precise netlists and connector pinouts.