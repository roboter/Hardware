# APM32F072VB Mini Board Wiring and Programming

## Power Supply
- **USB Type-B**: Connect to PC to power the board.
- **J6, J8, J9, J10**: Ensure these jumpers are solid for proper operation.

## Programming and Debugging
- **SWD Interface**: Use an external emulator (like J-Link) for programming and debugging via the SWD interface.
- **SEGGER Embedded Studio**: Can be used for development on macOS (Note: Choose J-Link as the debugger).

## Interface Notes
- **USB**: 1x Type B port.
- **SWD**: 1x interface for debugging.
- **USART**: Switch between USART1 or USART2 using jumpers.

## Connectors details
The board features 81 GPIOs accessible via headers.
