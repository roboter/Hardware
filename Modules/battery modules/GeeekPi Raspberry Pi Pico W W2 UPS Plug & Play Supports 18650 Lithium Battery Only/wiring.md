# Wiring — GeeekPi Pico UPS (1×18650)

Typical connections:
- Battery holder: + -> BAT+, - -> GND
- Board-to-Pico connector: plug into Pico header (board intended for direct Pico mounting)

Power routing:
- Battery provides power to onboard regulator/charging circuit.
- Output to Pico is usually via VSYS / 5V header — check the board silkscreen to confirm which pin the module feeds.

Notes:
- Confirm how the module handles USB power vs. battery (auto-switching or charging behaviour).
- If unclear, measure the module's output pins with and without USB connected to understand power path.