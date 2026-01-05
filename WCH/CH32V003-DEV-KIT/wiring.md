# Wiring — CH32V003-DEV-KIT

- Power:
  - Board typically powered via USB or external 3.3V supply; check board regulator.
- Debugging/Programming:
  - CH32V003 boards use SWD for programming; ensure a common ground and correct VTref when using WCH-Link.
- Peripherals:
  - SSD1306 OLED and I2C examples included in this folder — connect SCL/SDA to MCU I2C pins and observe pull-ups if needed.
- Safety:
  - Measure Vcc before connecting unknown modules; avoid applying 5V to 3.3V-only pins.