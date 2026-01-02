# Wiring & Repair Notes — frankenstein

- This folder documents a repair/experiment where an ATmega/compatible MCU was replaced and some power traces were modified.
- If you are testing this board:
  - Verify any cut or bridged power lines with a multimeter before applying power.
  - Power up with a current-limited bench supply initially (set a low current limit, e.g., 100–200 mA) to avoid smoke on wiring errors.
  - Keep suspects isolated and double-check pin mappings of the replacement MCU (pinouts and Vcc/GND pins).
- Safety:
  - Repairs can leave floating nets or exposed copper — be careful with short circuits and avoid powering until you are confident of connections.