# Wiring — STM32F746G Discovery

- Power:
  - Usually USB-powered; ensure the 3.3V regulator is used for external peripherals where required.
- Display:
  - Board includes LTDC display controller — consult board documentation for parallel connector pinouts and display power requirements.
- Debugging:
  - Use on-board ST-Link or external SWD (SWDIO/SWCLK) connector for programming and debugging.
- Peripherals:
  - When connecting touch panels or camera interfaces, verify signal voltage levels and connector pinouts.
- Safety:
  - The display and related circuits can draw significant current — ensure your supply can handle peak loads.