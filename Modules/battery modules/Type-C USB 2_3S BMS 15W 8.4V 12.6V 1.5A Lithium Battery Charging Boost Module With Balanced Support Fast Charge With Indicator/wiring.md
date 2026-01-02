# Wiring — Type-C USB 2/3S BMS (IP2326 based)

Common connections (verify silk on board):
- B+ / B- : pack positive / negative terminals
- Balance pins: B1, B2, B3 (depending on 2S/3S configuration)
- P+ / P- or OUT+: pack output / charge/discharge terminals
- USB Type-C VBUS / GND: input for charging (observe CC wiring in Type-C implementations)

2S wiring example:
Cell1 (-) ---- [B-]
Cell1 (+) ---- [B1]
Cell2 (-) ---- [B1]
Cell2 (+) ---- [B+]

USB input:
Type-C VBUS (+5V) ---- [VIN/USB+] (follow board's Type-C wiring)
USB GND ------------- [GND]

Notes & cautions:
- The included IP2326 datasheet is helpful to verify pin functions — check it when in doubt.
- The original `readme.md` notes the schematic may be incorrect; prefer the IC datasheet and verify continuity/pins with a meter before first power-up.
- For fast charge scenarios, ensure the cell configuration matches the board rating and that balancing is functioning.
