# SI5351 Clock Generator

**Short description**
SI5351 family clock generator modules provide programmable multi-output clock generation (I2C-controlled PLL and multisynths). Commonly used for OSS/SDR, microcontroller clocks, and test equipment.

**Key notes**
- Control: I2C
- Useful outputs: configurable frequencies up to tens of MHz depending on configuration

**Files**
- `Si5351-B.pdf` (datasheet)

**Wiring**
See `wiring.md` for I2C wiring and typical pull-up requirements.

**Notes & Safety**
- Use appropriate pull-ups on SDA/SCL if not present on your board.
- Confirm power requirements (3.3 V or 5 V tolerant modules usually use 3.3 V I/O).