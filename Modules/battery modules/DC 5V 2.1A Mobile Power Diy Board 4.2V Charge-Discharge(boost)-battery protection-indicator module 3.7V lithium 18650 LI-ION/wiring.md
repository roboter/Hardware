# Wiring — DD06CVSA Mobile Power / Boost Module

Common pins (verify by silkscreen):
- VIN (or Charging port +)  — connect to USB 5 V input (or charging source)
- GND — ground (USB ground / battery negative)
- BAT — battery + (3.7–4.2 V)
- VOUT (or 5V) — boosted 5 V output
- KEY — output trigger (active low pulse; see README)

Example connections:

USB 5 V (+) ---- [VIN]
USB GND   ------ [GND]
Battery (+) ---- [BAT]
Battery (-) ---- [GND]
Device + ------- [VOUT]
Device - ------- [GND]

Notes: Verify the pin silkscreen and that the module has on-board charging/protection. Use the KEY pin as documented to toggle output where needed.