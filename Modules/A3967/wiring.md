# Wiring — A3967 EasyDriver

Typical connections:
- VMOT / V+ : motor power (up to module rating)
- GND : motor and logic ground
- STEP : step pulse input
- DIR : direction input
- EN / SLP : enable / sleep pins (optional)

Notes:
- Set current limit via potentiometer on driver (if present).
- Use proper decoupling and heatsinking for higher currents.