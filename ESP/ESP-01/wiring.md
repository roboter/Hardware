# ESP-01 Wiring and Programming

The ESP-01 is one of the smallest ESP8266 modules, often used as a serial-to-WiFi bridge or for simple standalone projects.

## Board Features
- **MCU**: ESP8266
- **Flash**: Typically 1MB (8Mbit)
- **Pins**: 8-pin 0.1" header.

## Programming
- **Interface**: External USB-to-Serial adapter (3.3V levels!).
- **Boot Mode**:
    1. Connect **GPIO0** to GND.
    2. Power/Reset the module.
- **Boot for Execution**: Disconnect **GPIO0** from GND and power/reset.

## Standard Pinout
| Pin | Label | Function | Note |
| --- | --- | --- | --- |
| 1 | GND | Ground | |
| 2 | TX | UART TX | Connect to Adapter RX |
| 3 | GPIO2 | General IO | Connected to Blue LED on most modules |
| 4 | CH_PD | Chip Enable | Connect to 3.3V to enable |
| 5 | GPIO0 | Flash Mode | Connect to GND for programming |
| 6 | RST | Reset | Pull to GND to reset |
| 7 | RX | UART RX | Connect to Adapter TX |
| 8 | VCC | 3.3V Power | **Do NOT connect to 5V!** |

## Arduino Setup
- **Board**: `Generic ESP8266 Module`
- **Flash Size**: `1M (64K SPIFFS)`
- **Flash Mode**: `DIO`
- **Reset Method**: `ck` or `nodemcu` (depending on adapter auto-reset)

## Links
- [Arduino ESP8266 GitHub](https://github.com/esp8266/Arduino)
- [ESP8266 Read the Docs](https://arduino-esp8266.readthedocs.io/en/latest/)
