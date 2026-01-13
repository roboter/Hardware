# STM32F429 Discovery Wiring and Programming

## Board Overview
The STM32F429 Discovery kit (32F429IDISCOVERY) features an STM32F429ZIT6 MCU with a 2.4" QVGA TFT LCD.

## Power Supply
- **Mini-USB**: Power via the ST-LINK Mini-USB connector.
- **External**: Can be powered via the 5V and 3V pins on headers (be careful with polarity).

## Programming and Debugging
- **On-board ST-LINK/V2-B**: Connect via Mini-USB to program and debug.
- **External Header**: Can be used as a standalone ST-LINK to program other boards by removing jumpers J3.

## On-board Peripherals
- **LCD**: 2.4" QVGA TFT LCD.
- **SDRAM**: 64 Mbits.
- **Gyroscope**: L3GD20 (on SPI).
- **User LEDs**: 
    - LD3 (Green): PG13
    - LD4 (Red): PG14
- **User Button**: PA0 (Blue Button).

## Pinout
Refer to the official user manual for full header pinouts:
- [um1670-discovery-kit-with-stm32f429zi-mcu.pdf](um1670-discovery-kit-with-stm32f429zi-mcu-stmicroelectronics.pdf)
- [STM32F4DISCO-Block-diagram.jpg](STM32F4DISCO-Block-diagram.jpg)
