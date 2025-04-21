/*******************************************************************************************************************************************

    DZX | LPC18xx | CCU                                                                                                   VERSION 18.2.1
    ------------------------------------------------------------------------------------------------------------------------------------

    This is part of the MCU peripheral drivers and provides support for the clock control unit (CCU).

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
#ifndef MCU_CCU_H__
#define MCU_CCU_H__

#include "Kernel/kernel.h"

typedef struct CCU1PMBITFIELD {
    UINT32 PD                      :1;
    UINT32                         :31;
} CCU1PMBITFIELD;

typedef struct CCU1BASESTATBITFIELD {
    UINT32 BASEAPB3CLKIND          :1;
    UINT32 BASEAPB1CLKIND          :1;
    UINT32 BASESPIFICLKIND         :1;
    UINT32 BASEM3CLKIND            :1;
    UINT32                         :3;
    UINT32 BASEUSB0CLKIND          :1;
    UINT32 BASEUSB1CLKIND          :1;
    UINT32                         :23;
} CCU1BASESTATBITFIELD;

typedef struct CCU1CLKAPB3BUSCFGBITFIELD {
    UINT32 RUN                     :1;
    UINT32 AUTO                    :1;
    UINT32 WAKEUP                  :1;
    UINT32                         :29;
} CCU1CLKAPB3BUSCFGBITFIELD;

typedef struct CCU1CLKAPB3BUSSTATBITFIELD {
    UINT32 RUN                     :1;
    UINT32 AUTO                    :1;
    UINT32 WAKEUP                  :1;
    UINT32                         :29;
} CCU1CLKAPB3BUSSTATBITFIELD;
typedef struct CCU1CLKAPB3I2C1CFGBITFIELD
{
    UINT32 RUN                     :1;
    UINT32 AUTO                    :1;
    UINT32 WAKEUP                  :1;
    UINT32                         :29;
} CCU1CLKAPB3I2C1CFGBITFIELD;

typedef struct CCU1CLKAPB3I2C1STATBITFIELD {
    UINT32 RUN                     :1;
    UINT32 AUTO                    :1;
    UINT32 WAKEUP                  :1;
    UINT32                         :29;
} CCU1CLKAPB3I2C1STATBITFIELD;
typedef struct CCU1CLKAPB3DACCFGBITFIELD
{
    UINT32 RUN                     :1;
    UINT32 AUTO                    :1;
    UINT32 WAKEUP                  :1;
    UINT32                         :29;
} CCU1CLKAPB3DACCFGBITFIELD;

typedef struct CCU1CLKAPB3DACSTATBITFIELD {
    UINT32 RUN                     :1;
    UINT32 AUTO                    :1;
    UINT32 WAKEUP                  :1;
    UINT32                         :29;
} CCU1CLKAPB3DACSTATBITFIELD;

typedef struct CCU1CLKAPB3ADC0CFGBITFIELD {
    UINT32 RUN                     :1;
    UINT32 AUTO                    :1;
    UINT32 WAKEUP                  :1;
    UINT32                         :29;
} CCU1CLKAPB3ADC0CFGBITFIELD;

typedef struct CCU1CLKAPB3ADC0STATBITFIELD {
    UINT32 RUN                     :1;
    UINT32 AUTO                    :1;
    UINT32 WAKEUP                  :1;
    UINT32                         :29;
} CCU1CLKAPB3ADC0STATBITFIELD;

typedef struct CCU1CLKAPB3ADC1CFGBITFIELD
{
    UINT32 RUN                     :1;
    UINT32 AUTO                    :1;
    UINT32 WAKEUP                  :1;
    UINT32                         :29;
} CCU1CLKAPB3ADC1CFGBITFIELD;
typedef struct CCU1CLKAPB3ADC1STATBITFIELD
{
    UINT32 RUN                     :1;
    UINT32 AUTO                    :1;
    UINT32 WAKEUP                  :1;
    UINT32                         :29;
} CCU1CLKAPB3ADC1STATBITFIELD;
typedef struct CCU1CLKAPB3CANCFGBITFIELD
{
    UINT32 RUN                     :1;
    UINT32 AUTO                    :1;
    UINT32 WAKEUP                  :1;
    UINT32                         :29;
} CCU1CLKAPB3CANCFGBITFIELD;
typedef struct CCU1CLKAPB3CANSTATBITFIELD
{
    UINT32 RUN                     :1;
    UINT32 AUTO                    :1;
    UINT32 WAKEUP                  :1;
    UINT32                         :29;
} CCU1CLKAPB3CANSTATBITFIELD;
typedef struct CCU1CLKAPB1BUSCFGBITFIELD
{
    UINT32 RUN                     :1;
    UINT32 AUTO                    :1;
    UINT32 WAKEUP                  :1;
    UINT32                         :29;
} CCU1CLKAPB1BUSCFGBITFIELD;
typedef struct CCU1CLKAPB1BUSSTATBITFIELD
{
    UINT32 RUN                     :1;
    UINT32 AUTO                    :1;
    UINT32 WAKEUP                  :1;
    UINT32                         :29;
} CCU1CLKAPB1BUSSTATBITFIELD;
typedef struct CCU1CLKAPB1MOTOCONCFGBITFIELD
{
    UINT32 RUN                     :1;
    UINT32 AUTO                    :1;
    UINT32 WAKEUP                  :1;
    UINT32                         :29;
} CCU1CLKAPB1MOTOCONCFGBITFIELD;
typedef struct CCU1CLKAPB1MOTOCONSTATBITFIELD
{
    UINT32 RUN                     :1;
    UINT32 AUTO                    :1;
    UINT32 WAKEUP                  :1;
    UINT32                         :29;
} CCU1CLKAPB1MOTOCONSTATBITFIELD;
typedef struct CCU1CLKAPB1I2C0CFGBITFIELD
{
    UINT32 RUN                     :1;
    UINT32 AUTO                    :1;
    UINT32 WAKEUP                  :1;
    UINT32                         :29;
} CCU1CLKAPB1I2C0CFGBITFIELD;
typedef struct CCU1CLKAPB1I2C0STATBITFIELD
{
    UINT32 RUN                     :1;
    UINT32 AUTO                    :1;
    UINT32 WAKEUP                  :1;
    UINT32                         :29;
} CCU1CLKAPB1I2C0STATBITFIELD;
typedef struct CCU1CLKAPB1I2SCFGBITFIELD
{
    UINT32 RUN                     :1;
    UINT32 AUTO                    :1;
    UINT32 WAKEUP                  :1;
    UINT32                         :29;
} CCU1CLKAPB1I2SCFGBITFIELD;
typedef struct CCU1CLKAPB1I2SSTATBITFIELD
{
    UINT32 RUN                     :1;
    UINT32 AUTO                    :1;
    UINT32 WAKEUP                  :1;
    UINT32                         :29;
} CCU1CLKAPB1I2SSTATBITFIELD;
typedef struct CCU1CLKSPIFICFGBITFIELD
{
    UINT32 RUN                     :1;
    UINT32 AUTO                    :1;
    UINT32 WAKEUP                  :1;
    UINT32                         :29;
} CCU1CLKSPIFICFGBITFIELD;
typedef struct CCU1CLKSPIFISTATBITFIELD
{
    UINT32 RUN                     :1;
    UINT32 AUTO                    :1;
    UINT32 WAKEUP                  :1;
    UINT32                         :29;
} CCU1CLKSPIFISTATBITFIELD;
typedef struct CCU1CLKM3BUSCFGBITFIELD
{
    UINT32 RUN                     :1;
    UINT32 AUTO                    :1;
    UINT32 WAKEUP                  :1;
    UINT32                         :29;
} CCU1CLKM3BUSCFGBITFIELD;
typedef struct CCU1CLKM3BUSSTATBITFIELD
{
    UINT32 RUN                     :1;
    UINT32 AUTO                    :1;
    UINT32 WAKEUP                  :1;
    UINT32                         :29;
} CCU1CLKM3BUSSTATBITFIELD;
typedef struct CCU1CLKM3SPIFICFGBITFIELD
{
    UINT32 RUN                     :1;
    UINT32 AUTO                    :1;
    UINT32 WAKEUP                  :1;
    UINT32                         :29;
} CCU1CLKM3SPIFICFGBITFIELD;
typedef struct CCU1CLKM3SPIFISTATBITFIELD
{
    UINT32 RUN                     :1;
    UINT32 AUTO                    :1;
    UINT32 WAKEUP                  :1;
    UINT32                         :29;
} CCU1CLKM3SPIFISTATBITFIELD;
typedef struct CCU1CLKM3GPIOCFGBITFIELD
{
    UINT32 RUN                     :1;
    UINT32 AUTO                    :1;
    UINT32 WAKEUP                  :1;
    UINT32                         :29;
} CCU1CLKM3GPIOCFGBITFIELD;
typedef struct CCU1CLKM3GPIOSTATBITFIELD
{
    UINT32 RUN                     :1;
    UINT32 AUTO                    :1;
    UINT32 WAKEUP                  :1;
    UINT32                         :29;
} CCU1CLKM3GPIOSTATBITFIELD;
typedef struct CCU1CLKM3LCDCFGBITFIELD
{
    UINT32 RUN                     :1;
    UINT32 AUTO                    :1;
    UINT32 WAKEUP                  :1;
    UINT32                         :29;
} CCU1CLKM3LCDCFGBITFIELD;
typedef struct CCU1CLKM3LCDSTATBITFIELD
{
    UINT32 RUN                     :1;
    UINT32 AUTO                    :1;
    UINT32 WAKEUP                  :1;
    UINT32                         :29;
} CCU1CLKM3LCDSTATBITFIELD;
typedef struct CCU1CLKM3ETHERNETCFGBITFIELD
{
    UINT32 RUN                     :1;
    UINT32 AUTO                    :1;
    UINT32 WAKEUP                  :1;
    UINT32                         :29;
} CCU1CLKM3ETHERNETCFGBITFIELD;
typedef struct CCU1CLKM3ETHERNETSTATBITFIELD
{
    UINT32 RUN                     :1;
    UINT32 AUTO                    :1;
    UINT32 WAKEUP                  :1;
    UINT32                         :29;
} CCU1CLKM3ETHERNETSTATBITFIELD;
typedef struct CCU1CLKM3USB0CFGBITFIELD
{
    UINT32 RUN                     :1;
    UINT32 AUTO                    :1;
    UINT32 WAKEUP                  :1;
    UINT32                         :29;
} CCU1CLKM3USB0CFGBITFIELD;
typedef struct CCU1CLKM3USB0STATBITFIELD
{
    UINT32 RUN                     :1;
    UINT32 AUTO                    :1;
    UINT32 WAKEUP                  :1;
    UINT32                         :29;
} CCU1CLKM3USB0STATBITFIELD;
typedef struct CCU1CLKM3EMCCFGBITFIELD
{
    UINT32 RUN                     :1;
    UINT32 AUTO                    :1;
    UINT32 WAKEUP                  :1;
    UINT32                         :29;
} CCU1CLKM3EMCCFGBITFIELD;
typedef struct CCU1CLKM3EMCSTATBITFIELD
{
    UINT32 RUN                     :1;
    UINT32 AUTO                    :1;
    UINT32 WAKEUP                  :1;
    UINT32                         :29;
} CCU1CLKM3EMCSTATBITFIELD;
typedef struct CCU1CLKM3SDIOCFGBITFIELD
{
    UINT32 RUN                     :1;
    UINT32 AUTO                    :1;
    UINT32 WAKEUP                  :1;
    UINT32                         :29;
} CCU1CLKM3SDIOCFGBITFIELD;
typedef struct CCU1CLKM3SDIOSTATBITFIELD
{
    UINT32 RUN                     :1;
    UINT32 AUTO                    :1;
    UINT32 WAKEUP                  :1;
    UINT32                         :29;
} CCU1CLKM3SDIOSTATBITFIELD;
typedef struct CCU1CLKM3DMACFGBITFIELD
{
    UINT32 RUN                     :1;
    UINT32 AUTO                    :1;
    UINT32 WAKEUP                  :1;
    UINT32                         :29;
} CCU1CLKM3DMACFGBITFIELD;
typedef struct CCU1CLKM3DMASTATBITFIELD
{
    UINT32 RUN                     :1;
    UINT32 AUTO                    :1;
    UINT32 WAKEUP                  :1;
    UINT32                         :29;
} CCU1CLKM3DMASTATBITFIELD;
typedef struct CCU1CLKM3M3CORECFGBITFIELD
{
    UINT32 RUN                     :1;
    UINT32 AUTO                    :1;
    UINT32 WAKEUP                  :1;
    UINT32                         :29;
} CCU1CLKM3M3CORECFGBITFIELD;
typedef struct CCU1CLKM3M3CORESTATBITFIELD
{
    UINT32 RUN                     :1;
    UINT32 AUTO                    :1;
    UINT32 WAKEUP                  :1;
    UINT32                         :29;
} CCU1CLKM3M3CORESTATBITFIELD;
typedef struct CCU1CLKM3AESCFGBITFIELD
{
    UINT32 RUN                     :1;
    UINT32 AUTO                    :1;
    UINT32 WAKEUP                  :1;
    UINT32                         :29;
} CCU1CLKM3AESCFGBITFIELD;
typedef struct CCU1CLKM3AESSTATBITFIELD
{
    UINT32 RUN                     :1;
    UINT32 AUTO                    :1;
    UINT32 WAKEUP                  :1;
    UINT32                         :29;
} CCU1CLKM3AESSTATBITFIELD;
typedef struct CCU1CLKM3SCTCFGBITFIELD
{
    UINT32 RUN                     :1;
    UINT32 AUTO                    :1;
    UINT32 WAKEUP                  :1;
    UINT32                         :29;
} CCU1CLKM3SCTCFGBITFIELD;
typedef struct CCU1CLKM3SCTSTATBITFIELD
{
    UINT32 RUN                     :1;
    UINT32 AUTO                    :1;
    UINT32 WAKEUP                  :1;
    UINT32                         :29;
} CCU1CLKM3SCTSTATBITFIELD;
typedef struct CCU1CLKM3USB1CFGBITFIELD
{
    UINT32 RUN                     :1;
    UINT32 AUTO                    :1;
    UINT32 WAKEUP                  :1;
    UINT32                         :29;
} CCU1CLKM3USB1CFGBITFIELD;
typedef struct CCU1CLKM3USB1STATBITFIELD
{
    UINT32 RUN                     :1;
    UINT32 AUTO                    :1;
    UINT32 WAKEUP                  :1;
    UINT32                         :29;
} CCU1CLKM3USB1STATBITFIELD;
typedef struct CCU1CLKM3EMCDIVCFGBITFIELD
{
    UINT32 RUN                     :1;
    UINT32 AUTO                    :1;
    UINT32 WAKEUP                  :1;
    UINT32                         :2;
    UINT32 DIV                     :3;
    UINT32                         :24;
} CCU1CLKM3EMCDIVCFGBITFIELD;
typedef struct CCU1CLKM3EMCDIVSTATBITFIELD
{
    UINT32 RUN                     :1;
    UINT32 AUTO                    :1;
    UINT32 WAKEUP                  :1;
    UINT32                         :29;
} CCU1CLKM3EMCDIVSTATBITFIELD;
typedef struct CCU1CLKM3WWDTCFGBITFIELD
{
    UINT32 RUN                     :1;
    UINT32 AUTO                    :1;
    UINT32 WAKEUP                  :1;
    UINT32                         :29;
} CCU1CLKM3WWDTCFGBITFIELD;
typedef struct CCU1CLKM3WWDTSTATBITFIELD
{
    UINT32 RUN                     :1;
    UINT32 AUTO                    :1;
    UINT32 WAKEUP                  :1;
    UINT32                         :29;
} CCU1CLKM3WWDTSTATBITFIELD;
typedef struct CCU1CLKM3USART0CFGBITFIELD
{
    UINT32 RUN                     :1;
    UINT32 AUTO                    :1;
    UINT32 WAKEUP                  :1;
    UINT32                         :29;
} CCU1CLKM3USART0CFGBITFIELD;
typedef struct CCU1CLKM3USART0STATBITFIELD
{
    UINT32 RUN                     :1;
    UINT32 AUTO                    :1;
    UINT32 WAKEUP                  :1;
    UINT32                         :29;
} CCU1CLKM3USART0STATBITFIELD;
typedef struct CCU1CLKM3UART1CFGBITFIELD
{
    UINT32 RUN                     :1;
    UINT32 AUTO                    :1;
    UINT32 WAKEUP                  :1;
    UINT32                         :29;
} CCU1CLKM3UART1CFGBITFIELD;
typedef struct CCU1CLKM3UART1STATBITFIELD
{
    UINT32 RUN                     :1;
    UINT32 AUTO                    :1;
    UINT32 WAKEUP                  :1;
    UINT32                         :29;
} CCU1CLKM3UART1STATBITFIELD;
typedef struct CCU1CLKM3SSP0CFGBITFIELD
{
    UINT32 RUN                     :1;
    UINT32 AUTO                    :1;
    UINT32 WAKEUP                  :1;
    UINT32                         :29;
} CCU1CLKM3SSP0CFGBITFIELD;
typedef struct CCU1CLKM3SSP0STATBITFIELD
{
    UINT32 RUN                     :1;
    UINT32 AUTO                    :1;
    UINT32 WAKEUP                  :1;
    UINT32                         :29;
} CCU1CLKM3SSP0STATBITFIELD;
typedef struct CCU1CLKM3TIMER0CFGBITFIELD
{
    UINT32 RUN                     :1;
    UINT32 AUTO                    :1;
    UINT32 WAKEUP                  :1;
    UINT32                         :29;
} CCU1CLKM3TIMER0CFGBITFIELD;
typedef struct CCU1CLKM3TIMER0STATBITFIELD
{
    UINT32 RUN                     :1;
    UINT32 AUTO                    :1;
    UINT32 WAKEUP                  :1;
    UINT32                         :29;
} CCU1CLKM3TIMER0STATBITFIELD;
typedef struct CCU1CLKM3TIMER1CFGBITFIELD
{
    UINT32 RUN                     :1;
    UINT32 AUTO                    :1;
    UINT32 WAKEUP                  :1;
    UINT32                         :29;
} CCU1CLKM3TIMER1CFGBITFIELD;
typedef struct CCU1CLKM3TIMER1STATBITFIELD
{
    UINT32 RUN                     :1;
    UINT32 AUTO                    :1;
    UINT32 WAKEUP                  :1;
    UINT32                         :29;
} CCU1CLKM3TIMER1STATBITFIELD;
typedef struct CCU1CLKM3SCUCFGBITFIELD
{
    UINT32 RUN                     :1;
    UINT32 AUTO                    :1;
    UINT32 WAKEUP                  :1;
    UINT32                         :29;
} CCU1CLKM3SCUCFGBITFIELD;
typedef struct CCU1CLKM3SCUSTATBITFIELD
{
    UINT32 RUN                     :1;
    UINT32 AUTO                    :1;
    UINT32 WAKEUP                  :1;
    UINT32                         :29;
} CCU1CLKM3SCUSTATBITFIELD;
typedef struct CCU1CLKM3CREGCFGBITFIELD
{
    UINT32 RUN                     :1;
    UINT32 AUTO                    :1;
    UINT32 WAKEUP                  :1;
    UINT32                         :29;
} CCU1CLKM3CREGCFGBITFIELD;
typedef struct CCU1CLKM3CREGSTATBITFIELD
{
    UINT32 RUN                     :1;
    UINT32 AUTO                    :1;
    UINT32 WAKEUP                  :1;
    UINT32                         :29;
} CCU1CLKM3CREGSTATBITFIELD;
typedef struct CCU1CLKM3RITIMERCFGBITFIELD
{
    UINT32 RUN                     :1;
    UINT32 AUTO                    :1;
    UINT32 WAKEUP                  :1;
    UINT32                         :29;
} CCU1CLKM3RITIMERCFGBITFIELD;
typedef struct CCU1CLKM3RITIMERSTATBITFIELD
{
    UINT32 RUN                     :1;
    UINT32 AUTO                    :1;
    UINT32 WAKEUP                  :1;
    UINT32                         :29;
} CCU1CLKM3RITIMERSTATBITFIELD;
typedef struct CCU1CLKM3USART2CFGBITFIELD
{
    UINT32 RUN                     :1;
    UINT32 AUTO                    :1;
    UINT32 WAKEUP                  :1;
    UINT32                         :29;
} CCU1CLKM3USART2CFGBITFIELD;
typedef struct CCU1CLKM3USART2STATBITFIELD
{
    UINT32 RUN                     :1;
    UINT32 AUTO                    :1;
    UINT32 WAKEUP                  :1;
    UINT32                         :29;
} CCU1CLKM3USART2STATBITFIELD;
typedef struct CCU1CLKM3USART3CFGBITFIELD
{
    UINT32 RUN                     :1;
    UINT32 AUTO                    :1;
    UINT32 WAKEUP                  :1;
    UINT32                         :29;
} CCU1CLKM3USART3CFGBITFIELD;
typedef struct CCU1CLKM3USART3STATBITFIELD
{
    UINT32 RUN                     :1;
    UINT32 AUTO                    :1;
    UINT32 WAKEUP                  :1;
    UINT32                         :29;
} CCU1CLKM3USART3STATBITFIELD;
typedef struct CCU1CLKM3TIMER2CFGBITFIELD
{
    UINT32 RUN                     :1;
    UINT32 AUTO                    :1;
    UINT32 WAKEUP                  :1;
    UINT32                         :29;
} CCU1CLKM3TIMER2CFGBITFIELD;
typedef struct CCU1CLKM3TIMER2STATBITFIELD
{
    UINT32 RUN                     :1;
    UINT32 AUTO                    :1;
    UINT32 WAKEUP                  :1;
    UINT32                         :29;
} CCU1CLKM3TIMER2STATBITFIELD;
typedef struct CCU1CLKM3TIMER3CFGBITFIELD
{
    UINT32 RUN                     :1;
    UINT32 AUTO                    :1;
    UINT32 WAKEUP                  :1;
    UINT32                         :29;
} CCU1CLKM3TIMER3CFGBITFIELD;
typedef struct CCU1CLKM3TIMER3STATBITFIELD
{
    UINT32 RUN                     :1;
    UINT32 AUTO                    :1;
    UINT32 WAKEUP                  :1;
    UINT32                         :29;
} CCU1CLKM3TIMER3STATBITFIELD;
typedef struct CCU1CLKM3SSP1CFGBITFIELD
{
    UINT32 RUN                     :1;
    UINT32 AUTO                    :1;
    UINT32 WAKEUP                  :1;
    UINT32                         :29;
} CCU1CLKM3SSP1CFGBITFIELD;
typedef struct CCU1CLKM3SSP1STATBITFIELD
{
    UINT32 RUN                     :1;
    UINT32 AUTO                    :1;
    UINT32 WAKEUP                  :1;
    UINT32                         :29;
} CCU1CLKM3SSP1STATBITFIELD;
typedef struct CCU1CLKM3QEICFGBITFIELD
{
    UINT32 RUN                     :1;
    UINT32 AUTO                    :1;
    UINT32 WAKEUP                  :1;
    UINT32                         :29;
} CCU1CLKM3QEICFGBITFIELD;
typedef struct CCU1CLKM3QEISTATBITFIELD
{
    UINT32 RUN                     :1;
    UINT32 AUTO                    :1;
    UINT32 WAKEUP                  :1;
    UINT32                         :29;
} CCU1CLKM3QEISTATBITFIELD;
typedef struct CCU1CLKUSB0CFGBITFIELD
{
    UINT32 RUN                     :1;
    UINT32 AUTO                    :1;
    UINT32 WAKEUP                  :1;
    UINT32                         :29;
} CCU1CLKUSB0CFGBITFIELD;
typedef struct CCU1CLKUSB0STATBITFIELD
{
    UINT32 RUN                     :1;
    UINT32 AUTO                    :1;
    UINT32 WAKEUP                  :1;
    UINT32                         :29;
} CCU1CLKUSB0STATBITFIELD;
typedef struct CCU1CLKUSB1CFGBITFIELD
{
    UINT32 RUN                     :1;
    UINT32 AUTO                    :1;
    UINT32 WAKEUP                  :1;
    UINT32                         :29;
} CCU1CLKUSB1CFGBITFIELD;
typedef struct CCU1CLKUSB1STATBITFIELD
{
    UINT32 RUN                     :1;
    UINT32 AUTO                    :1;
    UINT32 WAKEUP                  :1;
    UINT32                         :29;
} CCU1CLKUSB1STATBITFIELD;
typedef struct CCU2PMBITFIELD
{
    UINT32 PD                      :1;
    UINT32                         :31;
} CCU2PMBITFIELD;
typedef struct CCU2BASESTATBITFIELD
{
    UINT32                         :1;
    UINT32 BASEUART3CLK            :1;
    UINT32 BASEUART2CLK            :1;
    UINT32 BASEUART1CLK            :1;
    UINT32 BASEUART0CLK            :1;
    UINT32 BASESSP1CLK             :1;
    UINT32 BASESSP0CLK             :1;
    UINT32                         :25;
} CCU2BASESTATBITFIELD;
typedef struct CCU2CLKAPB2UART3CFGBITFIELD
{
    UINT32 RUN                     :1;
    UINT32 AUTO                    :1;
    UINT32 WAKEUP                  :1;
    UINT32                         :29;
} CCU2CLKAPB2UART3CFGBITFIELD;
typedef struct CCU2CLKAPB2UART3STATBITFIELD
{
    UINT32 RUN                     :1;
    UINT32 AUTO                    :1;
    UINT32 WAKEUP                  :1;
    UINT32                         :29;
} CCU2CLKAPB2UART3STATBITFIELD;
typedef struct CCU2CLKAPB2UART2CFGBITFIELD
{
    UINT32 RUN                     :1;
    UINT32 AUTO                    :1;
    UINT32 WAKEUP                  :1;
    UINT32                         :29;
} CCU2CLKAPB2UART2CFGBITFIELD;
typedef struct CCU2CLKAPB2UART2STATBITFIELD
{
    UINT32 RUN                     :1;
    UINT32 AUTO                    :1;
    UINT32 WAKEUP                  :1;
    UINT32                         :29;
} CCU2CLKAPB2UART2STATBITFIELD;
typedef struct CCU2CLKAPB2UART1CFGBITFIELD
{
    UINT32 RUN                     :1;
    UINT32 AUTO                    :1;
    UINT32 WAKEUP                  :1;
    UINT32                         :29;
} CCU2CLKAPB2UART1CFGBITFIELD;
typedef struct CCU2CLKAPB2UART1STATBITFIELD
{
    UINT32 RUN                     :1;
    UINT32 AUTO                    :1;
    UINT32 WAKEUP                  :1;
    UINT32                         :29;
} CCU2CLKAPB2UART1STATBITFIELD;
typedef struct CCU2CLKAPB2UART0CFGBITFIELD
{
    UINT32 RUN                     :1;
    UINT32 AUTO                    :1;
    UINT32 WAKEUP                  :1;
    UINT32                         :29;
} CCU2CLKAPB2UART0CFGBITFIELD;
typedef struct CCU2CLKAPB2UART0STATBITFIELD
{
    UINT32 RUN                     :1;
    UINT32 AUTO                    :1;
    UINT32 WAKEUP                  :1;
    UINT32                         :29;
} CCU2CLKAPB2UART0STATBITFIELD;
typedef struct CCU2CLKAPB2SSP1CFGBITFIELD
{
    UINT32 RUN                     :1;
    UINT32 AUTO                    :1;
    UINT32 WAKEUP                  :1;
    UINT32                         :29;
} CCU2CLKAPB2SSP1CFGBITFIELD;
typedef struct CCU2CLKAPB2SSP1STATBITFIELD
{
    UINT32 RUN                     :1;
    UINT32 AUTO                    :1;
    UINT32 WAKEUP                  :1;
    UINT32                         :29;
} CCU2CLKAPB2SSP1STATBITFIELD;
typedef struct CCU2CLKAPB2SSP0CFGBITFIELD
{
    UINT32 RUN                     :1;
    UINT32 AUTO                    :1;
    UINT32 WAKEUP                  :1;
    UINT32                         :29;
} CCU2CLKAPB2SSP0CFGBITFIELD;
typedef struct CCU2CLKAPB2SSP0STATBITFIELD
{
    UINT32 RUN                     :1;
    UINT32 AUTO                    :1;
    UINT32 WAKEUP                  :1;
    UINT32                         :29;
} CCU2CLKAPB2SSP0STATBITFIELD;
typedef struct CCU2CLKSDIOCFGBITFIELD
{
    UINT32 RUN                     :1;
    UINT32 AUTO                    :1;
    UINT32 WAKEUP                  :1;
    UINT32                         :29;
} CCU2CLKSDIOCFGBITFIELD;
typedef struct CCU2CLKSDIOSTATBITFIELD
{
    UINT32 RUN                     :1;
    UINT32 AUTO                    :1;
    UINT32 WAKEUP                  :1;
    UINT32                         :29;
} CCU2CLKSDIOSTATBITFIELD;

#define REG_CCU1BASESTAT                          REG_32(0x40051004)
#define REGBITS_CCU1BASESTAT                      REGBITS_32(0x40051004, CCU1BASESTATBITFIELD)
#define REG_CCU1CLKAPB1BUSCFG                     REG_32(0x40051200)
#define REGBITS_CCU1CLKAPB1BUSCFG                 REGBITS_32(0x40051200, CCU1CLKAPB1BUSCFGBITFIELD)
#define REG_CCU1CLKAPB1BUSSTAT                    REG_32(0x40051204)
#define REGBITS_CCU1CLKAPB1BUSSTAT                REGBITS_32(0x40051204, CCU1CLKAPB1BUSSTATBITFIELD)
#define REG_CCU1CLKAPB1I2C0CFG                    REG_32(0x40051210)
#define REGBITS_CCU1CLKAPB1I2C0CFG                REGBITS_32(0x40051210, CCU1CLKAPB1I2C0CFGBITFIELD)
#define REG_CCU1CLKAPB1I2C0STAT                   REG_32(0x40051214)
#define REGBITS_CCU1CLKAPB1I2C0STAT               REGBITS_32(0x40051214, CCU1CLKAPB1I2C0STATBITFIELD)
#define REG_CCU1CLKAPB1I2SCFG                     REG_32(0x40051218)
#define REGBITS_CCU1CLKAPB1I2SCFG                 REGBITS_32(0x40051218, CCU1CLKAPB1I2SCFGBITFIELD)
#define REG_CCU1CLKAPB1I2SSTAT                    REG_32(0x4005121C)
#define REGBITS_CCU1CLKAPB1I2SSTAT                REGBITS_32(0x4005121C, CCU1CLKAPB1I2SSTATBITFIELD)
#define REG_CCU1CLKAPB1MOTOCONCFG                 REG_32(0x40051208)
#define REGBITS_CCU1CLKAPB1MOTOCONCFG             REGBITS_32(0x40051208, CCU1CLKAPB1MOTOCONCFGBITFIELD)
#define REG_CCU1CLKAPB1MOTOCONSTAT                REG_32(0x4005120C)
#define REGBITS_CCU1CLKAPB1MOTOCONSTAT            REGBITS_32(0x4005120C, CCU1CLKAPB1MOTOCONSTATBITFIELD)
#define REG_CCU1CLKAPB3ADC0CFG                    REG_32(0x40051118)
#define REGBITS_CCU1CLKAPB3ADC0CFG                REGBITS_32(0x40051118, CCU1CLKAPB3ADC0CFGBITFIELD)
#define REG_CCU1CLKAPB3ADC0STAT                   REG_32(0x4005111C)
#define REGBITS_CCU1CLKAPB3ADC0STAT               REGBITS_32(0x4005111C, CCU1CLKAPB3ADC0STATBITFIELD)
#define REG_CCU1CLKAPB3ADC1CFG                    REG_32(0x40051120)
#define REGBITS_CCU1CLKAPB3ADC1CFG                REGBITS_32(0x40051120, CCU1CLKAPB3ADC1CFGBITFIELD)
#define REG_CCU1CLKAPB3ADC1STAT                   REG_32(0x40051124)
#define REGBITS_CCU1CLKAPB3ADC1STAT               REGBITS_32(0x40051124, CCU1CLKAPB3ADC1STATBITFIELD)
#define REG_CCU1CLKAPB3BUSCFG                     REG_32(0x40051100)
#define REGBITS_CCU1CLKAPB3BUSCFG                 REGBITS_32(0x40051100, CCU1CLKAPB3BUSCFGBITFIELD)
#define REG_CCU1CLKAPB3BUSSTAT                    REG_32(0x40051104)
#define REGBITS_CCU1CLKAPB3BUSSTAT                REGBITS_32(0x40051104, CCU1CLKAPB3BUSSTATBITFIELD)
#define REG_CCU1CLKAPB3CANCFG                     REG_32(0x40051128)
#define REGBITS_CCU1CLKAPB3CANCFG                 REGBITS_32(0x40051128, CCU1CLKAPB3CANCFGBITFIELD)
#define REG_CCU1CLKAPB3CANSTAT                    REG_32(0x4005112C)
#define REGBITS_CCU1CLKAPB3CANSTAT                REGBITS_32(0x4005112C, CCU1CLKAPB3CANSTATBITFIELD)
#define REG_CCU1CLKAPB3DACCFG                     REG_32(0x40051110)
#define REGBITS_CCU1CLKAPB3DACCFG                 REGBITS_32(0x40051110, CCU1CLKAPB3DACCFGBITFIELD)
#define REG_CCU1CLKAPB3DACSTAT                    REG_32(0x40051114)
#define REGBITS_CCU1CLKAPB3DACSTAT                REGBITS_32(0x40051114, CCU1CLKAPB3DACSTATBITFIELD)
#define REG_CCU1CLKAPB3I2C1CFG                    REG_32(0x40051108)
#define REGBITS_CCU1CLKAPB3I2C1CFG                REGBITS_32(0x40051108, CCU1CLKAPB3I2C1CFGBITFIELD)
#define REG_CCU1CLKAPB3I2C1STAT                   REG_32(0x4005110C)
#define REGBITS_CCU1CLKAPB3I2C1STAT               REGBITS_32(0x4005110C, CCU1CLKAPB3I2C1STATBITFIELD)
#define REG_CCU1CLKM3AESCFG                       REG_32(0x40051460)
#define REGBITS_CCU1CLKM3AESCFG                   REGBITS_32(0x40051460, CCU1CLKM3AESCFGBITFIELD)
#define REG_CCU1CLKM3AESSTAT                      REG_32(0x40051464)
#define REGBITS_CCU1CLKM3AESSTAT                  REGBITS_32(0x40051464, CCU1CLKM3AESSTATBITFIELD)
#define REG_CCU1CLKM3BUSCFG                       REG_32(0x40051400)
#define REGBITS_CCU1CLKM3BUSCFG                   REGBITS_32(0x40051400, CCU1CLKM3BUSCFGBITFIELD)
#define REG_CCU1CLKM3BUSSTAT                      REG_32(0x40051404)
#define REGBITS_CCU1CLKM3BUSSTAT                  REGBITS_32(0x40051404, CCU1CLKM3BUSSTATBITFIELD)
#define REG_CCU1CLKM3CREGCFG                      REG_32(0x40051538)
#define REGBITS_CCU1CLKM3CREGCFG                  REGBITS_32(0x40051538, CCU1CLKM3CREGCFGBITFIELD)
#define REG_CCU1CLKM3CREGSTAT                     REG_32(0x4005153C)
#define REGBITS_CCU1CLKM3CREGSTAT                 REGBITS_32(0x4005153C, CCU1CLKM3CREGSTATBITFIELD)
#define REG_CCU1CLKM3DMACFG                       REG_32(0x40051440)
#define REGBITS_CCU1CLKM3DMACFG                   REGBITS_32(0x40051440, CCU1CLKM3DMACFGBITFIELD)
#define REG_CCU1CLKM3DMASTAT                      REG_32(0x40051444)
#define REGBITS_CCU1CLKM3DMASTAT                  REGBITS_32(0x40051444, CCU1CLKM3DMASTATBITFIELD)
#define REG_CCU1CLKM3EMCCFG                       REG_32(0x40051430)
#define REGBITS_CCU1CLKM3EMCCFG                   REGBITS_32(0x40051430, CCU1CLKM3EMCCFGBITFIELD)
#define REG_CCU1CLKM3EMCDIVCFG                    REG_32(0x40051478)
#define REGBITS_CCU1CLKM3EMCDIVCFG                REGBITS_32(0x40051478, CCU1CLKM3EMCDIVCFGBITFIELD)
#define REG_CCU1CLKM3EMCDIVSTAT                   REG_32(0x4005147C)
#define REGBITS_CCU1CLKM3EMCDIVSTAT               REGBITS_32(0x4005147C, CCU1CLKM3EMCDIVSTATBITFIELD)
#define REG_CCU1CLKM3EMCSTAT                      REG_32(0x40051434)
#define REGBITS_CCU1CLKM3EMCSTAT                  REGBITS_32(0x40051434, CCU1CLKM3EMCSTATBITFIELD)
#define REG_CCU1CLKM3ETHERNETCFG                  REG_32(0x40051420)
#define REGBITS_CCU1CLKM3ETHERNETCFG              REGBITS_32(0x40051420, CCU1CLKM3ETHERNETCFGBITFIELD)
#define REG_CCU1CLKM3ETHERNETSTAT                 REG_32(0x40051424)
#define REGBITS_CCU1CLKM3ETHERNETSTAT             REGBITS_32(0x40051424, CCU1CLKM3ETHERNETSTATBITFIELD)
#define REG_CCU1CLKM3GPIOCFG                      REG_32(0x40051410)
#define REGBITS_CCU1CLKM3GPIOCFG                  REGBITS_32(0x40051410, CCU1CLKM3GPIOCFGBITFIELD)
#define REG_CCU1CLKM3GPIOSTAT                     REG_32(0x40051414)
#define REGBITS_CCU1CLKM3GPIOSTAT                 REGBITS_32(0x40051414, CCU1CLKM3GPIOSTATBITFIELD)
#define REG_CCU1CLKM3LCDCFG                       REG_32(0x40051418)
#define REGBITS_CCU1CLKM3LCDCFG                   REGBITS_32(0x40051418, CCU1CLKM3LCDCFGBITFIELD)
#define REG_CCU1CLKM3LCDSTAT                      REG_32(0x4005141C)
#define REGBITS_CCU1CLKM3LCDSTAT                  REGBITS_32(0x4005141C, CCU1CLKM3LCDSTATBITFIELD)
#define REG_CCU1CLKM3M3CORECFG                    REG_32(0x40051448)
#define REGBITS_CCU1CLKM3M3CORECFG                REGBITS_32(0x40051448, CCU1CLKM3M3CORECFGBITFIELD)
#define REG_CCU1CLKM3M3CORESTAT                   REG_32(0x4005144C)
#define REGBITS_CCU1CLKM3M3CORESTAT               REGBITS_32(0x4005144C, CCU1CLKM3M3CORESTATBITFIELD)
#define REG_CCU1CLKM3QEICFG                       REG_32(0x40051630)
#define REGBITS_CCU1CLKM3QEICFG                   REGBITS_32(0x40051630, CCU1CLKM3QEICFGBITFIELD)
#define REG_CCU1CLKM3QEISTAT                      REG_32(0x40051634)
#define REGBITS_CCU1CLKM3QEISTAT                  REGBITS_32(0x40051634, CCU1CLKM3QEISTATBITFIELD)
#define REG_CCU1CLKM3RITIMERCFG                   REG_32(0x40051600)
#define REGBITS_CCU1CLKM3RITIMERCFG               REGBITS_32(0x40051600, CCU1CLKM3RITIMERCFGBITFIELD)
#define REG_CCU1CLKM3RITIMERSTAT                  REG_32(0x40051604)
#define REGBITS_CCU1CLKM3RITIMERSTAT              REGBITS_32(0x40051604, CCU1CLKM3RITIMERSTATBITFIELD)
#define REG_CCU1CLKM3SCTCFG                       REG_32(0x40051468)
#define REGBITS_CCU1CLKM3SCTCFG                   REGBITS_32(0x40051468, CCU1CLKM3SCTCFGBITFIELD)
#define REG_CCU1CLKM3SCTSTAT                      REG_32(0x4005146C)
#define REGBITS_CCU1CLKM3SCTSTAT                  REGBITS_32(0x4005146C, CCU1CLKM3SCTSTATBITFIELD)
#define REG_CCU1CLKM3SCUCFG                       REG_32(0x40051530)
#define REGBITS_CCU1CLKM3SCUCFG                   REGBITS_32(0x40051530, CCU1CLKM3SCUCFGBITFIELD)
#define REG_CCU1CLKM3SCUSTAT                      REG_32(0x40051534)
#define REGBITS_CCU1CLKM3SCUSTAT                  REGBITS_32(0x40051534, CCU1CLKM3SCUSTATBITFIELD)
#define REG_CCU1CLKM3SDIOCFG                      REG_32(0x40051438)
#define REGBITS_CCU1CLKM3SDIOCFG                  REGBITS_32(0x40051438, CCU1CLKM3SDIOCFGBITFIELD)
#define REG_CCU1CLKM3SDIOSTAT                     REG_32(0x4005143C)
#define REGBITS_CCU1CLKM3SDIOSTAT                 REGBITS_32(0x4005143C, CCU1CLKM3SDIOSTATBITFIELD)
#define REG_CCU1CLKM3SPIFICFG                     REG_32(0x40051408)
#define REGBITS_CCU1CLKM3SPIFICFG                 REGBITS_32(0x40051408, CCU1CLKM3SPIFICFGBITFIELD)
#define REG_CCU1CLKM3SPIFISTAT                    REG_32(0x4005140C)
#define REGBITS_CCU1CLKM3SPIFISTAT                REGBITS_32(0x4005140C, CCU1CLKM3SPIFISTATBITFIELD)
#define REG_CCU1CLKM3SSP0CFG                      REG_32(0x40051518)
#define REGBITS_CCU1CLKM3SSP0CFG                  REGBITS_32(0x40051518, CCU1CLKM3SSP0CFGBITFIELD)
#define REG_CCU1CLKM3SSP0STAT                     REG_32(0x4005151C)
#define REGBITS_CCU1CLKM3SSP0STAT                 REGBITS_32(0x4005151C, CCU1CLKM3SSP0STATBITFIELD)
#define REG_CCU1CLKM3SSP1CFG                      REG_32(0x40051628)
#define REGBITS_CCU1CLKM3SSP1CFG                  REGBITS_32(0x40051628, CCU1CLKM3SSP1CFGBITFIELD)
#define REG_CCU1CLKM3SSP1STAT                     REG_32(0x4005162C)
#define REGBITS_CCU1CLKM3SSP1STAT                 REGBITS_32(0x4005162C, CCU1CLKM3SSP1STATBITFIELD)
#define REG_CCU1CLKM3TIMER0CFG                    REG_32(0x40051520)
#define REGBITS_CCU1CLKM3TIMER0CFG                REGBITS_32(0x40051520, CCU1CLKM3TIMER0CFGBITFIELD)
#define REG_CCU1CLKM3TIMER0STAT                   REG_32(0x40051524)
#define REGBITS_CCU1CLKM3TIMER0STAT               REGBITS_32(0x40051524, CCU1CLKM3TIMER0STATBITFIELD)
#define REG_CCU1CLKM3TIMER1CFG                    REG_32(0x40051528)
#define REGBITS_CCU1CLKM3TIMER1CFG                REGBITS_32(0x40051528, CCU1CLKM3TIMER1CFGBITFIELD)
#define REG_CCU1CLKM3TIMER1STAT                   REG_32(0x4005152C)
#define REGBITS_CCU1CLKM3TIMER1STAT               REGBITS_32(0x4005152C, CCU1CLKM3TIMER1STATBITFIELD)
#define REG_CCU1CLKM3TIMER2CFG                    REG_32(0x40051618)
#define REGBITS_CCU1CLKM3TIMER2CFG                REGBITS_32(0x40051618, CCU1CLKM3TIMER2CFGBITFIELD)
#define REG_CCU1CLKM3TIMER2STAT                   REG_32(0x4005161C)
#define REGBITS_CCU1CLKM3TIMER2STAT               REGBITS_32(0x4005161C, CCU1CLKM3TIMER2STATBITFIELD)
#define REG_CCU1CLKM3TIMER3CFG                    REG_32(0x40051620)
#define REGBITS_CCU1CLKM3TIMER3CFG                REGBITS_32(0x40051620, CCU1CLKM3TIMER3CFGBITFIELD)
#define REG_CCU1CLKM3TIMER3STAT                   REG_32(0x40051624)
#define REGBITS_CCU1CLKM3TIMER3STAT               REGBITS_32(0x40051624, CCU1CLKM3TIMER3STATBITFIELD)
#define REG_CCU1CLKM3UART1CFG                     REG_32(0x40051510)
#define REGBITS_CCU1CLKM3UART1CFG                 REGBITS_32(0x40051510, CCU1CLKM3UART1CFGBITFIELD)
#define REG_CCU1CLKM3UART1STAT                    REG_32(0x40051514)
#define REGBITS_CCU1CLKM3UART1STAT                REGBITS_32(0x40051514, CCU1CLKM3UART1STATBITFIELD)
#define REG_CCU1CLKM3USART0CFG                    REG_32(0x40051508)
#define REGBITS_CCU1CLKM3USART0CFG                REGBITS_32(0x40051508, CCU1CLKM3USART0CFGBITFIELD)
#define REG_CCU1CLKM3USART0STAT                   REG_32(0x4005150C)
#define REGBITS_CCU1CLKM3USART0STAT               REGBITS_32(0x4005150C, CCU1CLKM3USART0STATBITFIELD)
#define REG_CCU1CLKM3USART2CFG                    REG_32(0x40051608)
#define REGBITS_CCU1CLKM3USART2CFG                REGBITS_32(0x40051608, CCU1CLKM3USART2CFGBITFIELD)
#define REG_CCU1CLKM3USART2STAT                   REG_32(0x4005160C)
#define REGBITS_CCU1CLKM3USART2STAT               REGBITS_32(0x4005160C, CCU1CLKM3USART2STATBITFIELD)
#define REG_CCU1CLKM3USART3CFG                    REG_32(0x40051610)
#define REGBITS_CCU1CLKM3USART3CFG                REGBITS_32(0x40051610, CCU1CLKM3USART3CFGBITFIELD)
#define REG_CCU1CLKM3USART3STAT                   REG_32(0x40051614)
#define REGBITS_CCU1CLKM3USART3STAT               REGBITS_32(0x40051614, CCU1CLKM3USART3STATBITFIELD)
#define REG_CCU1CLKM3USB0CFG                      REG_32(0x40051428)
#define REGBITS_CCU1CLKM3USB0CFG                  REGBITS_32(0x40051428, CCU1CLKM3USB0CFGBITFIELD)
#define REG_CCU1CLKM3USB0STAT                     REG_32(0x4005142C)
#define REGBITS_CCU1CLKM3USB0STAT                 REGBITS_32(0x4005142C, CCU1CLKM3USB0STATBITFIELD)
#define REG_CCU1CLKM3USB1CFG                      REG_32(0x40051470)
#define REGBITS_CCU1CLKM3USB1CFG                  REGBITS_32(0x40051470, CCU1CLKM3USB1CFGBITFIELD)
#define REG_CCU1CLKM3USB1STAT                     REG_32(0x40051474)
#define REGBITS_CCU1CLKM3USB1STAT                 REGBITS_32(0x40051474, CCU1CLKM3USB1STATBITFIELD)
#define REG_CCU1CLKM3WWDTCFG                      REG_32(0x40051500)
#define REGBITS_CCU1CLKM3WWDTCFG                  REGBITS_32(0x40051500, CCU1CLKM3WWDTCFGBITFIELD)
#define REG_CCU1CLKM3WWDTSTAT                     REG_32(0x40051504)
#define REGBITS_CCU1CLKM3WWDTSTAT                 REGBITS_32(0x40051504, CCU1CLKM3WWDTSTATBITFIELD)
#define REG_CCU1CLKSPIFICFG                       REG_32(0x40051300)
#define REGBITS_CCU1CLKSPIFICFG                   REGBITS_32(0x40051300, CCU1CLKSPIFICFGBITFIELD)
#define REG_CCU1CLKSPIFISTAT                      REG_32(0x40051304)
#define REGBITS_CCU1CLKSPIFISTAT                  REGBITS_32(0x40051304, CCU1CLKSPIFISTATBITFIELD)
#define REG_CCU1CLKUSB0CFG                        REG_32(0x40051800)
#define REGBITS_CCU1CLKUSB0CFG                    REGBITS_32(0x40051800, CCU1CLKUSB0CFGBITFIELD)
#define REG_CCU1CLKUSB0STAT                       REG_32(0x40051804)
#define REGBITS_CCU1CLKUSB0STAT                   REGBITS_32(0x40051804, CCU1CLKUSB0STATBITFIELD)
#define REG_CCU1CLKUSB1CFG                        REG_32(0x40051900)
#define REGBITS_CCU1CLKUSB1CFG                    REGBITS_32(0x40051900, CCU1CLKUSB1CFGBITFIELD)
#define REG_CCU1CLKUSB1STAT                       REG_32(0x40051904)
#define REGBITS_CCU1CLKUSB1STAT                   REGBITS_32(0x40051904, CCU1CLKUSB1STATBITFIELD)
#define REG_CCU1PM                                REG_32(0x40051000)
#define REGBITS_CCU1PM                            REGBITS_32(0x40051000, CCU1PMBITFIELD)
#define REG_CCU2BASESTAT                          REG_32(0x40052004)
#define REGBITS_CCU2BASESTAT                      REGBITS_32(0x40052004, CCU2BASESTATBITFIELD)
#define REG_CCU2CLKAPB2SSP0CFG                    REG_32(0x40052700)
#define REGBITS_CCU2CLKAPB2SSP0CFG                REGBITS_32(0x40052700, CCU2CLKAPB2SSP0CFGBITFIELD)
#define REG_CCU2CLKAPB2SSP0STAT                   REG_32(0x40052704)
#define REGBITS_CCU2CLKAPB2SSP0STAT               REGBITS_32(0x40052704, CCU2CLKAPB2SSP0STATBITFIELD)
#define REG_CCU2CLKAPB2SSP1CFG                    REG_32(0x40052600)
#define REGBITS_CCU2CLKAPB2SSP1CFG                REGBITS_32(0x40052600, CCU2CLKAPB2SSP1CFGBITFIELD)
#define REG_CCU2CLKAPB2SSP1STAT                   REG_32(0x40052604)
#define REGBITS_CCU2CLKAPB2SSP1STAT               REGBITS_32(0x40052604, CCU2CLKAPB2SSP1STATBITFIELD)
#define REG_CCU2CLKAPB2UART0CFG                   REG_32(0x40052500)
#define REGBITS_CCU2CLKAPB2UART0CFG               REGBITS_32(0x40052500, CCU2CLKAPB2UART0CFGBITFIELD)
#define REG_CCU2CLKAPB2UART0STAT                  REG_32(0x40052504)
#define REGBITS_CCU2CLKAPB2UART0STAT              REGBITS_32(0x40052504, CCU2CLKAPB2UART0STATBITFIELD)
#define REG_CCU2CLKAPB2UART1CFG                   REG_32(0x40052400)
#define REGBITS_CCU2CLKAPB2UART1CFG               REGBITS_32(0x40052400, CCU2CLKAPB2UART1CFGBITFIELD)
#define REG_CCU2CLKAPB2UART1STAT                  REG_32(0x40052404)
#define REGBITS_CCU2CLKAPB2UART1STAT              REGBITS_32(0x40052404, CCU2CLKAPB2UART1STATBITFIELD)
#define REG_CCU2CLKAPB2UART2CFG                   REG_32(0x40052300)
#define REGBITS_CCU2CLKAPB2UART2CFG               REGBITS_32(0x40052300, CCU2CLKAPB2UART2CFGBITFIELD)
#define REG_CCU2CLKAPB2UART2STAT                  REG_32(0x40052304)
#define REGBITS_CCU2CLKAPB2UART2STAT              REGBITS_32(0x40052304, CCU2CLKAPB2UART2STATBITFIELD)
#define REG_CCU2CLKAPB2UART3CFG                   REG_32(0x40052200)
#define REGBITS_CCU2CLKAPB2UART3CFG               REGBITS_32(0x40052200, CCU2CLKAPB2UART3CFGBITFIELD)
#define REG_CCU2CLKAPB2UART3STAT                  REG_32(0x40052204)
#define REGBITS_CCU2CLKAPB2UART3STAT              REGBITS_32(0x40052204, CCU2CLKAPB2UART3STATBITFIELD)
#define REG_CCU2CLKSDIOCFG                        REG_32(0x40052800)
#define REGBITS_CCU2CLKSDIOCFG                    REGBITS_32(0x40052800, CCU2CLKSDIOCFGBITFIELD)
#define REG_CCU2CLKSDIOSTAT                       REG_32(0x40052804)
#define REGBITS_CCU2CLKSDIOSTAT                   REGBITS_32(0x40052804, CCU2CLKSDIOSTATBITFIELD)
#define REG_CCU2PM                                REG_32(0x40052000)
#define REGBITS_CCU2PM                            REGBITS_32(0x40052000, CCU2PMBITFIELD)

#endif /* MCU_CCU_H__ */
