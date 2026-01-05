# Discovery3 Hardware Specification

The Discovery3 project is based on the **STM32F3Discovery** (STM32F303XC) development kit. This board is designed around the STM32F303VCT6 microcontroller.

## 1. Microcontroller: STM32F303VCT6
- **Core**: ARM® Cortex®-M4F 32-bit CPU with FPU.
- **Clock**: Up to 72 MHz.
- **Memory**:
    - **Flash**: 256 KB.
    - **SRAM**: 48 KB (40 KB + 8 KB Core Coupled Memory - CCM).
- **Analog Peripherals**:
    - 4x 12-bit ADCs (up to 39 channels).
    - 2x 12-bit DACs.
    - 7x Fast ultra-low-power comparators.
    - 4x Operational amplifiers (PGA).
- **Communication**:
    - 2x I2C, 3x SPI, 5x USART/UART, 1x CAN, 1x USB 2.0 Full Speed.

## 2. On-Board Peripherals

### 2.1 Motion Sensors
- **L3GD20**: ST MEMS 3-axis digital output gyroscope.
- **LSM303DLHC**: ST MEMS 3D digital linear acceleration sensor and 3D digital magnetic sensor.

### 2.2 LEDs
- **LD1**: Red LED for 3.3V power.
- **LD2**: Red/Green LED for USB communication (ST-LINK).
- **User LEDs**: 8 user-programmable LEDs arranged in a compass pattern:
    - **LD3**: Red (North) - PE9
    - **LD4**: Blue (North-East) - PE8
    - **LD5**: Orange (East) - PE10
    - **LD6**: Green (South-East) - PE15
    - **LD7**: Green (South) - PE11
    - **LD8**: Orange (South-West) - PE14
    - **LD9**: Blue (West) - PE12
    - **LD10**: Red (North-West) - PE13

### 2.3 Buttons
- **B1 (USER)**: Blue push-button for user interaction (connected to PA0).
- **B2 (RESET)**: Black push-button for MCU reset.

## 3. Jumpers and Connectors

| Jumper/Connector | Description | Default Setting |
| :--- | :--- | :--- |
| **CN4** | ST-LINK/V2 Link Jumpers | **ON**: ST-LINK connected to on-board MCU. |
| **JP3** | IDD Jumper | **ON**: Power supply connected to MCU. |
| **CN1** | USB ST-LINK | Used for programming and debugging. |
| **CN2** | USB USER | Used for user USB application. |
| **CN3** | SWD Connector | Used for external programming (when CN4 is OFF). |

## 4. Pin Headers and Wiring

The board provides two 2x25 male headers (P1 and P2) that expose all available GPIOs of the LQFP100 package.

### Connector P1 (Left Side)
| Pin | Description | Pin | Description |
| :--- | :--- | :--- | :--- |
| 1 | VDD | 2 | VDD |
| 3 | GND | 4 | GND |
| 5 | PC13 | 6 | PC14 |
| 7 | PC15 | 8 | PF0 |
| 9 | PF1 | 10 | NRST |
| ... | ... | ... | ... |

### Connector P2 (Right Side)
| Pin | Description | Pin | Description |
| :--- | :--- | :--- | :--- |
| 1 | VDD | 2 | VDD |
| 3 | GND | 4 | GND |
| 5 | PH0 | 6 | PH1 |
| ... | ... | ... | ... |

> [!NOTE]
> For a full pinout diagram and detailed alternate functions, refer to the [STM32F303xC Datasheet](https://www.st.com/resource/en/datasheet/stm32f303vc.pdf) and [UM1570 User Manual](https://www.st.com/resource/en/user_manual/um1570-discovery-kit-with-stm32f303vc-mcu-stmicroelectronics.pdf).

## 5. Power Supply
- Power can be supplied via the USB connector (Mini-B) or through an external 3V or 5V source on the headers.
- Protection is provided by a 500mA resettable fuse (polyfuse).
