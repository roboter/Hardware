# Wiring — INA3221 (I2C)

Connections:
- VCC -> 3.3 V (or module specified voltage)
- GND -> ground
- SDA -> I2C SDA
- SCL -> I2C SCL
- SHUNT+ / SHUNT- : connect shunt resistor for each channel

Notes:
- Place sense resistor close to the monitored load and keep traces short.
- Choose shunt resistance to keep voltage drop small while providing measurable voltage for ADC input.