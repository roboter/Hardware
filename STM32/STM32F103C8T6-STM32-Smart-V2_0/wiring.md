# STM32 Smart V2.0 Wiring and Programming

## Programming and Debugging
- **ST-Link v2 (SWD)**: Connect GND, SWDIO, and SWCLK. 
- **Important**: When using ST-Link, provide power separately from the USB port, or ensure the power jumper is correctly configured.

## Display (MCUDEV_TFT1.44 / ST7735S)
The board features an "OLED" header specifically for small displays. 

### Display Pinout
| Header Pin | Label | Function | MCU Pin | Note |
| --- | --- | --- | --- | --- |
| 1 | VCC | 3.3V | +3.3V | |
| 2 | GND | Ground | GND | |
| 3 | DIN | MOSI | PB15 | |
| 4 | CLK | SCK | PB13 | |
| 5 | CS | Chip Select | PB12 | |
| 6 | RST | Reset | NRST | See Reset Note below |
| 7 | DC | Data/Cmd | PB1 | |
| 8 | BLK | Backlight | N.C. | |

### Reset Note
There is a known issue where the display may only initialize correctly if the reset is triggered via the ST-Link or a specific power-on sequence.

## SWO Button
- The board may have a button connected for SWO or user use. Refer to `swo.c` and [SWO button.png](SWO button.png) for details.

## Links
- [STM32-base: STM32 Smart V2.0](https://stm32-base.org/boards/STM32F103C8T6-STM32-Smart-V2.0)
