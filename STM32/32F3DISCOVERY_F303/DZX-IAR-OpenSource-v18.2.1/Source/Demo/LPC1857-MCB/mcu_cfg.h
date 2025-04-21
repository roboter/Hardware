/*******************************************************************************************************************************************

    DZX | LPC18xx | CONFIGURATION                                                                                         VERSION 18.2.1
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

    ADC CLOCK FREQUENCY             The frequency, in hertz, that should be used for the ADC clock (Must be less than 4.5Mhz per manual).

*******************************************************************************************************************************************/
#define CFG_ADCCLOCKHZ              4500000

/*******************************************************************************************************************************************

    UART RX BUFFER SIZE             The size, in bytes, of the buffer used for receiving data from a UART.

*******************************************************************************************************************************************/
#define CFG_UARTRXBUFFERSIZE        128

/*******************************************************************************************************************************************

    UART TX BUFFER SIZE             The size, in bytes, of the buffer used for transmitting data to a UART.

*******************************************************************************************************************************************/
#define CFG_UARTTXBUFFERSIZE        128

/*******************************************************************************************************************************************

    USE SPIFI INTERRUPT             Use 'TRUE' to use interrupt for waiting for SPIFI commands to complete; otherwise 'FALSE' to spin loop.

*******************************************************************************************************************************************/
#define CFG_SPIFIIRQ                FALSE

/*******************************************************************************************************************************************

    CPU CLOCK FREQUENCY             Reflects the frequency of the CPU clock, in hertz.

*******************************************************************************************************************************************/
#define CFG_CPUCLOCKHZ              180000000

/*******************************************************************************************************************************************

    PLL 1 MULTIPLIER                The multiplier value for PLL 1.

                                        00000000 = 1
                                        00000001 = 2
                                        ...
                                        11111111 = 256

*******************************************************************************************************************************************/
#define CFG_PLL1MSEL		        14

/*******************************************************************************************************************************************

    PLL 1 POST-DIVIDER             The post-divider value for PLL 1. The P-divider applied by the PLL is 2xP.

                                        0x0 P = 1
                                        0x1 P = 2 (default)
                                        0x2 P = 4
                                        0x3 P = 8

*******************************************************************************************************************************************/
#define CFG_PLL1PSEL		        0

/*******************************************************************************************************************************************

    PLL 1 PRE-DIVIDER              The pre-divider value for PLL 1.

                                        0x0 1
                                        0x1 2
                                        0x2 3 (default)
                                        0x3 4

*******************************************************************************************************************************************/
#define CFG_PLL1NSEL                0

/*******************************************************************************************************************************************

    PLL 1 DIRECT                    PLL direct CCO output. '1' enabled, '0' disabled.

*******************************************************************************************************************************************/
#define CFG_PLL1DIRECT              1

/*******************************************************************************************************************************************

    HOOK UNHANDLED IRQ              Determines whether to call function 'HOOK_UnhandledIRQ' upon each unhandled interrupt. This function 
                                    is called from the context of the unhandled interrupt.

*******************************************************************************************************************************************/
#define CFG_HOOKUNHANDLEDIRQ        FALSE

/*******************************************************************************************************************************************

    DRIVER SIGNAL                   Specifies the signal that is used by all drivers to signal calling threads.

*******************************************************************************************************************************************/
#define CFG_DRIVERSIGNAL            SIGNAL_0

#endif /* MCU_CFG_H__ */
