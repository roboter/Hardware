# WeAct Black Pill Wiring and Programming

## Board Variants
- **V2.0/V3.0**: Commonly features STM32F401CEU6 or STM32F411CEU6.
- **V3.0+**: Often uses USB-C.

## Programming and Debugging
- **SWD**: Use an ST-Link or similar debugger connected to the 4-pin SWD header (GND, CLK, DIO, 3V3).
- **DFU (USB)**: 
    1. Hold **BOOT0** button.
    2. Press **RESET** button.
    3. Release **BOOT0**. 
    4. The board should now appear as a DFU device via USB-C.

## Pinout Highlights
- **User LED**: PC13 (Active Low).
- **User Button**: PA0.
- **Power**: 5V via USB-C or Vin pin; 3.3V via 3V3 pin.

## Links
- [STM32-base: WeAct Black Pill V3.0](https://stm32-base.org/boards/STM32F401CEU6-WeAct-Black-Pill-V3.0.html)
