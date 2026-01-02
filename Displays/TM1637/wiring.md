# Wiring — TM1637

- Interface: 2-wire protocol (CLK, DIO) — not standard I2C but similar two-line serial protocol used by TM1637.
- Power: Typically 5V modules; check module labelling.
- Notes:
  - Use the library's example code to drive the display. CLK and DIO are bidirectional data lines.
  - Do not connect to I2C devices expecting standard I2C protocol — TM1637 uses its own signaling.
- Safety:
  - Confirm the module supply voltage; use level shifting when interfacing with different logic voltages.

> Note: Refer to `Datasheet_TM1637.pdf` for detailed protocol and timing.