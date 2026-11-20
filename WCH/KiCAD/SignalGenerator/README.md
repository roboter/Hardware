# KiCad — Signal Generator Hardware Workspace

KiCad hardware design files and supporting footprints/references for the **CH32V003F4P6 + Si5351A Signal Generator** project.

---

## Directory Contents

| Item | Description |
|---|---|
| [`SignalGenerator/`](SignalGenerator/) | Main KiCad project (`signalgenerator.kicad_pro`, `signalgenerator.kicad_sch`, `signalgenerator.kicad_pcb`) |
| [`SignalGenerator/signalgenerator-rounded.kicad_pro`](SignalGenerator/signalgenerator-rounded.kicad_pro) | Rounded-tracks PCB variant (`signalgenerator-rounded.kicad_pcb` + `signalgenerator.round-tracks-config`) |
| [`WCH-LinkSCH.PDF`](WCH-LinkSCH.PDF) | WCH-Link programmer/debugger reference schematic |
| [`LR1262.kicad_mod`](LR1262.kicad_mod) | Custom KiCad footprint for `LR1262` (`16×16 mm` SMD module) |
| [`deepseek_python_20251001_d1509a.py`](deepseek_python_20251001_d1509a.py) | Python generator script for `LR1262.kicad_mod` |
| [`grbl/`](grbl/) | GRBL / CNC milling output or related files |
| [`ul_RN42-I-RM/`](ul_RN42-I-RM/) | Ultra Librarian footprint/library package for `RN42-I/RM` |
| [`Screenshot 2023-12-24 143231.png`](Screenshot%202023-12-24%20143231.png) | Design reference screenshot |

---

## Opening the Project in KiCad

1. Launch **KiCad** (KiCad 7+ recommended).
2. Open [`SignalGenerator/signalgenerator.kicad_pro`](SignalGenerator/signalgenerator.kicad_pro) for the standard layout, or [`SignalGenerator/signalgenerator-rounded.kicad_pro`](SignalGenerator/signalgenerator-rounded.kicad_pro) for the rounded-tracks PCB layout.
3. Inspect the schematic in [`SignalGenerator/signalgenerator.kicad_sch`](SignalGenerator/signalgenerator.kicad_sch) and PCB layout in [`SignalGenerator/signalgenerator.kicad_pcb`](SignalGenerator/signalgenerator.kicad_pcb).

---

## Companion Firmware

The CH32V003F4P6 firmware, Retro Vernier Drum Dial UI, wiring guide, and build/flash scripts live in:
- [`../../ch32v003f4p6-SignalGenerator/readme.md`](../../ch32v003f4p6-SignalGenerator/readme.md)
- [`../../ch32v003f4p6-SignalGenerator/wiring.md`](../../ch32v003f4p6-SignalGenerator/wiring.md)
