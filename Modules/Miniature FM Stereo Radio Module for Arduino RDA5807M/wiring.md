# Wiring — RDA5807M FM Module

Typical connections:
- VCC -> 3.3 V (or 5 V if module supports it)
- GND -> ground
- SDA -> I2C SDA
- SCL -> I2C SCL
- L/R -> audio outputs to amp / headphone
- ANT -> antenna (wire or external antenna)

Notes:
- Use proper decoupling and a short antenna lead for good reception.
- Example libraries (Arduino) are available to control tuning and audio features.