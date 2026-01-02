# Wiring — CJMCU-Beetle (ATmega32U4)

- Power:
  - Operating voltage: 5V. Supply via USB or 5V pin.
- Pins:
  - Digital I/O and PWM pins follow ATmega32U4 pinout — check silkscreen.
  - I2C: SDA / SCL available on header (use 5V I2C devices or level-shift to 3.3V where needed).
  - UART (TX/RX) exposed on headers for serial communications.
- Programming:
  - Bootloader present — use USB for programming or SPI/ICSP for low-level programming.
- Safety:
  - Verify voltage before connecting sensors; do not drive 5V signals into 3.3V-only peripherals.

> Note: Consult the board silkscreen for exact pin labels and confirm with a multimeter if unsure.