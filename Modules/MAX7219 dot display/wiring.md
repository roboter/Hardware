# Wiring — MAX7219 Dot Matrix (SPI)

Single module connections:
- VCC -> 5 V
- GND -> ground
- DIN -> MOSI (microcontroller data out)
- CLK -> SCK (clock)
- CS / LOAD -> any available GPIO (chip select)

Cascading modules:
- Connect DOUT of module 1 to DIN of module 2
- Share CLK and CS lines across modules
- Remember to use adequate power supply for multiple modules

Notes:
- Use library support (e.g., Arduino MD_MAX72XX or LedControl) to control multiple displays easily.