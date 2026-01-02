# AD9833 DDS Signal Generator Module

<img src="./AD9833-Programmable-Microprocessors-Serial-Interface-Module-Sine-Square-Wave-DDS-Signal-Generator-Module.jpg" width="420" alt="AD9833 module"/>

**Short description**
Small DDS module based on AD9833 for generating sine/square/triangle waveforms. Control via SPI-like serial interface.

**Key pins**
- VCC: 3.3 V
- GND: ground
- SDATA / FDATA: serial data (use SPI MOSI)
- SCLK: serial clock
- FSYNC / RESET: latch / reset

**Wiring**
See `wiring.md` in this folder for example connections to a microcontroller.

**Notes**
- AD9833 outputs are analog (sine) and may require buffering for low impedance loads.
- Confirm operating voltage and add output filtering as needed.