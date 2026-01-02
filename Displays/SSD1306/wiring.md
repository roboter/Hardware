# Wiring — SSD1306 (Displays folder)

- Power: 3.3V or 5V depending on module (verify on module).
- Pins: GND, VCC, SCL (I2C SCL), SDA (I2C SDA). Some modules also support SPI.
- I2C addresses commonly 0x3C/0x3D — check module solder jumper.
- Safety: Do not apply 5V to 3.3V-only logic pins; use level shifting when necessary.

> Note: Example code and libraries are linked in the `readme.md` of this folder.