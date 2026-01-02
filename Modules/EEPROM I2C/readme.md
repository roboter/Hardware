# I2C EEPROM (BR24L16 and similar)

<img src="./BR24L16.PDF" width="320" alt="BR24L16 datasheet"/>

**Short description**
I2C EEPROM devices (e.g., BR24L16) provide non-volatile storage accessible over the I2C bus. Good for storing configuration, logs, or calibration data.

**Key notes**
- Interface: I2C
- Capacity: depends on part (e.g., 16 kbit for BR24L16)
- Page write limitations: observe page size when writing

**Wiring**
See `wiring.md` for I2C wiring and example read/write notes.

**Files**
- `BR24L16.PDF` (datasheet)

*Add example read/write code for your preferred platform to make this README more useful.*