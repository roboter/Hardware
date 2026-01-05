# TTGO TS V1.0 Wiring and Programming

The TTGO TS V1.0 is a feature-rich ESP32 board with a display, speaker, and SD card slot.

## Board Features
- **MCU**: ESP32 (Dual-core, 240MHz)
- **Display**: 1.44" TFT LCD (SPI)
- **Audio**: Speaker connector and amplifier.
- **Storage**: MicroSD Card Slot (SPI).
- **Power**: Battery charger integrated (typically features a JST connector for LiPo).
- **USB-to-Serial**: CP210X.

## Programming
- **Interface**: Micro-USB port.
- **Drivers**: Silicon Labs CP210X VCP drivers.
- **Board Selection**: `ESP32 Dev Module`.

## On-board Peripherals
- **TFT Display (SPI)**:
    - CS: GPIO16
    - SCL: GPIO5
    - SDA: GPIO18
    - RES: GPIO9
    - DC: GPIO17
    - BL: GPIO27
- **MicroSD Card (SPI)**:
    - CS: GPIO13
    - MOSI: GPIO15
    - MISO: GPIO2
    - SCK: GPIO14
- **Speaker**: Connected to an on-board amplifier (check specific code for pin).
- **MPU9250**: Note that **V1.0** typically does **NOT** include the MPU9250 IMU.

## Links
- [TTGO-TS-V1.2 GitHub (Reference)](https://github.com/LilyGO/TTGO-TS-V1.2)
- [Introduction Video](https://www.youtube.com/watch?v=s12XuR7BJkw)
