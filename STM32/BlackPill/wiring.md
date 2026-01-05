# Wiring — BlackPill (STM32F1/F4 variants)

- Power:
  - Many BlackPill boards use 3.3V MCU voltage. Some have a 5V USB supply with a regulator — check board options.
- Boot and Boot0:
  - To enter the built-in bootloader, BOOT0 must be pulled high at reset on many STM32F1 devices.
- Debugging:
  - Use SWD (SWCLK/SWDIO) header for programming with ST-Link or other debuggers.
- Pins:
  - Check the exact MCU variant for available pins; many break out standard Arduino-style headers for convenience.
- Safety:
  - Verify Vcc/GND and avoid applying 5V to 3.3V-only I/O.