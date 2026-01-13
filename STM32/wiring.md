# STM32 Wiring and Programming

This guide provides a central entry point for STM32 documentation in this repository.

## Programming Interfaces

### ST-Link (Standard)
Most STM32 boards use the **SWD (Serial Wire Debug)** interface:
- **SWDIO**: Data
- **SWCLK**: Clock
- **GND**: Ground
- **3V3**: Power (Target)

### Boot Modes
STM32 chips use **BOOT0** and **BOOT1** pins to determine where to boot from:
- **Flash (Default)**: BOOT0 = 0
- **System Memory (Bootloader)**: BOOT0 = 1, BOOT1 = 0
- **SRAM**: BOOT0 = 1, BOOT1 = 1

### DFU (USB Programming)
Many modern STM32s support DFU mode directly over USB. Hold the **BOOT0** button while plugging in the USB cable.

## Subfolder Documentation
For specific board details, refer to the `wiring.md` in each subfolder:
- [BluePill/wiring.md](BluePill/wiring.md)
- [BlackPill/wiring.md](BlackPill/wiring.md)
- [WeAct Black Pill V3.0/wiring.md](WeAct Black Pill V3.0/wiring.md)
- [maple mini clone/wiring.md](maple mini clone/wiring.md)
- [NUCLEO-F303K8/wiring.md](NUCLEO-F303K8/wiring.md)
- [STM32F429-Discovery/wiring.md](STM32F429-Discovery/wiring.md)
- ...and others.
