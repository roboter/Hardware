/*******************************************************************************************************************************************

    DZX | LPC15xx | CONFIGURATION                                                                                         VERSION 18.2.1
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

    DRIVER SIGNAL                   Specifies the signal that is used by all drivers to signal calling threads.

*******************************************************************************************************************************************/
#define CFG_DRIVERSIGNAL            SIGNAL_0

/*******************************************************************************************************************************************

    ADC CLOCK FREQUENCY             The frequency that should be used for the ADC clock (Must be less than 13Mhz per manual).

*******************************************************************************************************************************************/
#define CFG_ADCCLOCKHZ              13000000

/*******************************************************************************************************************************************

    UART RX BUFFER SIZE             The size, in bytes, of the buffer used for receiving data from a UART.

*******************************************************************************************************************************************/
#define CFG_UARTRXBUFFERSIZE        128

/*******************************************************************************************************************************************

    UART TX BUFFER SIZE             The size, in bytes, of the buffer used for transmitting data to a UART.

*******************************************************************************************************************************************/
#define CFG_UARTTXBUFFERSIZE        128

/*******************************************************************************************************************************************

    CPU CLOCK FREQUENCY             Reflects the frequency of the CPU clock, in hertz.

*******************************************************************************************************************************************/
#define CFG_CPUCLOCKHZ              72000000

/*******************************************************************************************************************************************

    PLL 0 MULTIPLIER                The feedback divider value for the system PLL.

*******************************************************************************************************************************************/
#define CFG_SYSPLLMSEL		        0x5

/*******************************************************************************************************************************************

    PLL 0 PRE-DIVIDER               The post-divider value for the system PLL.

*******************************************************************************************************************************************/
#define CFG_SYSPLLPSEL		        0x2

/*******************************************************************************************************************************************

    FLASH MEMORY ACCESS TIME        Flash memory access time. FLASHTIM +1 is equal to the number of system clocks used for flash access.

                                        0x0 - 1 clock cycle (for system clock frequencies of up to 25 MHz).
                                        0x1 - 2 clock cycles (for system clock frequencies of up to 55 MHz).
                                        0x2 - 3 clock cycles (for system clock frequencies of up to 72 MHz).

*******************************************************************************************************************************************/
#define CFG_FLASHTIM                0x2

#endif /* MCU_CFG_H__ */
