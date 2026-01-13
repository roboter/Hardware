# STM8F407VET6 Black Board Wiring and Programming

## Power Supply
- **Mini USB**: Power the board via the Mini USB connector.
- **3.3V LDO**: The board includes an on-board regulator.
- **Battery**: CR1220 socket for RTC power.

## Programming and Debugging
- **JTAG/SWD**: Use an ST-Link or J-Link connected to the 20-pin JTAG/SWD header.
- **ISP**: 4-pin ISP header available for serial programming.

## On-board Peripherals
- **User LEDs**: 
    - D2: PA6 (Active Low)
    - D3: PA7 (Active Low)
- **User Buttons**:
    - K0: PE4
    - K1: PE3
    - Wakeup: PA0
- **Storage**: Micro SD slot (SDIO).
- **Flash**: Winbond W25Q16 (SPI Flash).
- **Wireless**: NRF24L01 socket.
- **Display**: 2x16 FMSC LCD interface.

## Pinout
Refer to the schematics and images in this folder for the full 100-pin mapping and header layouts.
- [stm32f407vet6_black_sch.pdf](stm32f407vet6_black_sch.pdf)
- [stm32f407vet6_view01.jpg](stm32f407vet6_view01.jpg)
