# Tests

This directory contains unit tests for the STM32 project.

## Test Files

- `test_bit_manipulation.c`: Tests for bit manipulation macros defined in `include/bit_manipulation.h`. Runs on native platform.
- `embedded/test_hal.c`: Tests for STM32 HAL GPIO functions. Runs on STM32 hardware.

## Running Tests

### Native Tests (Bit Manipulation)
```bash
pio test -e test
```

### HAL Tests (STM32)
Build and upload to STM32 hardware:
```bash
pio run -e test_stm32
```
The test will run on the target and output results via serial.

## Test Frameworks

- Native tests use Unity framework.
- HAL tests use Unity framework with custom configuration for embedded environment.