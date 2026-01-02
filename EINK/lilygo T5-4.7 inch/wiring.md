# Wiring and power notes — Lilygo T5 4.7" e-paper ESP32 board

- Power:
  - Built-in 18650 battery holder; the board includes a Li-Ion charging circuit.
  - USB-C provides power and can charge the battery. When using external power, ensure the battery is connected properly and polarity is correct.
- Battery:
  - Use a single 18650 Li-Ion cell or compatible single-cell LiPo sized to the holder.
  - Remove battery when working on exposed wiring or when storing the board for long periods.
- Pins / Peripherals:
  - ESP32 pins are available on header pads — verify silkscreen and board documentation before wiring.
  - If using display touch or external sensors, check voltage tolerances (3.3V logic) and avoid supplying >3.3V to GPIOs.
- Safety:
  - Verify the battery holder wiring and that the protection circuit (if present) is functional.
  - Do not short the battery terminals; use a multimeter to check orientation and voltage before connecting.

> Note: This is general guidance — consult the specific Lilygo documentation and any on-board markings for charger IC details and exact pinouts before connecting sensors or batteries.