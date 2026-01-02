# Wiring — 2S BMS (HX-2S-JH20 style)

Terminals usually found on board:
- B+ : pack positive
- B- : pack negative
- B1 / MMB : middle connection between cell1 and cell2 (balance point)
- P+ / P- : charge / discharge output terminals (shared)

Typical wiring for 2×18650 (series):

Cell1 (-) ---- [B-]
Cell1 (+) ---- [B1 / MMB]
Cell2 (-) ---- [B1 / MMB]
Cell2 (+) ---- [B+]

Charger / Load:
Charger + / Load + ---- [P+]
Charger - / Load - ---- [P-]

Safety notes:
- Verify each pad with a multimeter to avoid reversing cells.
- Confirm that P+/P- are rated for your load (this board indicates ~10 A working current on the label).