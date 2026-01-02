# Wiring — AD9833 DDS Module

Example SPI-like wiring:
- VCC -> 3.3 V
- GND -> ground
- SDATA -> MOSI
- SCLK -> SCK
- FSYNC -> CS
- RESET -> optional reset pin

Notes:
- Use the AD9833 library or write register-level code to program frequency and waveform type.
- Buffer outputs for low impedance loads to avoid distortion.