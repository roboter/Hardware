# Si5351 VFO/RF Generator — Button Controls

## Overview
This firmware implements a **3-channel VFO / RF Signal Generator** (`CLK0`, `CLK1`, `CLK2`) using a **CH32V003F4P6**, an **Si5351A** clock generator, a **128×64 dual-color SSD1306 OLED** with a **Retro Vernier Drum Dial**, and 5 navigation buttons.

## Hardware Setup
- **MCU**: WCH CH32V003F4P6
- **Display**: SSD1306 128×64 OLED (`0x3C`, I2C1) — 16 px yellow top bar + 48 px blue area
- **Generator**: Si5351A (`0x60`, I2C1) — `10 kHz` to `225 MHz`
- **Buttons (`GPIOC`, active-high)**:
  - `UP` (`PC7`), `DOWN` (`PC4`), `LEFT` (`PC5`), `RIGHT` (`PC6`), `ENTER` (`PC3`)

---

## Focus Modes (`ENTER` Short Press)

A **short press** on `ENTER` cycles the active UI focus:

1. **`FOCUS_TABS`** (Top Yellow Bar): Select `CLK0`, `CLK1`, `CLK2`, or `SYS`
2. **`FOCUS_DIAL`** *(default)* (Frequency & Drum Dial): Tune frequency and step cursor
3. **`FOCUS_CONFIG`** (Bottom Config Strip): Configure dial style and IF offset

*(When on the `SYS` tab, short-pressing `ENTER` toggles between `FOCUS_TABS` and `FOCUS_CONFIG`.)*

---

## Button Actions by Focus Mode

### 1. Dial Focus (`FOCUS_DIAL`)
- **`UP` / `DOWN`**: Tune active channel frequency up or down by the selected step size.
  - Holding `UP` or `DOWN` triggers **14–20 Hz auto-repeat** after ~250 ms, smoothly scrolling the drum dial.
- **`LEFT` / `RIGHT`**: Move the digit cursor across the 9-digit readout (`XXX.XXX.XXX`), changing the step size per tick:
  - `100 MHz` ↔ `10 MHz` ↔ `1 MHz` ↔ `100 kHz` ↔ `10 kHz` *(default)* ↔ `1 kHz` ↔ `100 Hz` ↔ `10 Hz` ↔ `1 Hz`
- **`ENTER` (Short)**: Switch to `FOCUS_CONFIG`.
- **`ENTER` (Hold ≥ 500 ms)**: Toggle the active channel output **ON / OFF** (`▲` solid = ON, `△` hollow = OFF).

### 2. Tab Focus (`FOCUS_TABS`)
- **`LEFT` / `RIGHT`**: Switch between `CLK0`, `CLK1`, `CLK2`, and `SYS`.
- **`UP` / `DOWN`**: Toggle the active channel output **ON / OFF**.
- **`ENTER` (Short)**: Switch to `FOCUS_DIAL` (or `FOCUS_CONFIG` on `SYS`).
- **`ENTER` (Hold ≥ 500 ms)**: Toggle the active channel output **ON / OFF**.

### 3. Config Focus (`FOCUS_CONFIG`)
- **`LEFT` / `RIGHT`**: Select setting (`DIAL` or `IF`).
- **`UP` / `DOWN`**: Change value:
  - **`DIAL`**: `CURVED` (parabolic drum droop) ↔ `FLAT`
  - **`IF`**: `0` (`VFO` mode) ↔ `455k` (`+455 kHz` `LO` mode) ↔ `10.7M` (`+10.7 MHz` `LO` mode)
- **`ENTER` (Short)**: Return to `FOCUS_TABS`.
- **`ENTER` (Hold ≥ 500 ms)**: Toggle the active channel output **ON / OFF**.

---

## Display Layout

```text
+------------------------------------------+
| [CLK0]  CLK1   CLK2   SYS  |    ON       | ← Yellow Bar: Tabs + Output Status
+------------------------------------------+
| 145.000.000               STP:10k        | ← Digital Readout + Active Step
|     ^                                    | ← Active Digit Cursor
| |         ===                            | ← Min..Max Limit Bar (10k..225M)
|  144.9      145.0      145.1             | ← Sliding Major Scale Labels
|   .  |  .  |  .  |  .  |  .  |  .  |     | ← Parabolic Drum Dial (0-RAM)
| VFO               ▲                 CRV  | ← Mode, Pointer (▲/△), Dial Style
+------------------------------------------+
```

### Channel Defaults & Limits
- **Frequency Range**: `10 kHz` (`SI5351_MIN_FREQ`) to `225 MHz` (`SI5351_MAX_USER_FREQ`)
- **Defaults**:
  - `CLK0`: `145.000.000 Hz` (`ON`, `10 kHz` step)
  - `CLK1`: `10.700.000 Hz` (`OFF`, `10 kHz` step)
  - `CLK2`: `7.100.000 Hz` (`OFF`, `10 kHz` step)
