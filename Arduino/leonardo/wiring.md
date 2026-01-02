# Wiring — Arduino Leonardo

- Power:
  - USB-powered (5V). Some clones may also expose RAW or VIN pins for external supply.
- MCU:
  - ATmega32U4 with native USB.
- Pins:
  - Standard Arduino Leonardo pinout (digital, analog, PWM) — check silkscreen for exact pin numbers.
- Programming:
  - Uses built-in USB bootloader — plugs into a host and exposes a virtual COM port.
- Safety:
  - Ensure 5V signals on I/O are compatible with attached peripherals.

> Note: Refer to official Arduino Leonardo documentation for exact pin mapping and USB behavior.