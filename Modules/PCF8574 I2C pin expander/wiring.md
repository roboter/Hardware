# Wiring — PCF8574 (I2C GPIO Expander)

Connections:
- VCC -> 3.3 V or 5 V (verify module tolerance)
- GND -> ground
- SDA -> I2C SDA
- SCL -> I2C SCL
- A0 / A1 / A2 -> address configuration (pull-up or pull-down)
- P0..P7 -> GPIO pins (quasi-bidirectional)

Notes:
- Use appropriate pull-ups on the I2C lines if not present on the board.
- Scan the bus with `i2cdetect` to find the module address before use.