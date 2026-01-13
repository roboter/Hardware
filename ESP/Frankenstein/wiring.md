# Frankenstein (ESP-12E) Wiring and Programming

## Programming
- **Interface**: Uses an external USB-to-Serial adapter (similar to ESP-01).
- **Boot Mode**: 
    - Hold **BOOT0** button (if available) or pull GPIO0 to GND.
    - Perform a **RESET**.
- **Successful Upload**: Once "Hard resetting via RTS pin..." appears, you may need to reset the board manually.

## On-board LEDs
- **LED_BUILTIN**: Typically Blue LED on the ESP-12E/ESP-01 module (GPIO2).
- **D13**: Some "frankenstein" boards might have an additional LED on a pin labeled 13.

## External Display (TM1637)
Commonly used with a 7-segment display:
- **CLK**: D6 (GPIO12)
- **DIO**: D5 (GPIO14)

## Pinout
Refer to the following images for ESP-12E details:
- [ESP-12E Pinout](ESP12E_Pinouts-800x800.jpg)
- [Schematic Snippet 1](AE0711203405-48.png)
- [Schematic Snippet 2](AE0711203405-49.png)
