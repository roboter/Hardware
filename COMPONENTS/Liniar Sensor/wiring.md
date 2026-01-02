# Wiring — TSL2014

- The TSL2014 is a photodiode-based light-to-voltage sensor; see `TSL2014.pdf` for electrical characteristics.
- Power:
  - Observe recommended supply voltages in the datasheet (often 2.7–5.5V range depending on part).
- Output:
  - Analog voltage output proportional to illuminance; connect to ADC input through appropriate scaling if needed.
- Safety:
  - Avoid exceeding supply voltage; consult datasheet absolute maximums.

> Note: Use an ADC with adequate input range and sample rate to read the sensor accurately.