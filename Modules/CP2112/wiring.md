# Wiring — CP2112 (USB to I2C)

Typical connections:
- USB -> host computer (power + data)
- VCC (3.3 V) -> device power (check module regulator)
- GND -> common ground
- SDA -> I2C SDA
- SCL -> I2C SCL

Notes:
- Install CP2112 drivers on host machine to enumerate the device.
- For Windows/macOS/Linux, use Silicon Labs' library or HID APIs to control I2C transactions.