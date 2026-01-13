# Modules Wiring and Programming

This directory contains a wide variety of electronic breakout modules.

## Common Module Types

### Serial Adapters (USB-to-UART)
- **CP2102 / CH340**: Standard 3.3V/5V serial bridges.
- **Wiring**: TX -> RX, RX -> TX, GND -> GND.

### RTC Modules (Real Time Clock)
- **DS3231 / DS1307**: High-precision clocks via I2C (Address 0x68).

### Communication Modules
- **NRF24L01**: 2.4GHz RF via SPI.
- **CC1101**: Sub-1GHz RF via SPI.

### Power & Battery
- **TP4056**: Li-Ion charging.
- **BMS Modules**: Protection for multi-cell packs.

## Navigation
Each module typically has its own folder with specific datasheets and notes.
Refer to the [Modules/readme.md](readme.md) for a full list and images.
