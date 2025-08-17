# STM32H750_LED Project

## Description
Simple LED blinking project for STM32H750VBT6 development board.

## Features
- LED connected to PC13 (GPIOC, Pin 13)
- LED blinks every 500ms
- Simple GPIO configuration
- Clean, minimal code structure

## Hardware Setup
- Connect LED to PC13 pin
- Use appropriate current limiting resistor
- Ensure proper power supply

## Code Structure
- **main.c**: Main application with LED control logic
- **gpio.c**: GPIO configuration for LED pin
- **main.h**: Header file with function declarations

## Build and Debug
- Open project in STM32CubeIDE
- Build using Debug or Release configuration
- Use ST-Link debugger for programming and debugging

## Expected Behavior
- LED should blink on and off every 500ms
- No additional functionality - pure LED demonstration