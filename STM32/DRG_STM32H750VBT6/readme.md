# STM32H750VBT6 Projects

This repository contains multiple STM32H750VBT6 projects with different editors/compilers:

## Project Structure

### STM32CubeIDE Projects
- **STM32H750_OV2640**: Camera OV2640 project with LCD display
- **STM32H750_Display_ADC**: ADC display project with LCD
- **STM32H750_LED**: Simple LED blinking project

### Keil Projects
- **10_OV2640**: Camera OV2640 project (working version)
- **14_DEMO**: Demo project with camera and key functionality

## Recent Fixes Applied

### 1. Code Comments and Organization
- **Fixed Chinese comments**: Converted all Chinese comments to English for better readability
- **Organized code sections**: Moved all custom code to proper `/* USER CODE BEGIN */` and `/* USER CODE END */` sections
- **Standardized headers**: Applied consistent STMicroelectronics copyright headers across all projects

### 2. STM32CubeIDE OV2640 Project Fixes
- **Added missing includes**: Added necessary includes for camera and LCD functionality in `main.h`
- **Fixed main function**: Replaced simplified LED blink code with complete camera functionality
- **Enabled MPU configuration**: Properly configured MPU for camera buffer access
- **Added function declarations**: Added missing function prototypes in header files

### 3. Camera Functionality Issues Resolved
- **Missing initialization**: Added `DCMI_OV2640_Init()` and `SPI_LCD_Init()` calls
- **Missing DMA transmission**: Added `OV2640_DMA_Transmit_Continuous()` call
- **Missing display code**: Added LCD display loop for camera frames
- **Missing MPU setup**: Configured MPU for proper memory access

### 4. Debug Configuration
- **Debug launch file**: Verified STM32CubeIDE debug configuration is properly set up
- **ST-Link settings**: Confirmed proper ST-Link configuration for debugging

## Key Differences Between Working and Non-Working Projects

### Working Keil Project (10_OV2640)
- Complete camera initialization sequence
- Proper MPU configuration
- Full DCMI and LCD setup
- DMA transmission enabled

### Previously Non-Working STM32CubeIDE Project
- Missing camera initialization calls
- Disabled MPU configuration
- Simplified main loop without camera functionality
- Missing function declarations

## How to Use

### Building and Debugging
1. **STM32CubeIDE**: Open the project and build using the IDE
2. **Keil**: Open the `.uvprojx` file and build using Keil MDK
3. **Debugging**: Use ST-Link debugger with proper configuration

### Camera Setup
1. Ensure OV2640 camera module is properly connected
2. Check DCMI pin connections
3. Verify LCD display connections
4. Configure MPU for camera buffer access

## Troubleshooting

### Common Issues
- **Camera not working**: Check DCMI initialization and MPU configuration
- **Debug not starting**: Verify ST-Link connection and debug configuration
- **Build errors**: Ensure all required includes are present

### Debug Configuration
- Verify ST-Link is properly connected
- Check debug launch configuration in STM32CubeIDE
- Ensure proper target selection (STM32H750VBTx)

## Project Status

- ✅ **Keil 10_OV2640**: Fully functional camera project
- ✅ **Keil 14_DEMO**: Working demo project
- ✅ **STM32CubeIDE OV2640**: Fixed and functional
- ✅ **STM32CubeIDE Display_ADC**: Basic ADC display project
- ✅ **STM32CubeIDE LED**: Simple LED project

All projects now have:
- Proper English comments
- Organized code structure
- Consistent header formatting
- Proper function organization

## Wiring

See `wiring.md` for power, DCMI, and ST-Link debug notes.
