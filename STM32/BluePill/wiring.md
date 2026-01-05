# Wiring — Blue Pill (STM32F103C8T6)

- Power:
  - Board typically runs at 3.3V. The USB-serial regulator or external 5V/VIN must be used with caution.
- Debugging:
  - Use SWD header (SWCLK/SWDIO) with ST-Link for reliable programming.
- Bootloader:
  - To use the built-in serial bootloader, set BOOT0 high at reset and use the MCU UART pins for upload.
- Pins:
  - Check `bluepill-pinout.gif` in the folder for pin mappings (PAx/PBx/PCx).
- Safety:
  - Do not apply 5V to 3.3V I/O pins; use level shifters for 5V peripherals.