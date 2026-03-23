# TI (Texas Instruments)

This directory contains Texas Instruments microcontroller development boards and documentation.

See [wiring.md](wiring.md) for general TI LaunchPad wiring and programming notes.

## Contents

### LaunchPad MSP-EXP430G2
MSP430 LaunchPad development board featuring:
- Audio Capacitive Touch BoosterPack
- Microcontroller: MSP430G2553

<br/><img src="LaunchPadMSP430G2452-v1.5.jpg" alt="MSP-EXP430G2 LaunchPad" width="256">

## MSP430G2553 Microcontroller - Complete Feature Summary

### Core Specifications
- **Architecture**: 16-bit RISC
- **Supply Voltage Range**: 1.8V to 3.6V
- **Instruction Cycle Time**: 62.5 ns
- **Operating Temperature**: -40°C to +85°C
- **Wakeup Time**: < 1 µs from standby

### Memory
- **Flash Memory**: 16KB
- **RAM**: 512B

### Power Management
- **Power Modes**: 5 low-power modes (LPM0 to LPM4)
- **Ultra-Low Power**: <1 µA in LPM4 (RAM retention)
- **Brownout Detector**: Integrated power protection
- **Design Focus**: Extended battery life for portable systems

### Clock System
- **Frequency Range**: 32kHz (low) to 16MHz (high)
- **Clock Sources**:
  - ACLK (Auxiliary Clock)
  - SMCLK (Sub-Main Clock)
  - MCLK (Main Clock)
  - DCO (Digitally-Controlled Oscillator)
- **Flexibility**: Both fixed and programmable clocks available

### Peripherals & Interfaces
- **ADC**: 10-bit Analog-to-Digital Converter
- **Timers**: Two 16-bit timers
- **Communication**: Universal Serial Communication Interface (USCI)
- **Protocol Support**: UART, SPI, I2C
- **I/O Pins**: 24 pins with interrupt capability

### Programming & Debugging
- **Programming**: Onboard serial programming
- **Debug Interface**: Spy-Bi-Wire (2-wire JTAG)
- **Security**: Fuse-protected program code
- **Development**: No external programming hardware needed

### Packaging Options
- 20-pin TSSOP (Thin Shrink Small Outline Package)
- 20-pin PDIP (Plastic Dual Inline Package)
- 28-pin TSSOP
- 32-pin QFP (Quad Flat Package)

### Operating Modes Detail

| Mode | CPU | ACLK | SMCLK | MCLK | DCO | Description |
|------|-----|------|-------|------|-----|-------------|
| Active | Enabled | Enabled | Enabled | Enabled | Enabled | Full operation |
| LPM0 | Disabled | Enabled | Enabled | Disabled | Enabled | Low power with peripherals |
| LPM1 | Disabled | Enabled | Enabled | Disabled | Disabled | Lower power than LPM0 |
| LPM2 | Disabled | Enabled | Disabled | Disabled | Enabled | ACLK only with DCO |
| LPM3 | Disabled | Enabled | Disabled | Disabled | Disabled | ACLK only (typical standby) |
| LPM4 | Disabled | Disabled | Disabled | Disabled | Disabled | Lowest power (RAM retention) |

### Typical Applications
- Medical devices and portable medical equipment
- Battery-powered sensor systems
- Data acquisition and signal processing
- Digital display and user interface control
- Portable instrumentation
- Low-power embedded controls

### Key Advantages
1. **Ultra-Low Power Consumption**: Optimized for battery operation
2. **Fast Operation**: 62.5 ns instruction cycle at 16MHz
3. **Cost-Effective**: Budget-friendly for volume production
4. **Integrated Peripherals**: Reduces external component count
5. **Flexible Clocking**: Multiple clock sources and configurations
6. **Easy Development**: On-chip programming and debugging
7. **Reliable Operation**: Brownout protection and wide voltage range

### Development Resources
- Official MSP430G2553 datasheet from Texas Instruments
- CAD models available from component libraries (like Ultra Librarian)
- Development kits and evaluation modules
- Code examples and application notes from TI

### Important Notes for Designers
1. Always reference the official Texas Instruments datasheet
2. Adhere to absolute maximum ratings to prevent damage
3. Implement proper power sequencing
4. Consider EMI/EMC requirements in layout
5. Test all power modes during validation
6. Verify ADC performance for precision applications

### Documentation
- MSP-EXP430G2 LaunchPad™ Development Kit User Guide
- MSP430G2553 Mixed Signal Microcontroller datasheet
