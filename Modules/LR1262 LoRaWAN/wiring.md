# Wiring — LR1262 / SX126x LoRa Module

Typical connections:
- VCC -> 3.3 V (stable supply)
- GND -> ground
- SPI: MOSI / MISO / SCK / NSS (chip select)
- DIOx / IRQ pins -> optional MCU interrupt pins
- ANT -> antenna connector (SMA or PCB antenna)

Notes:
- Use proper antenna and RF matching for best range.
- Follow regional regulations for frequency and transmit power.