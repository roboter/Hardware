# MSP430G2xx Driver Library Examples

This directory contains example code demonstrating how to use each peripheral module in the MSP430G2xx Driver Library.

## Example Files

### GPIO Example (`gpio_example.c`)
- **Purpose**: Basic GPIO input/output operations
- **Features**: Button input with LED output, pin state control
- **Hardware**: P1.0 (LED), P1.3 (Button)

### Timer_A Example (`timer_a_example.c`)
- **Purpose**: Timer_A periodic interrupt generation
- **Features**: Up mode timer configuration, ISR-based LED toggling
- **Hardware**: P1.0 (LED), Timer_A0
- **Power Mode**: LPM3 (low power with ACLK active)

### UART Example (`usci_a_uart_example.c`)
- **Purpose**: UART communication with echo functionality
- **Features**: 9600 baud UART, transmit/receive, interrupt-driven echo
- **Hardware**: P1.1 (TX), P1.2 (RX), USCI_A0
- **Power Mode**: LPM0 (CPU active for UART interrupts)

### SPI Example (`usci_a_spi_example.c`)
- **Purpose**: SPI master communication
- **Features**: SPI data transmission/reception, 500kHz clock
- **Hardware**: P1.5 (SCLK), P1.6 (MISO), P1.7 (MOSI), P1.0 (Activity LED)
- **Note**: Requires external SPI slave device for full testing

### I2C Example (`usci_b_i2c_example.c`)
- **Purpose**: I2C master communication
- **Features**: I2C write/read transactions, 100kHz clock
- **Hardware**: P1.6 (SDA), P1.7 (SCL), P1.0 (Activity LED)
- **Note**: Requires external I2C slave device at address 0x48

### ADC Example (`adc10_a_example.c`)
- **Purpose**: Analog-to-digital conversion with PWM output
- **Features**: 10-bit ADC, continuous conversion, PWM duty cycle control
- **Hardware**: P1.0 (ADC input A0), P1.6 (PWM output), Timer_A0

### Clock System Example (`bcs_example.c`)
- **Purpose**: DCO frequency configuration and clock dividers
- **Features**: Multiple frequency ranges, visual frequency indication
- **Hardware**: P1.0 (Activity LED), P1.6 (Frequency indicator)

### Power Management Example (`pmm_example.c`)
- **Purpose**: Low power mode demonstration
- **Features**: LPM0-LPM3 cycling, GPIO interrupt wake-up
- **Hardware**: P1.0 (LED), P1.3 (Button for wake-up)
- **Power Modes**: Cycles through LPM0, LPM1, LPM2, LPM3

### Flash Controller Example (`flashctl_example.c`)
- **Purpose**: Flash memory read/write operations
- **Features**: Segment erase, data write, verify operations
- **Hardware**: P1.0 (Success LED), P1.6 (Activity LED)
- **Note**: Uses info segment A for testing - be careful with flash operations

### Watchdog Timer Example (`wdt_a_example.c`)
- **Purpose**: Watchdog timer configuration and feeding
- **Features**: Multiple modes (disabled, fed, unfed timeout)
- **Hardware**: P1.0 (Mode LED), P1.6 (Activity LED), P1.3 (Mode button)

## Building and Running Examples

### Prerequisites
1. **MSP430G2553 or compatible G2xx device**
2. **CCS, IAR, or GCC toolchain**
3. **MSP430 device headers** (`msp430g2553.h`)
4. **This driver library** included in project

### Setup Steps
1. **Create new MSP430 project** in your IDE
2. **Copy example .c file** to your project
3. **Include driverlib.h** in your project path
4. **Include device header** (`msp430g2553.h`)
5. **Configure project settings**:
   - Target device: MSP430G2553
   - Include paths for driverlib
   - Appropriate optimization settings

### Hardware Connections
Most examples use LaunchPad-standard connections:
- **P1.0**: Red LED (LED1)
- **P1.3**: Push button (S2)
- **P1.6**: Green LED (LED2)

For communication examples, connect:
- **UART**: P1.1 (TX), P1.2 (RX) to serial adapter
- **SPI**: P1.5 (CLK), P1.6 (MISO), P1.7 (MOSI) to SPI device
- **I2C**: P1.6 (SDA), P1.7 (SCL) to I2C device

### Running Examples
1. **Flash the example** to your MSP430
2. **Observe LED patterns** and behavior
3. **Use serial terminal** for UART examples (9600 baud)
4. **Press buttons** to interact with examples

## Important Notes

### Flash Operations
- **Caution**: Flash examples modify device flash memory
- **Backup**: Backup important data before running flash examples
- **Wear**: Flash has limited write cycles (~10,000)

### Communication Examples
- **External Hardware**: SPI and I2C examples need external devices
- **Wiring**: Double-check pin connections
- **Termination**: I2C bus may need pull-up resistors

### Power Management
- **Current Measurement**: Use ammeter to verify low power modes
- **Wake-up Sources**: GPIO interrupts are primary wake-up method
- **Clock Requirements**: Some modes require ACLK for wake-up

### Watchdog Timer
- **System Reset**: Unfed watchdog will reset the entire system
- **Debugging**: Use debugger to step through watchdog examples
- **Recovery**: Have recovery code for unexpected resets

## Troubleshooting

### Common Issues
1. **No LED activity**: Check power, connections, and device selection
2. **UART no output**: Verify baud rate, pins, and serial settings
3. **SPI/I2C failures**: Check wiring, pull-ups, and slave device
4. **ADC issues**: Verify reference voltage and input connections
5. **Flash problems**: Check segment addresses and write permissions

### Debug Tips
- Use **oscilloscope** for timing-critical examples
- **Logic analyzer** helpful for SPI/I2C debugging
- **Multimeter** for voltage and continuity checks
- **Serial terminal** for UART debugging

## Customization

Each example can be modified for your specific needs:
- **Pin assignments**: Change GPIO pins as needed
- **Timing values**: Adjust delays and periods
- **Buffer sizes**: Modify data buffers for your application
- **Addresses**: Change I2C addresses for your slave devices

## Learning Path

Start with simpler examples and progress to more complex ones:
1. **GPIO** - Basic I/O concepts
2. **Timer_A** - Interrupt handling
3. **BCS** - Clock system understanding
4. **ADC** - Analog signal processing
5. **UART** - Serial communication
6. **SPI/I2C** - Peripheral communication
7. **Flash** - Non-volatile storage
8. **PMM** - Power optimization
9. **WDT** - System reliability