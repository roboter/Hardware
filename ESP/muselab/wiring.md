# nanoESP32-C6 (Muse Lab) Wiring and Programming

## Board Features
- **MCU**: ESP32-C6-WROOM-1 (RISC-V, 160MHz)
- **USB Ports**:
    - **USB-to-TTL**: On-board serial bridge for easy debugging and programming.
    - **Native USB**: ESP32-C6's internal USB interface.
- **On-board Peripheral**: RGB LED (GPIO8).
- **Buttons**: BOOT and RST buttons for mode selection.

## Programming
- **Connection**: Use the **USB-to-TTL** port for most development.
- **Bootloader Mode**: 
    1. Hold the **BOOT** button.
    2. Press the **RST** button.
    3. Release the **BOOT** button.
- **Tooling**: Supported by ESP-IDF and PlatformIO (using `esp32-c6-devkitc-1` board definition).

## Pinout Highlights
- **RGB LED**: GPIO8
- **BOOT Button**: GPIO9 (Typically)

Refer to the diagram for full pinout:
- [Hardware Diagram](S22b1382851dd447fb99d6769ea8fa4edC.avif)
- [Specification Sheet](S8bc9a5534f704ff0b51a418b6b320441o.avif)
