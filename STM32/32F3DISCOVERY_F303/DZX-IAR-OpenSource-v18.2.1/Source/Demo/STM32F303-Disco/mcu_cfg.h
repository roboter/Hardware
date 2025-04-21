/*******************************************************************************************************************************************

    DZX | STM32F3xx | CONFIGURATION                                                                                       VERSION 18.2.1
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
#define CFG_CPUCLOCKHZ              72000000

/*******************************************************************************************************************************************

    PLL MULTIPLICATION FACTOR       The PLL multiplication factor.

                                        0000: PLL input clock x 2
                                        0001: PLL input clock x 3
                                        0010: PLL input clock x 4
                                        0011: PLL input clock x 5
                                        0100: PLL input clock x 6
                                        0101: PLL input clock x 7
                                        0110: PLL input clock x 8
                                        0111: PLL input clock x 9
                                        1000: PLL input clock x 10
                                        1001: PLL input clock x 11
                                        1010: PLL input clock x 12
                                        1011: PLL input clock x 13
                                        1100: PLL input clock x 14
                                        1101: PLL input clock x 15
                                        1110: PLL input clock x 16
                                        1111: PLL input clock x 16

                                    Caution: The PLL output frequency must not exceed 72 MHz.

*******************************************************************************************************************************************/
#define CFG_PLLMUL		            7

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

    APB 1 SPEED PRESCALAR           The APB 1 clock prescalar.

                                    0xx: AHB clock not divided
                                    100: AHB clock divided by 2
                                    101: AHB clock divided by 4
                                    110: AHB clock divided by 8
                                    111: AHB clock divided by 16

*******************************************************************************************************************************************/
#define CFG_PRE1		            0x5

/*******************************************************************************************************************************************

    APB 2 PRESCALAR                 The APB 2 clock prescalar.

                                    0xx: AHB clock not divided
                                    100: AHB clock divided by 2
                                    101: AHB clock divided by 4
                                    110: AHB clock divided by 8
                                    111: AHB clock divided by 16

*******************************************************************************************************************************************/
#define CFG_PRE2		            0x4

/*******************************************************************************************************************************************

    FLASH LATENCY                   These bits represent the ratio of the SYSCLK (system clock) period to the Flash memory access time.

                                        0: Zero wait state, if 0 < SYSCLK <= 24Mhz
                                        1: One wait state, if 24Mhz < SYSCLK <= 48Mhz
                                        2: Two wait states, if 48Mhz < SYSCLK <= 72Mhz

*******************************************************************************************************************************************/
#define CFG_FLASHLATENCY            2

#endif /* MCU_CFG_H__ */
