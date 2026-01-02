# Wiring — Digistump / Digispark (ATTINY85)

- Power:
  - Typical operating voltage: 5V (via USB or VCC pin).
  - Some boards may be 3.3V variants — check silkscreen before powering.
- Pins:
  - ATTiny85 general-purpose pins exposed (check Digispark pinout image in folder).
  - `LED_BUILTIN` is usually mapped to a pin defined in the hardware.
- Programming:
  - Use the Digistump bootloader and USB-based upload procedure; refer to the Digistump docs.
- Safety:
  - Verify VCC voltage before connecting 3.3V sensors.
  - Avoid driving pins beyond supply voltage.

> Note: For exact pin mapping and USB upload behavior, consult the board's pinout image `Digispark-Pinout.png` in this folder.