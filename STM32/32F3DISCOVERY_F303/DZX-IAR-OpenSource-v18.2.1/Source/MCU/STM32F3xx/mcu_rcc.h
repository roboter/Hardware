/*******************************************************************************************************************************************

    DZX | STM32F3xx | RCC                                                                                                 VERSION 18.2.1
    ------------------------------------------------------------------------------------------------------------------------------------

    This is part of the MCU peripheral drivers and provides support for reset and clock control.

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
#ifndef MCU_RCC_H__
#define MCU_RCC_H__

#include "Kernel/kernel.h"
/*******************************************************************************************************************************************
    REGISTER DEFINITIONS
*******************************************************************************************************************************************/
#define BASE_RCC                0x40021000

/*******************************************************************************************************************************************

    CR: Clock control register

*******************************************************************************************************************************************/
typedef struct RCCCRBITFIELD {
    UINT32 HSION                :1;                             /* Internal High Speed clock enable */
    UINT32 HSIRDY               :1;                             /* Internal High Speed clock ready flag */
    UINT32                      :1;
    UINT32 HSITRIM              :5;                             /* Internal High Speed clock trimming */
    UINT32 HSICAL               :8;                             /* Internal High Speed clock Calibration */
    UINT32 HSEON                :1;                             /* External High Speed clock enable */
    UINT32 HSERDY               :1;                             /* External High Speed clock ready flag */
    UINT32 HSEBYP               :1;                             /* External High Speed clock Bypass */
    UINT32 CSSON                :1;                             /* Clock Security System enable */
    UINT32                      :4;
    UINT32 PLLON                :1;                             /* PLL enable */
    UINT32 PLLRDY               :1;                             /* PLL clock ready flag */
    UINT32                      :6;
} RCCCRBITFIELD;

#define REG_RCCCR               REG_32(BASE_RCC + 0x000)
#define REGBITS_RCCCR           REGBITS_32(BASE_RCC + 0x000, RCCCRBITFIELD)

/*******************************************************************************************************************************************

    CFGR: Clock configuration register

*******************************************************************************************************************************************/
typedef struct RCCCFGRBITFIELD {
    UINT32 SW                   :2;                             /* System clock Switch */
    UINT32 SWS                  :2;                             /* System Clock Switch Status */
    UINT32 HPRE                 :4;                             /* AHB prescaler */
    UINT32 PPRE1                :3;                             /* APB Low speed prescaler (APB1) */
    UINT32 PPRE2                :3;                             /* APB high speed prescaler (APB2) */
    UINT32                      :2;
    UINT32 PLLSRC               :1;                             /* PLL entry clock source */
    UINT32 PLLXTPRE             :1;                             /* HSE divider for PLL entry */
    UINT32 PLLMUL               :4;                             /* PLL Multiplication Factor */
    UINT32 USBPRES              :1;                             /* USB prescaler */
    UINT32                      :1;
    UINT32 MCO                  :3;                             /* Microcontroller clock output */
    UINT32                      :1;
    UINT32 MCOF                 :1;                             /* Microcontroller Clock Output Flag */
    UINT32 I2SSRC               :1;                             /* I2S external clock source selection */
    UINT32                      :8;
} RCCCFGRBITFIELD;

#define REG_RCCCFGR             REG_32(BASE_RCC + 0x004)
#define REGBITS_RCCCFGR         REGBITS_32(BASE_RCC + 0x004, RCCCFGRBITFIELD)

/*******************************************************************************************************************************************

    CIR: Clock interrupt register

*******************************************************************************************************************************************/
typedef struct RCCCIRBITFIELD {
    UINT32 LSIRDYF              :1;                             /* LSI Ready Interrupt flag */
    UINT32 LSERDYF              :1;                             /* LSE Ready Interrupt flag */
    UINT32 HSIRDYF              :1;                             /* HSI Ready Interrupt flag */
    UINT32 HSERDYF              :1;                             /* HSE Ready Interrupt flag */
    UINT32 PLLRDYF              :1;                             /* PLL Ready Interrupt flag */
    UINT32                      :2;
    UINT32 CSSF                 :1;                             /* Clock Security System Interrupt flag */
    UINT32 LSIRDYIE             :1;                             /* LSI Ready Interrupt Enable */
    UINT32 LSERDYIE             :1;                             /* LSE Ready Interrupt Enable */
    UINT32 HSIRDYIE             :1;                             /* HSI Ready Interrupt Enable */
    UINT32 HSERDYIE             :1;                             /* HSE Ready Interrupt Enable */
    UINT32 PLLRDYIE             :1;                             /* PLL Ready Interrupt Enable */
    UINT32                      :3;
    UINT32 LSIRDYC              :1;                             /* LSI Ready Interrupt Clear */
    UINT32 LSERDYC              :1;                             /* LSE Ready Interrupt Clear */
    UINT32 HSIRDYC              :1;                             /* HSI Ready Interrupt Clear */
    UINT32 HSERDYC              :1;                             /* HSE Ready Interrupt Clear */
    UINT32 PLLRDYC              :1;                             /* PLL Ready Interrupt Clear */
    UINT32                      :2;
    UINT32 CSSC                 :1;                             /* Clock security system interrupt clear */
    UINT32                      :8;
} RCCCIRBITFIELD;

#define REG_RCCCIR              REG_32(BASE_RCC + 0x008)
#define REGBITS_RCCCIR          REGBITS_32(BASE_RCC + 0x008, RCCCIRBITFIELD)

/*******************************************************************************************************************************************

    APB2RSTR: APB2 peripheral reset register

*******************************************************************************************************************************************/
typedef struct RCCAPB2RSTRBITFIELD {
    UINT32 SYSCFGRST            :1;                             /* SYSCFG and COMP reset */
    UINT32                      :10;
    UINT32 TIM1RST              :1;                             /* TIM1 timer reset */
    UINT32 SPI1RST              :1;                             /* SPI 1 reset */
    UINT32 TIM8RST              :1;                             /* TIM8 timer reset */
    UINT32 USART1RST            :1;                             /* USART1 reset */
    UINT32                      :1;
    UINT32 TIM15RST             :1;                             /* TIM15 timer reset */
    UINT32 TIM16RST             :1;                             /* TIM16 timer reset */
    UINT32 TIM17RST             :1;                             /* TIM17 timer reset */
    UINT32                      :13;
} RCCAPB2RSTRBITFIELD;

#define REG_RCCAPB2RSTR         REG_32(BASE_RCC + 0x00C)
#define REGBITS_RCCAPB2RSTR     REGBITS_32(BASE_RCC + 0x00C, RCCAPB2RSTRBITFIELD)

/*******************************************************************************************************************************************

    APB1RSTR: APB1 peripheral reset register

*******************************************************************************************************************************************/
typedef struct RCCAPB1RSTRBITFIELD {
    UINT32 TIM2RST              :1;                             /* Timer 2 reset */
    UINT32 TIM3RST              :1;                             /* Timer 3 reset */
    UINT32 TIM4RST              :1;                             /* Timer 14 reset */
    UINT32                      :1;
    UINT32 TIM6RST              :1;                             /* Timer 6 reset */
    UINT32 TIM7RST              :1;                             /* Timer 7 reset */
    UINT32                      :5;
    UINT32 WWDGRST              :1;                             /* Window watchdog reset */
    UINT32                      :2;
    UINT32 SPI2RST              :1;                             /* SPI2 reset */
    UINT32 SPI3RST              :1;                             /* SPI3 reset */
    UINT32                      :1;
    UINT32 USART2RST            :1;                             /* USART 2 reset */
    UINT32 USART3RST            :1;                             /* USART3 reset */
    UINT32 UART4RST             :1;                             /* UART 4 reset */
    UINT32 UART5RST             :1;                             /* UART 5 reset */
    UINT32 I2C1RST              :1;                             /* I2C1 reset */
    UINT32 I2C2RST              :1;                             /* I2C2 reset */
    UINT32 USBRST               :1;                             /* USB reset */
    UINT32                      :1;
    UINT32 CANRST               :1;                             /* CAN reset */
    UINT32                      :2;
    UINT32 PWRRST               :1;                             /* Power interface reset */
    UINT32 DACRST               :1;                             /* DAC interface reset */
    UINT32                      :2;
} RCCAPB1RSTRBITFIELD;

#define REG_RCCAPB1RSTR         REG_32(BASE_RCC + 0x010)
#define REGBITS_RCCAPB1RSTR     REGBITS_32(BASE_RCC + 0x010, RCCAPB1RSTRBITFIELD)

/*******************************************************************************************************************************************

    AHBENR: AHB Peripheral Clock enable register

*******************************************************************************************************************************************/
typedef struct RCCAHBENRBITFIELD {
    UINT32 DMAEN                :1;                             /* DMA1 clock enable */
    UINT32 DMA2EN               :1;                             /* DMA2 clock enable */
    UINT32 SRAMEN               :1;                             /* SRAM interface clock enable */
    UINT32                      :1;
    UINT32 FLITFEN              :1;                             /* FLITF clock enable */
    UINT32                      :1;
    UINT32 CRCEN                :1;                             /* CRC clock enable */
    UINT32                      :10;
    UINT32 IOPAEN               :1;                             /* I/O port A clock enable */
    UINT32 IOPBEN               :1;                             /* I/O port B clock enable */
    UINT32 IOPCEN               :1;                             /* I/O port C clock enable */
    UINT32 IOPDEN               :1;                             /* I/O port D clock enable */
    UINT32 IOPEEN               :1;                             /* I/O port E clock enable */
    UINT32 IOPFEN               :1;                             /* I/O port F clock enable */
    UINT32                      :1;
    UINT32 TSCEN                :1;                             /* Touch sensing controller clock enable */
    UINT32                      :3;
    UINT32 ADC12EN              :1;                             /* ADC1 and ADC2 clock enable */
    UINT32 ADC34EN              :1;                             /* ADC3 and ADC4 clock enable */
    UINT32                      :2;
} RCCAHBENRBITFIELD;

#define REG_RCCAHBENR           REG_32(BASE_RCC + 0x014)
#define REGBITS_RCCAHBENR       REGBITS_32(BASE_RCC + 0x014, RCCAHBENRBITFIELD)

/*******************************************************************************************************************************************

    APB2ENR: APB2 peripheral clock enable register

*******************************************************************************************************************************************/
typedef struct RCCAPB2ENRBITFIELD {
    UINT32 SYSCFGEN             :1;                             /* SYSCFG clock enable */
    UINT32                      :10;
    UINT32 TIM1EN               :1;                             /* TIM1 Timer clock enable */
    UINT32 SPI1EN               :1;                             /* SPI 1 clock enable */
    UINT32 TIM8EN               :1;                             /* TIM8 Timer clock enable */
    UINT32 USART1EN             :1;                             /* USART1 clock enable */
    UINT32                      :1;
    UINT32 TIM15EN              :1;                             /* TIM15 timer clock enable */
    UINT32 TIM16EN              :1;                             /* TIM16 timer clock enable */
    UINT32 TIM17EN              :1;                             /* TIM17 timer clock enable */
    UINT32                      :13;
} RCCAPB2ENRBITFIELD;

#define REG_RCCAPB2ENR          REG_32(BASE_RCC + 0x018)
#define REGBITS_RCCAPB2ENR      REGBITS_32(BASE_RCC + 0x018, RCCAPB2ENRBITFIELD)

/*******************************************************************************************************************************************

    APB1ENR: APB1 peripheral clock enable register

*******************************************************************************************************************************************/
typedef struct RCCAPB1ENRBITFIELD {
    UINT32 TIM2EN               :1;                             /* Timer 2 clock enable */
    UINT32 TIM3EN               :1;                             /* Timer 3 clock enable */
    UINT32 TIM4EN               :1;                             /* Timer 4 clock enable */
    UINT32                      :1;
    UINT32 TIM6EN               :1;                             /* Timer 6 clock enable */
    UINT32 TIM7EN               :1;                             /* Timer 7 clock enable */
    UINT32                      :5;
    UINT32 WWDGEN               :1;                             /* Window watchdog clock enable */
    UINT32                      :2;
    UINT32 SPI2EN               :1;                             /* SPI 2 clock enable */
    UINT32 SPI3EN               :1;                             /* SPI 3 clock enable */
    UINT32                      :1;
    UINT32 USART2EN             :1;                             /* USART 2 clock enable */
    UINT32                      :3;
    UINT32 I2C1EN               :1;                             /* I2C 1 clock enable */
    UINT32 I2C2EN               :1;                             /* I2C 2 clock enable */
    UINT32 USBEN                :1;                             /* USB clock enable */
    UINT32                      :1;
    UINT32 CANEN                :1;                             /* CAN clock enable */
    UINT32                      :2;
    UINT32 PWREN                :1;                             /* Power interface clock enable */
    UINT32 DACEN                :1;                             /* DAC interface clock enable */
    UINT32                      :2;
} RCCAPB1ENRBITFIELD;

#define REG_RCCAPB1ENR          REG_32(BASE_RCC + 0x01C)
#define REGBITS_RCCAPB1ENR      REGBITS_32(BASE_RCC + 0x01C, RCCAPB1ENRBITFIELD)

/*******************************************************************************************************************************************

    BDCR: Backup domain control register

*******************************************************************************************************************************************/
typedef struct RCCBDCRBITFIELD {
    UINT32 LSEON                :1;                             /* External Low Speed oscillator enable */
    UINT32 LSERDY               :1;                             /* External Low Speed oscillator ready */
    UINT32 LSEBYP               :1;                             /* External Low Speed oscillator bypass */
    UINT32 LSEDRV               :2;                             /* LSE oscillator drive capability */
    UINT32                      :3;
    UINT32 RTCSEL               :2;                             /* RTC clock source selection */
    UINT32                      :5;
    UINT32 RTCEN                :1;                             /* RTC clock enable */
    UINT32 BDRST                :1;                             /* Backup domain software reset */
    UINT32                      :15;
} RCCBDCRBITFIELD;

#define REG_RCCBDCR             REG_32(BASE_RCC + 0x020)
#define REGBITS_RCCBDCR         REGBITS_32(BASE_RCC + 0x020, RCCBDCRBITFIELD)

/*******************************************************************************************************************************************

    CSR: Control/status register

*******************************************************************************************************************************************/
typedef struct RCCCSRBITFIELD {
    UINT32 LSION                :1;                             /* Internal low speed oscillator enable */
    UINT32 LSIRDY               :1;                             /* Internal low speed oscillator ready */
    UINT32                      :22;
    UINT32 RMVF                 :1;                             /* Remove reset flag */
    UINT32 OBLRSTF              :1;                             /* Option byte loader reset flag */
    UINT32 PINRSTF              :1;                             /* PIN reset flag */
    UINT32 PORRSTF              :1;                             /* POR/PDR reset flag */
    UINT32 SFTRSTF              :1;                             /* Software reset flag */
    UINT32 IWDGRSTF             :1;                             /* Independent watchdog reset flag */
    UINT32 WWDGRSTF             :1;                             /* Window watchdog reset flag */
    UINT32 LPWRRSTF             :1;                             /* Low-power reset flag */
} RCCCSRBITFIELD;

#define REG_RCCCSR              REG_32(BASE_RCC + 0x024)
#define REGBITS_RCCCSR          REGBITS_32(BASE_RCC + 0x024, RCCCSRBITFIELD)

/*******************************************************************************************************************************************

    AHBRSTR: AHB peripheral reset register

*******************************************************************************************************************************************/
typedef struct RCCAHBRSTRBITFIELD {
    UINT32                      :17;
    UINT32 IOPARST              :1;                             /* I/O port A reset */
    UINT32 IOPBRST              :1;                             /* I/O port B reset */
    UINT32 IOPCRST              :1;                             /* I/O port C reset */
    UINT32 IOPDRST              :1;                             /* I/O port D reset */
    UINT32 IOPERST              :1;                             /* I/O port E reset */
    UINT32 IOPFRST              :1;                             /* I/O port F reset */
    UINT32                      :1;
    UINT32 TSCRST               :1;                             /* Touch sensing controller reset */
    UINT32                      :3;
    UINT32 ADC12RST             :1;                             /* ADC1 and ADC2 reset */
    UINT32 ADC34RST             :1;                             /* ADC3 and ADC4 reset */
    UINT32                      :2;
} RCCAHBRSTRBITFIELD;

#define REG_RCCAHBRSTR          REG_32(BASE_RCC + 0x028)
#define REGBITS_RCCAHBRSTR      REGBITS_32(BASE_RCC + 0x028, RCCAHBRSTRBITFIELD)

/*******************************************************************************************************************************************

    CFGR2: Clock configuration register 2

*******************************************************************************************************************************************/
typedef struct RCCCFGR2BITFIELD {
    UINT32 PREDIV               :4;                             /* PREDIV division factor */
    UINT32 ADC12PRES            :5;                             /* ADC1 and ADC2 prescaler */
    UINT32 ADC34PRES            :5;                             /* ADC3 and ADC4 prescaler */
    UINT32                      :18;
} RCCCFGR2BITFIELD;

#define REG_RCCCFGR2            REG_32(BASE_RCC + 0x02C)
#define REGBITS_RCCCFGR2        REGBITS_32(BASE_RCC + 0x02C, RCCCFGR2BITFIELD)

/*******************************************************************************************************************************************

    CFGR3: Clock configuration register 3

*******************************************************************************************************************************************/
typedef struct RCCCFGR3BITFIELD {
    UINT32 USART1SW             :2;                             /* USART1 clock source selection */
    UINT32                      :2;
    UINT32 I2C1SW               :1;                             /* I2C1 clock source selection */
    UINT32 I2C2SW               :1;                             /* I2C2 clock source selection */
    UINT32                      :10;
    UINT32 USART2SW             :2;                             /* USART2 clock source selection */
    UINT32 USART3SW             :2;                             /* USART3 clock source selection */
    UINT32 TIM1SW               :1;                             /* Timer1 clock source selection */
    UINT32 TIM8SW               :1;                             /* Timer8 clock source selection */
    UINT32                      :10;
    UINT32 UART4SW              :2;                             /* UART4 clock source selection */
    UINT32 UART5SW              :2;                             /* UART5 clock source selection */
    UINT32                      :8;
} RCCCFGR3BITFIELD;

#define REG_RCCCFGR3            REG_32(BASE_RCC + 0x030)
#define REGBITS_RCCCFGR3        REGBITS_32(BASE_RCC + 0x030, RCCCFGR3BITFIELD)

/*******************************************************************************************************************************************
    PUBLIC FUNCTIONS
*******************************************************************************************************************************************/
extern UINT32 MCU_AHBClockHz(void);
extern UINT32 MCU_APB1ClockHz(void); 
extern UINT32 MCU_APB2ClockHz(void);

#endif /* MCU_RCC_H__ */
