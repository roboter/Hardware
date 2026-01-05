# Discovery3 Project

This project is an STM32F303XC based application developed using STM32CubeMX and CMake. It is designed to be built with the ARM GNU Toolchain and flashed onto a Discovery board.

## Project Structure

```text
.
├── cmake/                      # CMake toolchain and generated files
│   ├── gcc-arm-none-eabi.cmake # Toolchain configuration for ARM GCC
│   └── stm32cubemx/           # Generated CMake files from CubeMX
├── Core/                       # Application source and header files
│   ├── Inc/                    # Main application headers
│   └── Src/                    # Main application sources (main.c, etc.)
├── Drivers/                    # STM32 HAL and CMSIS drivers
├── CMakeLists.txt              # Main CMake project configuration
├── CMakePresets.json           # Build presets for Debug and Release
├── Discovery3.ioc              # STM32CubeMX project file
├── STM32F303XX_FLASH.ld        # Linker script for STM32F303XC
└── startup_stm32f303xc.s       # Assembly startup file
```

## Prerequisites

To build and run this project, you will need:

- **ARM GNU Toolchain**: `arm-none-eabi-gcc`
- **CMake**: Version 3.22 or higher
- **Ninja**: Build system (recommended)
- **OpenOCD** or **ST-Link Tools**: For flashing the firmware

## Build Instructions

This project uses CMake presets for easy configuration.

### Configure

To configure the project for Debug:

```bash
cmake --preset Debug
```

For Release:

```bash
cmake --preset Release
```

### Build

To build the project:

```bash
cmake --build build/Debug
```

or for Release:

```bash
cmake --build build/Release
```

The resulting binaries (e.g., `Discovery3.elf`) will be located in the `build/Debug/` or `build/Release/` directory.

## Verification

Before flashing, you can verify that your board is connected and recognized:

```bash
st-info --probe
```

## Flashing Instructions

### Using OpenOCD

```bash
openocd -f interface/stlink.cfg -f target/stm32f3x.cfg -c "program build/Debug/Discovery3.elf verify reset exit"
```

### Using st-flash

If you have `st-link` tools installed, you can generate a `.bin` file and flash it:

```bash
arm-none-eabi-objcopy -O binary build/Debug/Discovery3.elf build/Debug/Discovery3.bin
st-flash write build/Debug/Discovery3.bin 0x08000000
```

## IDE Support

This project includes `CMakePresets.json` and `CMAKE_EXPORT_COMPILE_COMMANDS=ON`, making it compatible with modern IDEs like VS Code (with CMake Tools), CLion, and Antigravity.
