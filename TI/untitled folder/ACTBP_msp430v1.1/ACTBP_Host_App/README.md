# 🎵 ACTBP Host Application
### MSP430G2553 LaunchPad — Audio Capacitive Touch BoosterPack

> Firmware for the **MSP430G2553** microcontroller that acts as the host controller for the **C5000 Audio Capacitive Touch BoosterPack (ACTBP)**. It handles capacitive touch input, gesture detection, OLED display output, file system navigation, and UART communication with a C55x DSP running the Audio Player Recorder Framework (APRF / "Raga").

[![Texas Instruments](https://img.shields.io/badge/Texas%20Instruments-MSP430-red)](https://www.ti.com)
[![Version](https://img.shields.io/badge/version-1.1-blue)](.)
[![License](https://img.shields.io/badge/license-BSD--3--Clause-green)](.)
[![Platform](https://img.shields.io/badge/platform-MSP430G2553-orange)](.)

---

## 📋 Table of Contents

- [Overview](#-overview)
- [Hardware Requirements](#-hardware-requirements)
- [Software Requirements](#-software-requirements)
- [Project Structure](#-project-structure)
- [Building the Project](#-building-the-project)
- [Importing into CCS](#-importing-into-ccs)
- [Controls & Gestures](#-controls--gestures)
- [State Machine](#-state-machine)
- [Known Issues](#-known-issues)
- [Changelog](#-changelog)
- [License](#-license)

---

## 🔍 Overview

This firmware runs on the **MSP430G2553** mounted on a **TI LaunchPad** development board. It serves as the host controller for the Audio Capacitive Touch BoosterPack, communicating with a **C55x DSP** over UART to control audio playback, recording, volume, file navigation, and OLED display output.

Key capabilities:
- 🖐️ Capacitive touch wheel — scroll, tap, and hold gesture detection
- 🎶 Audio playback control — play, pause, stop, skip, fast-forward, rewind
- 🎙️ Audio recording with file management
- 📁 File system navigation (directories and MP3 files)
- 📺 OLED display control via APRF display commands
- 🔌 USB Mass Storage Device (MSC) support
- 💤 Sleep / wake / power-off state management
- 🔄 Cycle and shuffle playback modes

---

## 🔧 Hardware Requirements

| Component | Details |
|-----------|---------|
| **MCU** | Texas Instruments **MSP430G2553** |
| **Development Board** | TI **MSP430 LaunchPad** (MSP-EXP430G2) |
| **BoosterPack** | TI **Audio Capacitive Touch BoosterPack (ACTBP)** |
| **DSP** | TI **C55x DSP** (on the BoosterPack) running APRF "Raga" firmware |
| **Display** | **OLED** display (128×64 pixels, 2 visible lines at a time) |
| **Storage** | SD card or compatible storage accessible by the DSP |
| **USB** | USB cable (optional, for USB Mass Storage mode) |
| **LEDs** | 8 LEDs (D6–D13) arranged around the capacitive touch wheel |

### 🔌 Pin Assignments

| Signal | MSP430 Pin | Description |
|--------|-----------|-------------|
| UART RXD | P1.1 (UCA0RXD) | Receive from DSP |
| UART TXD | P1.2 (UCA0TXD) | Transmit to DSP |
| DSP Power | P2.7 | DSP power enable (active high) |
| LED D8 / D9 / D7 / D6 | P1.3 (muxed) | Wheel LED control |
| LED D12 | P1.4 | Wheel LED |
| LED D10 | P1.5 | Wheel LED |
| LED D11 | P1.6 | Wheel LED |
| LED D13 | P1.7 | Wheel LED |

### ⚡ Clock Configuration

- **ACLK** — sourced from VLO (Very Low-power Oscillator), divided by 1
- **UART** — initialized at **9600 bps**, then switched to **19200 bps** after DSP boot
- **Timer A** — used for delays and UART timeout watchdog

---

## 💻 Software Requirements

| Tool | Version | Notes |
|------|---------|-------|
| **Code Composer Studio (CCS)** | v4 or later | Primary IDE |
| **MSP430 GCC / TI Compiler** | Included with CCS | C compiler for MSP430 |
| **MSP430 DriverLib / driverlib** | Included with CCS | MSP430G2553 device support |
| **TI Capacitive Touch Library** | Included in repo | `CapacitiveTouchLibrary/` |
| **APRF "Raga" DSP firmware** | Separate package | Must be flashed to C55x DSP |

> ⚠️ The DSP-side firmware (APRF / "Raga") is **not** included in this repository. It must be obtained separately from [ti.com/audioboosterpack](https://www.ti.com/audioboosterpack) ❌ and flashed to the C55x DSP on the BoosterPack.

---

## 📁 Project Structure

```
ACTBP_Host_App/                  ← Project root
│
├── ACTBP_Host_App.c             # Main application — init, state machine, LED control
├── ACTBP_HostVars.h             # Global variables, state enums, context struct, display defines
├── C55_APRF_UIF.h               # UART interface definitions for APRF (virtual register map)
│
├── ACTBP_capinput.c/.h          # Capacitive touch sensing, gesture & event detection
├── ACTBP_uart.c/.h              # Hardware UART ISRs and APRF communication APIs
├── ACTBP_timer.c/.h             # Timer ISRs and UART timeout/reset mechanism
├── ACTBP_filesys.c/.h           # File system navigation commands (CD, next/prev dir/file)
├── ACTBP_display.c/.h           # OLED display command wrappers (scroll, print, screen set)
├── ACTBP_test.c                 # Initial hardware test/validation code
│
├── CapacitiveTouchLibrary/      # TI Capacitive Touch Library
│   ├── CTS_HAL.c/.h             # Hardware abstraction layer for cap touch
│   ├── CTS_Layer.c/.h           # Cap touch measurement layer
│   └── structure.c/.h           # Sensor structure — calibrated for this hardware
│
├── CCS/                         # CCS IDE project configuration files
│   ├── .ccsproject
│   ├── .cdtbuild
│   ├── .cdtproject
│   ├── .project                 # Linked resource paths (portable project)
│   ├── lnk_msp430g2553.cmd      # Linker command file for MSP430G2553
│   ├── macros.ini               # Defines PROJECT_ROOT for portable paths
│   └── MSP430G2553.ccxml        # Target configuration
│
└── README.md                    # This file
```

### Module Responsibilities

| Module | Responsibility |
|--------|---------------|
| `ACTBP_Host_App.c` | Main loop, hardware init, LED startup sequence, top-level state machine dispatch |
| `ACTBP_capinput` | Reads capacitive touch wheel, detects gestures (scroll, tap, hold) and maps them to events |
| `ACTBP_uart` | UART init at 9600/19200 bps, `uif_writeScalar`, `uif_writeArray`, `uif_readScalar` APIs |
| `ACTBP_timer` | Timer A ISR for delays and UART communication timeout watchdog |
| `ACTBP_filesys` | Sends CD, DIR, NEXTF/PREVF/NEXTD/PREVD commands to APRF; updates context counts |
| `ACTBP_display` | Sends OLED commands to APRF: set cursor, virtual plane, horizontal scroll, print strings |
| `CTS_HAL / CTS_Layer` | Low-level capacitive sensing measurement using MSP430 timer-based RC charging |
| `structure` | Defines and calibrates the specific sensor electrodes on this BoosterPack |

---

## 🔨 Building the Project

### Prerequisites

1. Install **Code Composer Studio** from [ti.com/tool/CCSTUDIO](https://www.ti.com/tool/CCSTUDIO) ✅
2. During CCS installation, ensure the **MSP430** device support package is selected
3. Connect the LaunchPad with the ACTBP attached via USB

### Build Steps (CCS)

```
1. Open CCS
2. Create or select a workspace OUTSIDE the project folder
3. Go to:  Project → Import CCS Projects
4. Browse to:  <project_root>/CCS/
5. Select the project and click Finish
6. Build:  Project → Build All  (or Ctrl+B)
7. Flash:  Run → Debug  (or F11)
```

> 📝 **Note on portability:** The `macros.ini` file defines `PROJECT_ROOT` so that all source files are linked as relative paths. The CCS workspace must be separate from the project folder for this to work correctly.

### Build Configuration

| Setting | Value |
|---------|-------|
| Target device | MSP430G2553 |
| Compiler | TI MSP430 C Compiler |
| Optimization | As configured in `.cdtbuild` |
| Linker script | `CCS/lnk_msp430g2553.cmd` |

---

## 🎮 Controls & Gestures

The capacitive touch wheel supports the following gestures mapped to application events:

| Gesture | Event | Action (context-dependent) |
|---------|-------|---------------------------|
| Scroll clockwise | `SCROLL_RIGHT` | Next directory / Next file / Volume up |
| Scroll counter-clockwise | `SCROLL_LEFT` | Previous directory / Previous file / Volume down |
| Center tap | `MID` | Select directory / Play file / Pause/Resume |
| Center hold | `MID_HOLD` | Stop playback |
| Top tap | `UP` | Go up (Browse Dir → Browse File) / Shuffle toggle |
| Top hold | `UP_HOLD` | Power off |
| Right tap | `RIGHT` | Skip forward one file |
| Right hold | `RIGHT_HOLD` | Fast forward |
| Left tap | `LEFT` | Restart current file |
| Left double-tap | `LEFTx2` | Skip back one file |
| Left hold | `LEFT_HOLD` | Rewind |
| Bottom hold | `DOWN_HOLD` | Start recording |
| Bottom double-tap | `DOWNx2` | Enable USB Mass Storage (if cable connected) |

---

## 🔄 State Machine

The application runs a finite state machine with the following states:

```
PWR_OFF ──boot──► BROWSE_DIR ◄──UP──── BROWSE_FILE
                      │                     │
                   MID (CD)              MID (Play)
                      │                     │
                      └──────────────────► PLAY ◄──► PAUSE
                                            │
                                    RIGHT_HOLD / LEFT_HOLD
                                            │
                                        FF / RWD
                                            │
                                    DOWN_HOLD (from BROWSE_FILE)
                                            │
                                         RECORD ◄──► REC_PAUSE
                                            │
                                    DOWNx2 (USB cable present)
                                            │
                                         USB_MSC
                                            │
                                    UP_HOLD (any state)
                                            │
                                         PWR_OFF
```

---

## ⚠️ Known Issues

1. **Directory skip after recording** — After completing a recording, browsing directories may cause the OLED display to skip one directory entry.
2. **Sleep ACK ignored** — The host application does not process the ACK response for the `UIF_CMD_SLEEP` command.

---

## 📝 Changelog

### v1.1 — April 2012
- 🐛 Fixed fast-forward/rewind when playback is paused (was causing UART sync loss with DSP)
- 🐛 Corrected LED (diode) placement documentation and updated `#defines` accordingly
- 🐛 Fixed CCS project targeting wrong device (was MSP430G2533, now correctly MSP430G2553)

### v1.0 — February 2012
- 🎉 Initial release for MSP430G2553 on LaunchPad with the Audio Capacitive Touch BoosterPack

---

## 📄 License

Copyright © 2011–2012 Texas Instruments Incorporated — [ti.com](https://www.ti.com) ✅

Redistribution and use in source and binary forms, with or without modification, are permitted under the **BSD 3-Clause License** provided that the copyright notice, conditions list, and disclaimer are retained in all copies. See individual source files for the full license text.

---

## 🔗 Resources

- 📁 [docs/](docs/README.md) — Official TI documentation index (datasheets, user guides, reference design)
- 📡 [C5000 UART Protocol Specification](C5000_protocol.md) — Complete protocol documentation
- 🌐 [TI Audio BoosterPack product page](https://www.ti.com/audioboosterpack) ❌
- 💬 [ACTBP E2E support thread](https://e2e.ti.com/support/processors-group/processors/f/processors-forum/188254/audio-capacitive-touch-booster-pack-software) ✅
- 📖 [MSP430G2553 datasheet](https://www.ti.com/product/MSP430G2553) ✅
- 🛠️ [Code Composer Studio](https://www.ti.com/tool/CCSTUDIO) ✅
- 📦 [MSP430 LaunchPad (MSP-EXP430G2)](https://www.ti.com/tool/MSP-EXP430G2) ✅
- 🎵 [TI Capacitive Touch Library](https://www.ti.com/tool/CAPSENSELIBRARY) ❌
