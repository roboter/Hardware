# ESP32-C3 Core Board Wiring and Programming

## Programming
- **USB**: Most versions have a USB-C port for programming via the internal USB-serial bridge.
- **Buttons**:
    - **BOOT**: Typically IO9.
    - **RESET**: Reset pin/button.
- To enter bootloader: Hold **BOOT (IO9)**, press **RESET**, then release **BOOT**.

## Common Pinout
| Pin | Function | Note |
| --- | --- | --- |
| IO9 | BOOT | On-board button |
| IO2 | LED | Some boards have a user LED on IO2 |
| IO8 | RGB LED | Some boards feature a WS2812 RGB LED |

## Display Wiring (Common)
If the board features an 0.42" or 0.96" OLED:
- **I2C SDA**: IO5
- **I2C SCL**: IO6
- **Reset**: IO10 (if applicable)

Refer to the board's specific silkscreen for the most accurate pin mapping.
