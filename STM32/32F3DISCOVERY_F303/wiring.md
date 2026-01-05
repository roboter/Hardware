# Wiring — STM32F3 Discovery (F303)

- Power:
  - Board typically powered via USB (5V) which is regulated on board to required rails; many discoveries use 3.3V for MCU and peripherals.
- Clock:
  - Note: this board may not have external crystals soldered (as noted in the readme) — rely on internal oscillators or solder the crystal if required by your project.
- Debugging/Programming:
  - Use SWD/SWDIO (CNx headers) or the on-board ST-Link (if present) to flash and debug.
  - Ensure the target board is powered when connecting a debugger and that grounds are common.
- Peripherals:
  - Check the discovery board pins for accelerometer, audio, and other sensors — follow their datasheets for wiring.
- Safety:
  - Verify voltage rails with a multimeter before connecting external sensors; avoid hot-plugging sensitive interfaces.

> Note: See official ST documentation for exact header pinouts and CNx connector descriptions.