# Wiring — GD32VF103 boards

- Power: Typical development boards use 3.3V; verify the board regulator and supply accordingly.
- Programming/Debugging: Use GD-Link, JTAG, or SWD (see `GD-Link Programmer` and `gd32vf103_jtag.cfg`).
- Pins: Refer to `GD32VF103_Datasheet_Rev1.5.pdf` and `GD32VF103_Firmware_Library_User_Guide_V1.0.pdf` included in this folder.
- Safety: Verify voltage rails and do not apply 5V to I/O lines on 3.3V boards.

> Note: For RISC-V specific toolchains and examples, refer to the included demo suites and e-book.