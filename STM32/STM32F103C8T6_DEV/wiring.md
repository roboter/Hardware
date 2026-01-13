# STM32F103C8T6 Black Board Wiring and Programming

## Programming and Debugging
- **ST-Link (SWD)**: Recommended for debugging. Connect GND, SWDIO, SWCLK, and 3.3V.
- **Maple DFU**: The board may appear as "Maple DFU" when connected via USB. Use the Maple bootloader for USB uploads.

## On-board Peripherals
- **User LED**: PA1 (Active Low).
- **User Button**: PA8.
- **External Flash**: Winbond W25X16 (SPI).
- **EEPROM**: Atmel 24C04N (I2C).
- **SD Card**: TF Card slot (SPI).
- **Headers**:
    - **WiFi**: ESP8266 header (UART).
    - **RF**: nRF24L01 header (SPI).
    - **Ethernet**: W5500 header.

## Suggested Display Connection
Commonly used with small SPI/I2C OLEDs or LCDs:
- **SCL**: PB3
- **SDA**: PB5
- **RES**: PB7
- **DC**: PB9
- **BLK**: PB11

## Power
- **Micro USB**: Power and data.
- **3.3V/GND Pins**: Direct power input (ensure regulated 3.3V).

## Pinout and Schematic
- [Original Schematic (PDF)](original-schematic-STM32F103C8T6-Black_Board.pdf)
- [Schematic Image](schematic_translated.png)
