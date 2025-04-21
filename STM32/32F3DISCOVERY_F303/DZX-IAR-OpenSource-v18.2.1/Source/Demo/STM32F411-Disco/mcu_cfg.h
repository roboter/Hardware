/*******************************************************************************************************************************************

    DZX | STM32F4xx | CONFIGURATION                                                                                       VERSION 18.2.1
    ------------------------------------------------------------------------------------------------------------------------------------

    This provides configuration settings for the MCU peripheral drivers.

    ------------------------------------------------------------------------------------------------------------------------------------

    GNU GENERAL PUBLIC LICENSE VERSION 3 (GPLv3)

    This file is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published 
    by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.

    This file is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of 
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along with this distribution (license.txt). Please review the 
    following information to ensure all requirements of the license will be met:  
    <https://dzxdesigns.com/licensing/open.aspx> and <http://www.gnu.org/licenses/gpl-3.0.html> for more information.

    ------------------------------------------------------------------------------------------------------------------------------------
    COPYRIGHT (C) 2018 DZX DESIGNS 

*******************************************************************************************************************************************/
#ifndef MCU_CFG_H__
#define MCU_CFG_H__

/*******************************************************************************************************************************************

    MCU CONFIGURATION               Specifies whether code is included for each of the modules within the MCU driver.

*******************************************************************************************************************************************/
#define CFG_ADC                     TRUE
#define CFG_I2C                     TRUE
#define CFG_SPI                     TRUE
#define CFG_FLASH                   TRUE
#define CFG_UART                    TRUE

/*******************************************************************************************************************************************

    DRIVER SIGNAL                   Specifies the signal that is used by all drivers to signal calling threads.

*******************************************************************************************************************************************/
#define CFG_DRIVERSIGNAL            SIGNAL_0



/*******************************************************************************************************************************************
    UART CONFIGURATION
*******************************************************************************************************************************************/
/*******************************************************************************************************************************************

    UART RX BUFFER SIZE             The size, in bytes, of the buffer used for receiving data from a UART.

*******************************************************************************************************************************************/
#define CFG_UARTRXBUFFERSIZE        128

/*******************************************************************************************************************************************

    UART TX BUFFER SIZE             The size, in bytes, of the buffer used for transmitting data to a UART.

*******************************************************************************************************************************************/
#define CFG_UARTTXBUFFERSIZE        128





/*******************************************************************************************************************************************
    CPU CLOCK CONFIGURATION
*******************************************************************************************************************************************/
/*******************************************************************************************************************************************

    CPU CLOCK FREQUENCY             Reflects the frequency of the CPU clock, in hertz.

*******************************************************************************************************************************************/
#define CFG_CPUCLOCKHZ              96000000

/*******************************************************************************************************************************************

    PLL DIVISION FACTOR             The division factor for the main PLL input clock.

                                    VCO input frequency = PLL input clock frequency / PLLM with 2 = PLLM = 63
                                    000000: PLLM = 0, wrong configuration
                                    000001: PLLM = 1, wrong configuration
                                    000010: PLLM = 2
                                    000011: PLLM = 3
                                    000100: PLLM = 4
                                    ...
                                    111110: PLLM = 62
                                    111111: PLLM = 63

                                    Caution: The software has to set these bits correctly to ensure that the VCO input frequency ranges 
                                    from 1 to 2 MHz. It is recommended to select a frequency of 2 MHz to limit PLL jitter.

*******************************************************************************************************************************************/
#define CFG_PLLM		            8

/*******************************************************************************************************************************************

    PLL MULTIPLICATION FACTOR       The multiplication factor for VCO.

                                    VCO output frequency = VCO input frequency � PLLN with 50 = PLLN = 432
                                    000000000: PLLN = 0, wrong configuration
                                    000000001: PLLN = 1, wrong configuration
                                    ...
                                    000110010: PLLN = 50
                                    ...
                                    001100011: PLLN = 99
                                    001100100: PLLN = 100
                                    ...
                                    110110000: PLLN = 432
                                    110110001: PLLN = 433, wrong configuration
                                    ...
                                    111111111: PLLN = 511, wrong configuration

                                    Caution: The software has to set these bits correctly to ensure that the VCO output frequency is 
                                    between 100 and 432 MHz.

*******************************************************************************************************************************************/
#define CFG_PLLN		            384

/*******************************************************************************************************************************************

    PLL SYS DIVISION FACTOR         The main PLL division factor for the main system clock.

                                    PLL output clock frequency = VCO frequency / PLLP with PLLP = 2, 4, 6, or 8
                                    00: PLLP = 2
                                    01: PLLP = 4
                                    10: PLLP = 6
                                    11: PLLP = 8

                                    Caution: The software has to set these bits correctly not to exceed 100 MHz on this domain.

*******************************************************************************************************************************************/
#define CFG_PLLP		            1

/*******************************************************************************************************************************************

    PLL PER DIVISION FACTOR         The main PLL division factor for the USB OTG FS, SDIO and random number generator clock.

                                    USB OTG FS clock frequency = VCO frequency / PLLQ with 2 = PLLQ = 15
                                    0000: PLLQ = 0, wrong configuration
                                    0001: PLLQ = 1, wrong configuration
                                    0010: PLLQ = 2
                                    0011: PLLQ = 3
                                    0100: PLLQ = 4
                                    ...
                                    1111: PLLQ = 15

                                    Caution: The USB OTG FS requires a 48 MHz clock to work correctly. The SDIO and the random number 
                                    generator need a frequency lower than or equal to 48 MHz to work correctly.

*******************************************************************************************************************************************/
#define CFG_PLLQ		            8

/*******************************************************************************************************************************************

    AHB PRESCALAR                   The AHB clock prescalar.

                                    0xxx: system clock not divided
                                    1000: system clock divided by 2
                                    1001: system clock divided by 4
                                    1010: system clock divided by 8
                                    1011: system clock divided by 16
                                    1100: system clock divided by 64
                                    1101: system clock divided by 128
                                    1110: system clock divided by 256
                                    1111: system clock divided by 512

                                    Caution: The AHB clock frequency must be at least 25 MHz when the Ethernet is used.

*******************************************************************************************************************************************/
#define CFG_HPRE		            0x0

/*******************************************************************************************************************************************

    APB LOW SPEED PRESCALAR         The APB low speed clock prescalar.

                                    0xx: AHB clock not divided
                                    100: AHB clock divided by 2
                                    101: AHB clock divided by 4
                                    110: AHB clock divided by 8
                                    111: AHB clock divided by 16

                                    Caution: The software has to set these bits correctly not to exceed 42 MHz on this domain.

*******************************************************************************************************************************************/
#define CFG_PRE1		            0x5

/*******************************************************************************************************************************************

    APB HIGH SPEED PRESCALAR        The APB high speed clock prescalar.

                                    0xx: AHB clock not divided
                                    100: AHB clock divided by 2
                                    101: AHB clock divided by 4
                                    110: AHB clock divided by 8
                                    111: AHB clock divided by 16

                                    Caution: The software has to set these bits correctly not to exceed 84 MHz on this domain.

*******************************************************************************************************************************************/
#define CFG_PRE2		            0x4

/*******************************************************************************************************************************************

    FLASH LATENCY                   These bits represent the ratio of the CPU clock period to the Flash memory access time.

                                    0000: Zero wait state
                                    0001: One wait state
                                    0010: Two wait states
                                    ---
                                    1110: Fourteen wait states
                                    1111: Fifteen wait states

*******************************************************************************************************************************************/
#define CFG_FLASHLATENCY            5

#endif /* MCU_CFG_H__ */
