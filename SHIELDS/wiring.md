# SHIELDS Wiring and Compatibility

Arduino Shields are designed to plug directly into the headers of an Arduino-format board (Uno, Mega, Leonardo).

## General Notes

### Header Alignment
Ensure all pins are aligned before pressing the shield down. Misalignment can short power pins to I/O or Ground.

### Multi-shield Stacking
Shields can often be stacked, but you must check for:
1. **Pin Conflicts**: If two shields use the same I/O pin for different functions (e.g., both use D10 for Chip Select).
2. **Current Limits**: Multiple shields may exceed the power supply capability of the base board.

### Compatibility
- **Uno/Mega**: Most shields fit both, but SPI pins differ (Uno: D11/12/13, Mega: D51/52/50).
- **3.3V vs 5V**: Some older shields expect 5V and may damage 3.3V-only boards (like Duo or some ESP32 variants).

## Folders
- [Multi_Function_Shield/](Multi_Function_Shield/): Everything-on-one educational shield.
- [OPEN-SMART Rich Shield TWO/](OPEN-SMART Rich Shield TWO/): Advanced IoT learning shield.
- [ZYA0031/](ZYA0031/): Comprehensive IoT kit.
