# Displays Wiring and Programming

This directory contains resources for various display technologies (OLED, LCD, TFT, 7-Segment).

## Common Display Controllers

### SSD1306 (OLED)
- **Interface**: I2C or SPI.
- **I2C Address**: Usually 0x3C or 0x3D.
- **Voltage**: 3.3V or 5V (check module).

### ST7735 / ST7789 (TFT)
- **Interface**: SPI.
- **Typical Pins**: CS, DC (Data/Command), RST (Reset), BL (Backlight).

### HD44780 (Character LCD)
- **Interface**: Parallel (8-bit or 4-bit) or I2C (via PCF8574 backpack).
- **I2C Address**: Usually 0x27 or 0x3F.

### TM1637 (7-Segment)
- **Interface**: 2-wire serial (CLK, DIO). NOT standard I2C.

## Folders
Refer to subfolders for specific driver code and wiring:
- [SSD1306/](SSD1306/)
- [HD44780/](HD44780/)
- [st7789/](st7789/)
- [TM1637/](TM1637/)
- ...and others.
