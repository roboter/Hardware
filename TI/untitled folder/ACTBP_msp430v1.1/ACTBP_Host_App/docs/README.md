# 📚 Official Documentation — 430BOOST-C55AUDIO1

This folder collects all official TI documentation relevant to the **Audio Capacitive Touch BoosterPack (430BOOST-C55AUDIO1)** and its components.

> ⚠️ The original product page (`ti.com/audioboosterpack`) and the dedicated board user guide have been removed from TI's servers — this product is discontinued. The documents below are the closest official references available.

---

## 🗂️ Document Index

### 🎛️ Board & Reference Design

| Document | Description | Link | Status |
|----------|-------------|------|--------|
| **TIDM-LPBP-TCHMP3PLAYER** | Official TI reference design page for the 430BOOST-C55AUDIO1 — MP3 encoder/decoder with capacitive touch, OLED, SD card, USB MSC | [ti.com/tool/TIDM-LPBP-TCHMP3PLAYER](https://www.ti.com/tool/TIDM-LPBP-TCHMP3PLAYER) | ✅ |
| **E2E Support Thread** | Community support thread for the ACTBP — software, init issues, UART commands | [e2e.ti.com ACTBP thread](https://e2e.ti.com/support/processors-group/processors/f/processors-forum/188254/audio-capacitive-touch-booster-pack-software) | ✅ |
| **DigiKey Product Page** | Product listing with part number 430BOOST-C55AUDIO1 | [digikey.com/430BOOST-C55AUDIO1](https://www.digikey.com/en/products/detail/texas-instruments/430BOOST-C55AUDIO1/3139308) | ✅ |
| **Product Announcement** | Original press release describing the board features | [prnewswire.com](https://www.prnewswire.com/news-releases/add-crystal-clear-audio-to-microcontroller-based-applications-with-tis-new-audio-capacitive-touch-boosterpack-for-ultra-low-power-msp430-microcontrollers-144375925.html) | ✅ |

---

### 🔲 MSP430G2553 — Host Microcontroller

| Document | TI Lit # | Description | Link | Status |
|----------|----------|-------------|------|--------|
| **MSP430G2553 Datasheet** | SLAS735J | Mixed Signal Microcontroller — pinout, electrical specs, peripherals | [PDF](https://www.ti.com/lit/ds/slas735j/slas735j.pdf) | ✅ |
| **MSP430G2553 Product Page** | — | Full product page with all documents | [ti.com/product/MSP430G2553](https://www.ti.com/product/MSP430G2553) | ✅ |
| **MSP430x2xx Family User's Guide** | SLAU144K | Complete peripheral reference — USCI/UART, Timer A, clocks, ADC, GPIO | [PDF](https://www.ti.com/lit/ug/slau144k/slau144k.pdf) | ✅ |
| **MSP430 LaunchPad (MSP-EXP430G2)** | — | Development kit product page | [ti.com/tool/MSP-EXP430G2](https://www.ti.com/tool/MSP-EXP430G2) | ✅ |

---

### 🎵 TMS320C5535 — DSP (Audio Engine)

| Document | TI Lit # | Description | Link | Status |
|----------|----------|-------------|------|--------|
| **TMS320C5535 Datasheet** | SPRS543C | C55x Fixed-Point DSP — 100 MHz, USB, LCD, FFT HWA, SAR ADC | [PDF](https://www.ti.com/lit/ds/symlink/tms320c5535.pdf) | ✅ |
| **TMS320C5535 Product Page** | — | Full product page with all documents | [ti.com/product/TMS320C5535](https://www.ti.com/product/TMS320C5535) | ✅ |

---

### 🔊 TLV320AIC3204 — Audio Codec

| Document | TI Lit # | Description | Link | Status |
|----------|----------|-------------|------|--------|
| **TLV320AIC3204 Datasheet** | SLOS602 | Ultra-low-power stereo audio codec — I2S, 192kHz, programmable DSP | [PDF](https://www.ti.com/lit/ds/symlink/tlv320aic3204.pdf) | ✅ |
| **TLV320AIC3204 Product Page** | — | Full product page | [ti.com/product/TLV320AIC3204](https://www.ti.com/product/TLV320AIC3204) | ✅ |

---

### 👆 Capacitive Touch

| Document | TI Lit # | Description | Link | Status |
|----------|----------|-------------|------|--------|
| **430BOOST-SENSE1 User's Guide** | SLAU337A | User guide for the capacitive touch BoosterPack for LaunchPad — same cap touch library used in ACTBP | [manualslib.com mirror](https://www.manualslib.com/manual/1384247/Texas-Instruments-430boost-Sense1.html) | ✅ |
| **Capacitive Touch Library (SLAA363)** | SLAA363A | Original MSP430 cap touch library application note — sensor design, RC oscillator method | ❌ removed from ti.com | ❌ |
| **CapTIvate Design Center** | — | Current TI cap touch tooling (successor to the original library) | [ti.com/tool/MSPCAPTDSNCTR](https://www.ti.com/tool/MSPCAPTDSNCTR) | ✅ |

---

## 📋 Key Document Summary

### What each document covers for this project

```
430BOOST-C55AUDIO1 Board
├── TIDM-LPBP-TCHMP3PLAYER  ← System overview, block diagram, BOM
├── MSP430G2553 Datasheet   ← MCU pinout, UART/USCI registers, timer registers
├── MSP430x2xx User's Guide ← USCI UART config, Timer_A ISR, clock setup (ACLK/VLO)
├── TMS320C5535 Datasheet   ← DSP specs, USB, SD card interface
├── TLV320AIC3204 Datasheet ← Codec I2S interface, sample rates, register map
└── 430BOOST-SENSE1 Guide   ← Cap touch wheel/button hardware design reference
```

### UART Protocol Documents

The UART protocol between MSP430 and C5535 is proprietary to the APRF "Raga" firmware and is **not covered in any public TI document**. The full protocol has been reverse-engineered from the source code and documented in:

- 📄 [`../C5000_protocol.md`](../C5000_protocol.md) — Complete UIF protocol specification

---

## 🔗 Additional Resources

- [C55x Connected Audio Framework](https://software-dl.ti.com/dsps/dsps_public_sw/c5000/C55_Connected_Audio_Framework/usb/latest/index_FDS.html) — DSP-side audio framework (requires TI account)
- [MSP430 LaunchPad Getting Started](https://www.ti.com/tool/MSP-EXP430G2) — LaunchPad hardware guide
- [Code Composer Studio](https://www.ti.com/tool/CCSTUDIO) ✅ — IDE used to build this project
- [E2E: ACTBP Initialisation Problem](https://e2e.ti.com/support/processors-group/processors/f/processors-forum/193275/audio-capacitve-touch-boosterpack-430boost-c55audio1-initialisation-problem) ✅ — Useful troubleshooting thread
- [E2E: ACTBP with Stellaris LaunchPad](https://e2e.ti.com/support/processors-group/processors/f/processors-forum/252433/actbp-with-stellaris-launchpad-lm4f120) ✅ — Porting discussion with UART API details
