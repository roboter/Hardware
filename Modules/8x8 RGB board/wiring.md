# Wiring — 8×8 RGB Matrix

Generic guidance:
- For WS2812-style matrices: single DATA line (DIN) -> microcontroller output, 5 V power and ground common; use level shifter if MCU is 3.3 V.
- For multiplexed RGB matrices: rows/cols driven by matrix driver or shift registers with current-limiting resistors.

Notes:
- Ensure sufficient power (each LED draws up to ~60 mA at full white).
- Add a large decoupling capacitor and use a proper power supply.