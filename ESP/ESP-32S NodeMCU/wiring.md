# ESP-32S NodeMCU (WROOM-32) Wiring and Programming

This board is a common ESP32 development board (DevKit V1 style) based on the ESP-WROOM-32 module.

## Programming
- **Interface**: Integrated Micro-USB port (typically uses CP2102 or CH340 serial bridge).
- **Auto-Boot**: The board usually has an auto-reset circuit.
- **Manual Boot Mode**: If auto-upload fails:
    1. Hold the **BOOT** button.
    2. Start the upload in your IDE.
    3. Release **BOOT** when the upload begins.

## Pinout
Refer to the following images for detailed pin mappings:
- [ESP32 Devkit Pinout (High Res)](ESP32-Devkit-Pinout-Rev-12-4000p.png)
- [30-pin DevKit Pinout](esp32-wroom-wifi-devkit-v1_pinout_30.png)

## On-board Peripherals
- **User LED**: Typically GPIO2.
- **BOOT Button**: GPIO0.
- **EN (Reset) Button**: Resets the MCU.

## Power
- **USB**: 5V via Micro-USB.
- **Vin**: 5V external input.
- **3V3**: Regulated 3.3V output/input.
