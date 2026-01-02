# Wiring — CJMCU‑2232HL (FT2232HL)

Typical connections:
- USB Type‑B / Type‑C to host for USB power and data
- CBUS pins: configurable for CBUS functions (see datasheet)
- UART / SPI / I2C / JTAG pins available on headers

Notes:
- Configure CBUS pins via FT_Prog or EEPROM settings if needed.
- For MPSSE mode, follow AN_411 application note for SPI/I2C bit‑banging examples.