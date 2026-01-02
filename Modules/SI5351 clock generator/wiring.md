# Wiring — SI5351 (I2C)

Connections:
- VCC -> 3.3 V (confirm module voltage)
- GND -> ground
- SDA -> I2C SDA
- SCL -> I2C SCL

Notes:
- Use I2C address from datasheet/module or scan with i2cdetect.
- Add pull-up resistors (4.7k typical) to SDA and SCL if not present on the module.