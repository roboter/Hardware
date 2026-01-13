# WCH (RISC-V) Wiring and Programming

## Programming Tools
- **WCH-Link / WCH-LinkE**: The official programmer/debugger for WCH microcontrollers.
- **SWDIO / SDI**: RISC-V single-wire debug interface used for programming.
- **MounRiver Studio**: The recommended IDE for development.

## Power Supply
- Most CH32V003 boards operate at **3.3V**.
- Power can be supplied via the USB connector or the VCC/GND pins.
- **Warning**: Always verify the voltage requirements before connecting external power.

## Pinout and Connections
Each board variant may have specific pinouts. Refer to the `wiring.md` in individual board folders for detailed connections:
- [CH32V003-DEV-KIT/wiring.md](CH32V003-DEV-KIT/wiring.md)
- [CH32V003EVT/wiring.md](CH32V003EVT/wiring.md)
- [CH32V003J4M6/wiring.md](CH32V003J4M6/wiring.md)
- [ch32v003f4p6-SignalGenerator/wiring.md](ch32v003f4p6-SignalGenerator/wiring.md)
