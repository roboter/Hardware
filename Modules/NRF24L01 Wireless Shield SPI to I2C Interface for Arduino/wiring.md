# Wiring — NRF24L01 I2C Shield

Typical connections:
- VCC (3.3V) -> shield VCC
- GND -> shield GND
- SDA / SCL -> I2C bus pins on Arduino (check board address and documentation)

Notes:
- Shield converts NRF24L01 SPI to I2C/TWI for easier use with microcontrollers.
- Ensure 3.3 V supply for the RF module and proper antenna connection.