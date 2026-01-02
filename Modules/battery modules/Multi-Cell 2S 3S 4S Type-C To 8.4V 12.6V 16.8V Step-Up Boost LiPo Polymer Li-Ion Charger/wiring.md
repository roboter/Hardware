# Wiring — Multi-Cell Type-C Step-Up Charger (2S/3S/4S)

Common connections (2S example shown):

2S terminals:
- B- : pack negative
- B1 : connection between cell1 and cell2 (balance)
- B+ : pack positive

Type-C input:
- USB VBUS (+5 V) -> module input (often labeled VIN / USB+)
- USB GND -> module GND

Output (if present):
- VOUT -> load (verify module has output connector)

2S wiring (cells in series):
Cell1 (-) ---- [B-]
Cell1 (+) ---- [B1]
Cell2 (-) ---- [B1]
Cell2 (+) ---- [B+]

Notes:
- Charging current depends on module version (0.55A / 1A / 2.2A). Confirm silk labels.
- For 3S/4S, additional balance pads (B2, B3 ...) will be present—match each series cell to the correct pad.