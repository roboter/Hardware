/*******************************************************************************************************************************************

    DZX | LPC177x8x | CONFIGURATION                                                                                       VERSION 18.2.1
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

    ADC CLOCK FREQUENCY             The frequency, in hertz, that should be used for the ADC clock (Must be less than 12.4Mhz per manual).

*******************************************************************************************************************************************/
#define CFG_ADCCLOCKHZ              12400000

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
#define CFG_CPUCLOCKHZ              120000000

/*******************************************************************************************************************************************

    PLL 0 MULTIPLIER                The multiplier value for PLL 0.

*******************************************************************************************************************************************/
#define CFG_CLKPLL0MSEL		        0x9

/*******************************************************************************************************************************************

    PLL 0 PRE-DIVIDER               The pre-divider value for PLL 0.

*******************************************************************************************************************************************/
#define CFG_CLKPLL0PSEL		        0x0

/*******************************************************************************************************************************************

    POWER BOOST                     Allows choosing between high-speed operation above 100 Mhz, or power savings when operation is below
                                    100 Mhz.

                                    0x0 - Boost is off, operation must be below 100 Mhz.
                                    0x3 - Boost is on, operation up to 120 Mhz is supported.

*******************************************************************************************************************************************/
#define CFG_PBOOST                  0x3

/*******************************************************************************************************************************************

    FLASH ACCESS TIME               Flash access time. The value of this field plus 1 gives the number of CPU clocks used for flash access.

                                    0x0 - Flash accesses use 1 CPU clock. Use for up to 20 Mhz CPU clock with power boost off.
                                    0x1 - Flash accesses use 2 CPU clocks. Use for up to 40 Mhz CPU clock with power boost off.
                                    0x2 - Flash accesses use 3 CPU clocks. Use for up to 60 Mhz CPU clock with power boost off.
                                    0x3 - Flash accesses use 4 CPU clocks. Use for up to 80 Mhz CPU clock with power boost off.
                                    0x4 - Flash accesses use 5 CPU clocks. Use for up to 120 Mhz CPU clock.
                                    0x5 - Flash accesses use 6 CPU clocks. "Safe" setting for any allowed conditions.

*******************************************************************************************************************************************/
#define CFG_FLASHTIM                0x4 

/*******************************************************************************************************************************************

    CPU CLOCK DIVIDER               The CPU clock divider value.

                                    0x0 - Divider is turned off. No clock to the CPU.
                                    (0x1 - 0x2F) - The input clock is divided by n to produce the CPU clock.

*******************************************************************************************************************************************/
#define CFG_CCLKDIV                 0x1

/*******************************************************************************************************************************************

    HOOK UNHANDLED IRQ              Determines whether to call function 'HOOK_UnhandledIRQ' upon each unhandled interrupt. This funcion is
                                    called from the context of the unhandled interrupt.

*******************************************************************************************************************************************/
#define CFG_HOOKUNHANDLEDIRQ        FALSE

#endif /* MCU_CFG_H__ */
