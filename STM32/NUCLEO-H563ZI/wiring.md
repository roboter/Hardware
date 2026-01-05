# Wiring — NUCLEO-H563ZI

- Power: Ensure proper handling of multiple power domains if present; USB typically provides core supply.
- Debugging: Use on-board ST-Link for programming and SWD debug.
- Peripherals: Consult board-specific schematics for ADC and peripheral pinouts.
- Safety: Large-feature Nucleo boards may have extra power rails — double-check before connecting high-current devices.