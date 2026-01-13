# STM32 Mini V2.0 Wiring and Programming

## Board Features
- **MCU**: STM32F103RCT6 (ARM Cortex-M3, 72MHz)
- **Flash**: 256 KB
- **SRAM**: 48 KB
- **External Flash**: Winbond W25X16 (SPI).
- **USB**: Mini-USB for power and communication.

## Programming and Debugging
- **SWD Header**: Use an ST-Link or similar debugger. Pinout usually: GND, SWCLK, SWDIO, 3V3.
- **Jumpers**: Ensure BOOT jumpers are set for Flash execution (BOOT0=0).

## User LEDs
The LEDs on this board are connected to behave as "Sinks" (Active Low).
- **LED0**: PA8
- **LED1**: PD2

## Resources
- [STM32-base: STM32 Mini V2.0](https://stm32-base.org/boards/STM32F103RCT6-STM32-Mini-V2.0)
- [Board Schematic](schematic.png)
