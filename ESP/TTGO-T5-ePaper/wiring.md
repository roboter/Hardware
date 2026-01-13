# TTGO T5 ePaper Wiring and Programming

The TTGO T5 series features an ESP32 combined with an e-Paper display (various sizes, typically 1.54", 2.13", or 2.7").

## Board Features
- **MCU**: ESP32-D0WDQ6 (Dual-core, 240MHz)
- **Display**: 2.7" e-Ink (264x176 resolution) or other variants.
- **Interfaces**: SPI for display, I2C, UART.
- **On-board**: Speaker/Buzzer connector, SD Card slot (depending on version).

## Programming
- **Interface**: Integrated Micro-USB or USB-C port.
- **IDE**: Arduino IDE or PlatformIO.
- **Board Selection**: Use `ESP32 Dev Module` or `TTGO LoRa32-OLED` (as suggested in some versions).

## Display Wiring (Internal SPI)
| Function | ESP32 Pin | Note |
| --- | --- | --- |
| BUSY | 4 | |
| RST | 16 | |
| DC | 17 | |
| CS | 5 | |
| SCK | 18 | |
| DIN (MOSI) | 23 | |

## User Peripherals
- **Buttons**:
    - IO0 (BOOT)
    - Various other IOs depending on the specific V1.x or V2.x version.

## Links
- [LilyGo T-Ink Series GitHub](https://github.com/Xinyuan-LilyGO/LilyGo-T5-ink-series)
- [TTGO-T5-ePaper 1.54 GitHub](https://github.com/LilyGO/TTGO-T5-ePaper1.54)
