# Wiring — STM8 family overview

- Power: Most STM8 dev boards use 3.3V from a USB-connected regulator. Verify target voltage before connecting peripherals.
- Programming: Use ST-Link or dedicated STM8 programmers. SWIM (single-wire) is commonly used for STM8 devices; some boards expose JTAG connectors.
- Safety: Verify Vcc and use current-limited supplies for initial bring-up when testing modified boards.