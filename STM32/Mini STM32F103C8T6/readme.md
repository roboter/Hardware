## Introduction
MINI32 designs and manufactures core boards based on STM32F103C8T6, with a focus on small volume and TYPE-C ports
Data transmission (either serial port or USB), MINI32 can download programs through the onboard serial port. Small volume is the same as
Lead out all IO ports on both sides of the needle row, and separately lead out the SWD download port (both sides of the needle row IO ports are simultaneously led out)
Applicable to small volume control schemes.

TYPE-C: Choose between power input and USB/serial port (CH340N).
Key: RST (reset button), BTO (BOOT mode selection button).
LED: PWR (POWER power indicator), C13 (user control indicator), PC13 control LED negative Extreme.

Note: PIN TO PIN pin compatible chips are applicable to this core board, not limited to a single MCU, for exampleExamples include GD32F103C8T6, CH32F103C8T6, AT32F103C8T6, etc. Please do your best when conditions permit Use domestically produced MCU for quantity.

PCB external dimensions (excluding SWD download port): 25.40 * 22.86mm (100mil=2.54mm);
PIN spacing: 2.54mm;
The distance between the needle rows on both sides: 15.24mm (600mil) on the inner side and 20.32mm (800mil) on the outer side.

About TYPE-C port function selection
The core board pursues a small size with a single TYPE-C port design, and the USB and serial port functions are optional and mutually exclusive Excluding design, when welding U2 (CH340N) and not welding R4 and R5, the C port is used as a serial communication function,When welding R4 and R5 without welding U2 (CH340N), the C port is used as a USB communication function.
About the Hardware Design of TYPE-C Port CC Port
Both CC1 and CC2 pins are suspended: only the USBA to TYPE-C data cable can be used for power supply.
Short circuit CC1 and CC2 pins and pull down 5.1K resistor: use fast charging power supply and EMARK core simultaneously
The dual C-port data cable of the chip will not be powered, and all other configurations can be powered normally.
CC1 and CC2 pins pull down 5.1K resistors respectively: standard design, both can be powered, recommended for use.
Note: Actual design needs to consider factors such as PCB layout, usage scenarios, and costs. Please design according to your needs.

About Serial Port Download
Enter BOOT mode:
Hot entry: Press and hold the reset and BOOT buttons simultaneously, first release the reset button for about 1 second, then release the BOOT button
Press the button to enter BOOT download mode.
Cold entry: Press and hold the BOOT button, then connect the USB power for about 1 second, then release the BOOT button to enter
BOOT download mode.

## Wiring

See `wiring.md` for BOOT/RST and Type-C configuration notes.
STM32/CH32 serial port download interface:
