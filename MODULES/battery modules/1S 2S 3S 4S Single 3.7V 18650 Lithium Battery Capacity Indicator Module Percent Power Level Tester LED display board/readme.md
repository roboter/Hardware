# Capacity Indicator Module (1S–4S)

<img src="./S233aac683bb04ca89b503580a7f012b0G.jpg_960x960q75.jpg_.avif" width="320" alt="Capacity indicator"/>

**Short description**
Compact LED-based battery capacity indicator module supporting 1S–4S packs. Shows approximate state-of-charge with LED segments or percentage display depending on module variant.

**Typical specs (verify on your board)**
- Supported configurations: 1S / 2S / 3S / 4S
- Display: LED bar / numeric indicator (depends on version)
- Power: connect directly to battery monitoring inputs / balance taps (see pinout)

**Pinout / Connections (general)**
- B+, B-, B1, B2, B3, B4: cell/balance inputs depending on number of cells
- VCC / GND: module power (often connected to battery inputs)

**Wiring**
See `wiring.md` in this folder for a short wiring diagram and tips.

**Files**
- Images: `S233aac683bb04ca89b503580a7f012b0G.jpg_960x960q75.jpg_.avif`, `S7bd09779c5714335ac05b6c5f0c9e942R.webp`
- README: this file (please add any additional notes or measured voltages)

**Notes & Safety**
- Always verify cell order and polarity with a meter before connecting.
- This module is an indicator, not a charger or protection device; do not rely on it for safety-critical protection.

*If you have board silk markings or more detailed specs, add them and I will update this README.*