# Commodore-board (ESP32-WROOM-32UE) Wiring and Programming

This board is specialized for Commodore IEC interface projects.

## Board Features
- **MCU**: ESP32-WROOM-32UE
- **Goal**: Interface with Commodore 64/128 IEC bus.
- **On-board LEDs**:
    - LED2: GPIO2
    - LED3: GPIO4

## Programming
- **IDE**: Arduino IDE.
- **Board Selection**: `ESP32 Dev Module`.
- **Bootloader**: Perform a **RESET** while holding **BOOT0 (GPIO0)** to enter programming mode.

## Commodore IEC Wiring
Pins are connected to a DIN6 connector for the Commodore IEC bus:

| Function | ESP32 Pin | Commodore DIN6 Pin |
| --- | --- | --- |
| ATN | GPIO32 | 3 |
| CLK (In/Out) | GPIO33 | 4 |
| DATA (In/Out) | GPIO25 | 5 |
| SRQ | GPIO26 | 1 |
| RESET | GPIO34 | 6 |
| GND | GND | 2 |

## Notes
- **Power Consumption**: ~0.052 A.
- **GPIO34/35**: These pins are input-only and cannot be used as outputs for LEDs.

## Links
- [Commodore-board Reference (AliExpress)](https://www.aliexpress.com/item/1005001438925793.html)
