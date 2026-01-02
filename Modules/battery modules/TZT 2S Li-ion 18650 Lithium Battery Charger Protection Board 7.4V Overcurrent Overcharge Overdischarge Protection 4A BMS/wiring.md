# Wiring — TZT 2S Charger / Protection Board

Common terminals:
- B+ : pack positive
- B- : pack negative
- B1 : middle balance connection (between cell1 and cell2)
- P+ / P- : pack power (charge / discharge)

2S wiring example:
Cell1 (-) ---- [B-]
Cell1 (+) ---- [B1]
Cell2 (-) ---- [B1]
Cell2 (+) ---- [B+]

Charger / load:
Charger + / Load + ---- [P+]
Charger - / Load - ---- [P-]

Notes:
- Verify board markings and rated current (label suggests ~4 A). Use fusing for high-current applications.