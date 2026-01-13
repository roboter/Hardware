# EINK (E-Paper) Wiring and Programming

E-Ink displays offer low power consumption and high visibility in sunlight.

## Common Features
- **Interface**: SPI.
- **Refresh Rate**: Slow (requires full or partial refresh).
- **Persistence**: Content remains visible without power.

## Typical Pinout (SPI)
| Pin | Function | Note |
| --- | --- | --- |
| CS | Chip Select | |
| DC | Data/Command | |
| RST | Reset | |
| BUSY | Busy Signal | Must be checked before sending new data |
| DIN | SPI MOSI | |
| CLK | SPI Clock | |

## Specific Boards
- [lilygo T5-4.7 inch/](lilygo T5-4.7 inch/): Details for the powerful ESP32-based E-Ink display.
