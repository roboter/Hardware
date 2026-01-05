# Wiring — NUCLEO-C031C6

- Power:
  - Nucleo boards typically provide 3.3V from USB; some pins are 5V-tolerant on Arduino headers—check silkscreen and user manual.
- Debugging:
  - On-board ST-LINK provides programming and debugging; SWD is the standard interface.
- Pins:
  - User LED and button mappings are on the board silkscreen; consult `readme.md` for details.
- Safety:
  - Verify pin voltage tolerances before connecting external devices to Arduino-style headers.