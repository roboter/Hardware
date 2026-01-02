# Wiring — I2C EEPROM

Connections:
- VCC -> 3.3 V or 5 V (as specified by EEPROM)
- GND -> ground
- SDA -> I2C SDA (use pull-ups if not present)
- SCL -> I2C SCL
- WP -> optional write-protect pin (tie high or low per datasheet)

Notes:
- Respect the device's page size when doing page writes to avoid data wrapping.
- Use appropriate addressing for multiple EEPROMs on the bus.