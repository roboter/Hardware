# Wiring — STLink

- Connections:
  - SWD: SWCLK, SWDIO, GND, V target (VTref) — connect VTref to detect the target voltage.
  - For JTAG: TCK/TMS/TDI/TDO, RESET, etc.
- Power:
  - Do not power the target from the ST-Link unless the device supports it and you are certain of voltage levels. Prefer shared ground and separate power supply where possible.
- Safety:
  - Verify VTref to avoid damaging the target device with mismatched voltage levels.