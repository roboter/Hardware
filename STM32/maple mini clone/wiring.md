# Maple Mini (Clone) Wiring and Programming

## Programming and Debugging
- **USB DFU**: The board typically comes with a Maple bootloader. 
    1. Connect via Mini-USB.
    2. Reset the board and quickly attempt to upload via DFU.
    3. Note: If "No DFU capable USB device available" occurs, you may need to reinstall the bootloader or check drivers.
- **SWD**: Connect an ST-Link to the SWD pins for direct programming and debugging.

## Bootloader
- A backup of the bootloader is available in this folder: [maple_mini_boot20.bin](maple_mini_boot20.bin).

## Pinout
Refer to the provided pinout diagrams:
- [Maple Mini Pinout (SVG/PNG)](921px-Maple_Mini_Pinout.svg.png)
- [Maple Mini Pinout (Detailed)](maplemini_pinout.png)

## Schematic
- [Board Schematic](file_id_2060.jpeg)

## Power Supply
- Power via the Mini-USB connector or the Vin pin.
