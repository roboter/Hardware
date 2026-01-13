# STM32WB55 Wiring and Programming

## Nucleo-64 Board (MB1355)
- **Programming**: Integrated ST-LINK/V2-1 via Micro-USB. 
- **Power**: 
    - USB (5V)
    - External E5V (7V-12V)
    - Arduino headers (3.3V or 5V)
- **User LEDs**: LD1 (Blue), LD2 (Green), LD3 (Red). 
    - PB5 (Blue), PB0 (Green), PB1 (Red)
- **User Buttons**: SW1, SW2, SW3.
    - SW1 (PC4), SW2 (PD0), SW3 (PD1)

## USB Dongle (MB1293)
- **Programming**: 
    - USB DFU bootloader.
    - External SWD via smaller header (requires adapter or fine wires).
- **User LEDs**: LD1 (Green), LD2 (Red/Blue).
- **User Switch**: SW1 (User/Reset).

## Wireless Setup
The STM32WB requires a wireless stack to be loaded into the Cortex-M0+ core using **STM32CubeProgrammer** (FUS and Wireless Stack update).
Refer to [um2435](um2435-bluetooth-low-energy-and-802154-nucleo-pack-based-on-stm32wb-series-microcontrollers-stmicroelectronics.pdf) for detailed procedures.
