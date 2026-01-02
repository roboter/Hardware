# Wiring — HW-260 ATTiny 8-pin dev board

- Power:
  - Most simple 8-pin ATTiny dev boards operate at 5V; check silkscreen and regulator if present.
- ISP / Programming:
  - Board includes ISP programming header — use an AVR ISP or Arduino as ISP to program the chip.
  - Typical ISP pins: MISO, MOSI, SCK, RESET, VCC, GND — confirm header labeling.
- Safety:
  - When programming, ensure target VCC is the same as the programmer voltage to avoid damaging the programmer or target.

> Note: See example `blink/` project in this folder for a simple test program.