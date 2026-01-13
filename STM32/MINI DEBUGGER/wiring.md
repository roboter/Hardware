# WeAct Mini Debugger Wiring and Usage

## Features
- **Integrated Modes**: DAPLink (HID) or ST-Link V2.1.
- **Micro-USB**: High-speed USB interface for connection to PC.
- **USB-to-UART**: Integrated serial port bridge.
- **Drag-and-Drop**: Supports drag-and-drop programming in DAPLink mode.

## Output Header Pinout
Standard 6-pin output header for target connection:

| Pin | Label | Function | Note |
| --- | --- | --- | --- |
| 1 | 3V3 | Power Out | 3.3V power to target |
| 2 | SWDIO | SWD Data | Target SWDIO |
| 3 | SWCLK | SWD Clock | Target SWCLK |
| 4 | GND | Ground | |
| 5 | RXD | UART RX | Connect to target TX |
| 6 | TXD | UART TX | Connect to target RX |

## Connection to Target
- **SWD**: Connect 3V3, GND, SWDIO, and SWCLK to the target board.
- **Serial**: Connect RXD and TXD to the target's UART pins (crossover: RX->TX, TX->RX).

## Status LED
- **DAPLink Mode**: LED indicates activity and status.
- **ST-Link Mode**: LED behaves as a standard ST-Link indicator.

## Links
- [WeAct MiniDebugger GitHub](https://github.com/WeActStudio/WeActStudio.MiniDebugger)
