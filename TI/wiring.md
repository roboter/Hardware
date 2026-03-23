# Wiring — TI LaunchPad (MSP430) Overview

## Power
- **MSP-EXP430G2 LaunchPad**: USB-powered (5V via USB connector)
- **Target Voltage**: 3.3V (regulated onboard)
- **Power LED**: Indicates when board is powered
- **External Power**: Can be powered via external supply if needed (check board specifications)

## Programming & Debugging
- **Onboard Programming**: Built-in USB-to-serial converter for programming
- **Debug Interface**: Spy-Bi-Wire (2-wire JTAG) - uses minimal pins
- **No External Programmer Required**: The LaunchPad includes all necessary programming hardware
- **Connectors**: USB micro-B connector for both power and programming

## Pin Configuration
- **20-pin Header**: Standard LaunchPad pinout for easy expansion
- **BoosterPack Compatible**: Compatible with TI BoosterPack expansion modules
- **GPIO**: Most pins are available for user applications
- **Voltage Levels**: All I/O pins are 3.3V logic level

## Safety
- Verify voltage levels (3.3V logic) before connecting external peripherals
- Use current-limited supplies for initial testing
- Check pin assignments before connecting external components
- MSP430 operates at 1.8V to 3.6V - ensure power supply is within range

## BoosterPack Expansion
- **Audio Capacitive Touch BoosterPack**: Included in this directory
- **Connector**: Standard BoosterPack connector for easy module attachment
- **Power**: BoosterPacks are powered from the LaunchPad
