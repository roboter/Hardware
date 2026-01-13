# ESP-03 Wiring and Programming

The ESP-03 is a compact ESP8266 module with a ceramic antenna and a unique pinout (smd pads).

## Programming
- **Interface**: Requires an external USB-to-Serial adapter.
- **Boot Mode**:
    1. Connect **GPIO0** to GND.
    2. Power/Reset the module.
- **Connections**:
    - **VCC**: 3.3V
    - **GND**: GND
    - **TX**: Connect to Adapter RX
    - **RX**: Connect to Adapter TX
    - **CH_PD (EN)**: Connect to 3.3V
    - **GPIO15**: Connect to GND

Refer to [PROGRAM ESP.JPG](PROGRAM ESP.JPG) for a visual wiring guide.

## Pinout
- **GPIO2**: Often used for the on-board LED (if present).
- **Ceramic Antenna**: Integrated on the module.

## Links
- [Blink ESP-03 Tutorial](http://pdacontrolen.com/blink-esp8266-03-esp-03-in-arduino-ide/)
