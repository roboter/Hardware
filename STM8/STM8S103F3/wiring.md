# Wiring — STM8S103F3 breakout board

- Power:
  - Many STM8 boards are powered via USB; ensure the regulator provides 3.3V to the MCU.
  - When using ST-Link, the target board should be powered by USB (see note in `readme.md`).
- Programming:
  - STM8 uses SWIM for single-wire in-circuit debugging; some boards expose JTAG connectors for hardware debug.
  - Use ST-Link or dedicated STM8 programmers and ensure proper target voltage detection.
- Peripherals:
  - I2C/TWI pins and SPI pins are broken out; observe correct pull-ups and voltage levels.
- Safety:
  - Verify Vcc before connecting external sensors and avoid hot-plugging devices that draw large currents.

> Note: See datasheets and the included examples for wiring diagrams and recommended decoupling.