# Wiring — DRG STM32H750VBT6 projects

- Power:
  - Many development boards using H750 require 3.3V supply rails; check the project schematics for extra power domains (LCD, camera, SDRAM).
- Camera / DCMI:
  - DCMI pinouts for OV2640 camera are board-specific — check schematics and ensure data lines and clocks are correctly connected.
- Debugging:
  - Use ST-Link or compatible SWD debugger to program and debug projects.
- Safety:
  - Large displays and cameras can draw significant current — ensure a stable power source and proper decoupling.