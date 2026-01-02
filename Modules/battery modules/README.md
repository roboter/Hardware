# Battery Modules ⚡️

This document summarizes the battery-related modules in this folder and links to per-module files (images, datasheets and module READMEs where available).

---

## Quick index

| Module (folder) | Image | Type | Config(s) | Key specs | Files / Notes |
|---|:---:|---:|---|---|---|
| `1S 2S 3S 4S Single 3.7V 18650 Lithium Battery Capacity Indicator Module Percent Power Level Tester LED display board` | <img src="./1S 2S 3S 4S Single 3.7V 18650 Lithium Battery Capacity Indicator Module Percent Power Level Tester LED display board/S233aac683bb04ca89b503580a7f012b0G.jpg_960x960q75.jpg_.avif" width="120"/> | Indicator | 1S–4S | LED capacity indicator for single/multi-cell packs | has images, small `readme.md` ("my is 2s") |
| `2S 12A 8.4V Li-ion BMS Protection Plate with Balancing for Dual 18650 Batteries, Overcharge` | <img src="./2S 12A 8.4V Li-ion BMS Protection Plate with Balancing for Dual 18650 Batteries, Overcharge/S7cd60b97ad3a4c7baa2ed66f75ca0722m.webp" width="120"/> | BMS / Protection | 2S | HX-2S-JH20, 10 A working current, max instantaneous 20 A, size 46.7×23×3.15mm | `readme.md` with pinout & specs |
| `AA_AAA dry battery modified to lithium battery 3V-4.2V reduced by 1.5V` | <img src="./AA_AAA dry battery modified to lithium battery 3V-4.2V reduced by 1.5V/battery 1_5v replacement.webp" width="120"/> | Adapter / Converter | Single cell | Converts 3.7–4.2V Li to ~1.5V for AA/AAA form-factor devices | image only |
| `DC 5V 2.1A Mobile Power Diy Board 4.2V Charge-Discharge(boost)-battery protection-indicator module 3.7V lithium 18650 LI-ION` | <img src="./DC 5V 2.1A Mobile Power Diy Board 4.2V Charge-Discharge(boost)-battery protection-indicator module 3.7V lithium 18650 LI-ION/HTB1y5nybzihSKJjy0Feq6zJtpXae.webp" width="120"/> | Charge/boost / Protection / Indicator | 1S (18650) | Input 4.5–5.2V, Output 5V@0–2.1A, Charge up to 2.1A, Discharge up to 3.5A, protections: OCP/OVP/SCP/OTP | `readme.md` with pinout & usage |
| `GeeekPi Raspberry Pi Pico W W2 UPS Plug & Play Supports 18650 Lithium Battery Only` | <img src="./GeeekPi Raspberry Pi Pico W W2 UPS Plug & Play Supports 18650 Lithium Battery Only/S6a45ee01fc5e4d11aedc195ac19e968dV.webp" width="120"/> | UPS for Pico | 1×18650 | Pico UPS module, plug & play for Pico/Pico W/W2 | `readme.md` |
| `MH-CD42 CD42 DC 5V 2.1A Mobile Power Diy Module 3.7` | (no image) | Charge/boost (likely) | 1S | (no readme) | empty `readme.md` (needs documentation) |
| `Multi-Cell 2S 3S 4S Type-C To 8.4V 12.6V 16.8V Step-Up Boost LiPo Polymer Li-Ion Charger` | <img src="./Multi-Cell 2S 3S 4S Type-C To 8.4V 12.6V 16.8V Step-Up Boost LiPo Polymer Li-Ion Charger/schematic.webp" width="120"/> | Multi-cell step-up charger | 2S/3S/4S | Supports 2S/3S/4S, Type-C input, charging currents: 0.55A/1.1A/2.2A (depending on version) | `readme.md`, schematic image |
| `TZT 2S Li-ion 18650 Lithium Battery Charger Protection Board 7.4V Overcurrent Overcharge Overdischarge Protection 4A BMS` | <img src="./TZT 2S Li-ion 18650 Lithium Battery Charger Protection Board 7.4V Overcurrent Overcharge Overdischarge Protection 4A BMS/S0d605b834bc345369fcd0a1a6a79c3ab2.webp" width="120"/> | BMS / Charger | 2S | 4A BMS, protections (OCP/OVP/ODP) | images present, `readme.md` empty |
| `Type-C USB 2_3S BMS 15W 8.4V 12.6V 1.5A Lithium Battery Charging Boost Module With Balanced Support Fast Charge With Indicator` | <img src="./Type-C USB 2_3S BMS 15W 8.4V 12.6V 1.5A Lithium Battery Charging Boost Module With Balanced Support Fast Charge With Indicator/9c528e8772f7821052815b3e235ab789.jpg_2200x2200q80.jpg_.webp" width="120"/> | BMS / Charger / Boost | 2S / 3S | Up to 15 W, 1.5 A, balanced support, IP2326 controller (datasheet present) | `readme.md` (note: "Schematic is wrong"), IP2326 datasheet, pinout image |

---

## Per-module details

### 1S 2S 3S 4S Single 3.7V 18650 Lithium Battery Capacity Indicator Module Percent Power Level Tester LED display board
- Path: `Modules/battery modules/1S 2S 3S 4S Single 3.7V 18650 Lithium Battery Capacity Indicator Module Percent Power Level Tester LED display board`
- Files: images, minimal `readme.md` (only "my is 2s")
- Image: <img src="./1S 2S 3S 4S Single 3.7V 18650 Lithium Battery Capacity Indicator Module Percent Power Level Tester LED display board/S233aac683bb04ca89b503580a7f012b0G.jpg_960x960q75.jpg_.avif" width="240"/>
- Notes: add a proper description / pinout when available (currently missing).

### 2S 12A 8.4V Li-ion BMS Protection Plate with Balancing for Dual 18650 Batteries, Overcharge
- Path: `Modules/battery modules/2S 12A 8.4V Li-ion BMS Protection Plate with Balancing for Dual 18650 Batteries, Overcharge`
- Image: <img src="./2S 12A 8.4V Li-ion BMS Protection Plate with Balancing for Dual 18650 Batteries, Overcharge/S7cd60b97ad3a4c7baa2ed66f75ca0722m.webp" width="240"/>
- Key specs (from module README): Model: HX-2S-JH20; charging voltage 8.4–9V; operating current 10 A; max instantaneous 20 A; static current <10 μA; size 46.7×23×3.15 mm.
- Pinout notes in README: `B+` (battery +), `B-` (battery -), `MMB` (balance between cells), `P+`/`P-` (charge/discharge output).

### AA_AAA dry battery modified to lithium battery 3V-4.2V reduced by 1.5V
- Path: `Modules/battery modules/AA_AAA dry battery modified to lithium battery 3V-4.2V reduced by 1.5V`
- Files: image only — add documentation if you have notes on the circuit or module behaviour.
- Image: <img src="./AA_AAA dry battery modified to lithium battery 3V-4.2V reduced by 1.5V/Se2403a4270644fe3a738096ad8ea9fbcl.webp" width="240"/>

### DC 5V 2.1A Mobile Power Diy Board 4.2V Charge-Discharge(boost)
- Path: `Modules/battery modules/DC 5V 2.1A Mobile Power Diy Board 4.2V Charge-Discharge(boost)-battery protection-indicator module 3.7V lithium 18650 LI-ION`
- Summary: DD06CVSA multifunctional mobile power module — charge, discharge (boost), battery protection and indicator. Input 4.5–5.2V; Output 5V@0–2.1A; Charging up to 2.1A; Discharge conversion efficiency up to 96%; protections: OCP/OVP/SCP/OTP. Includes pin descriptions and KEY trigger behaviour.
- Image: <img src="./DC 5V 2.1A Mobile Power Diy Board 4.2V Charge-Discharge(boost)-battery protection-indicator module 3.7V lithium 18650 LI-ION/HTB1y5nybzihSKJjy0Feq6zJtpXae.webp" width="240"/>

### GeeekPi Raspberry Pi Pico/Pico W/W2 UPS
- Path: `Modules/battery modules/GeeekPi Raspberry Pi Pico W W2 UPS Plug & Play Supports 18650 Lithium Battery Only`
- Image: <img src="./GeeekPi Raspberry Pi Pico W W2 UPS Plug & Play Supports 18650 Lithium Battery Only/S6a45ee01fc5e4d11aedc195ac19e968dV.webp" width="240"/>
- Summary: Single 18650 UPS module tailored for Raspberry Pi Pico family. Useful for portable Pico projects; simple plug-and-play.

### MH-CD42 CD42 DC 5V 2.1A Mobile Power Diy Module 3.7
- Path: `Modules/battery modules/MH-CD42 CD42 DC 5V 2.1A Mobile Power Diy Module 3.7`
- Image: (none available) 
- Files: empty `readme.md` — please add specs or copy a similar description from the other 5V boost modules.

### Multi-Cell 2S/3S/4S Type-C Step-Up Charger
- Path: `Modules/battery modules/Multi-Cell 2S 3S 4S Type-C To 8.4V 12.6V 16.8V Step-Up Boost LiPo Polymer Li-Ion Charger`
- Image: <img src="./Multi-Cell 2S 3S 4S Type-C To 8.4V 12.6V 16.8V Step-Up Boost LiPo Polymer Li-Ion Charger/schematic.webp" width="240"/>
- Summary: Type-C input to step-up charger for 2S/3S/4S packs. Features switching up to 1 MHz, quasi-CV mode, automatic recharge, battery overvoltage protection. Size ~39×18×6.3 mm. Charging currents depend on selected version (0.55A / 1.1A / 2.2A).

### TZT 2S Li-ion 18650 Charger/Protection Board (4A)
- Path: `Modules/battery modules/TZT 2S Li-ion 18650 Lithium Battery Charger Protection Board 7.4V Overcurrent Overcharge Overdischarge Protection 4A BMS`
- Image: <img src="./TZT 2S Li-ion 18650 Lithium Battery Charger Protection Board 7.4V Overcurrent Overcharge Overdischarge Protection 4A BMS/S0d605b834bc345369fcd0a1a6a79c3ab2.webp" width="240"/>
- Files: images present but `readme.md` is empty — recommend adding the BMS nominal specs and pinout.

### Type-C USB 2/3S BMS 15W (IP2326)
- Path: `Modules/battery modules/Type-C USB 2_3S BMS 15W 8.4V 12.6V 1.5A Lithium Battery Charging Boost Module With Balanced Support Fast Charge With Indicator`
- Image: <img src="./Type-C USB 2_3S BMS 15W 8.4V 12.6V 1.5A Lithium Battery Charging Boost Module With Balanced Support Fast Charge With Indicator/9c528e8772f7821052815b3e235ab789.jpg_2200x2200q80.jpg_.webp" width="240"/>
- Files of interest: `IP2326 datasheet v1.0.pdf`, `lisc-pinout.png`, images. Current note in README: "Schematic is wrong" and an external store link. Please verify schematic and use the IP2326 datasheet for accurate pinout and design notes.

---

## How you can help / next steps 🔧
- Add missing module specs into the empty `readme.md` files (`MH-CD42`, `TZT 2S`, `AA/AAA adapter`, etc.).
- Add photos of pin labels and measured voltages where available.
- If you want, I can extract the IP2326 pinout into a short summary and add a verified schematic note.

## Contributing
- Open a PR with updates to individual module folders, or send me the missing details and I can update their `readme.md` files.

---

If you'd like, I can also:
- Add a short wiring diagram per module (if images/pin labels are available) ✅
- Create a short testing checklist for each module (voltage checks, expected behaviour under load) ✅

---

*Generated by GitHub Copilot — Raptor mini (Preview).*