# Lolin C3 Pico Wiring and Programming

The Lolin C3 Pico is a compact ESP32-C3 board compatible with LOLIN D1 mini shields.

## Board Features
- **MCU**: ESP32-C3 (RISC-V Single-Core, 160MHz)
- **USB**: USB-C connector.
- **RGB LED**: WS2812B connected to **GPIO7**.
- **I2C Port**: LOLIN I2C port (SH1.0-4P).
- **Battery**: Port with 500mA charging circuit.

## Programming
- **Interface**: USB-C (Native USB).
- **Mode**: Default firmware is MicroPython. For Arduino/ESP-IDF, use standard C3 upload methods.
- **Enter Bootloader Mode**: 
    1. Connect to PC via USB.
    2. Hold the **BOOT** (usually IO9, may require a jumper or button depending on revision).
    3. Press/Cycle **RESET**.

## Pinout
Refer to the high-resolution pinout diagram:
- [Lolin C3 Pico Pinout](WeMos-LOLIN-ESP32-C3-pico-pinout-high.png)

## On-board Peripheral Pins
- **RGB LED (WS2812B)**: GPIO7
- **I2C (LOLIN Port)**: 
    - SDA: IO8
    - SCL: IO10

## Links
- [Lolin C3 Pico Official Documentation](https://www.wemos.cc/en/latest/c3/c3_pico.html)
