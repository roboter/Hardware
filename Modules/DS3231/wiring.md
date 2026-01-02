# Wiring — DS3231 RTC Module

Typical pins:
- VCC: 3.3 V or 5 V (module dependent)
- GND: ground
- SDA: I2C data
- SCL: I2C clock
- SQW / INT: optional square-wave or interrupt output

Notes:
- Use pull-ups on I2C lines if not present on module.
- Confirm backup battery is present and seated properly.