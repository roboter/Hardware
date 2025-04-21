/*******************************************************************************************************************************************

    DZX | STM32F4xx | RCC                                                                                                 VERSION 18.2.1
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
typedef struct RCCCRBITFIELD {
    UINT32 HSION                   :1;
    UINT32 HSIRDY                  :1;
    UINT32                         :1;
    UINT32 HSITRIM                 :5;
    UINT32 HSICAL                  :8;
    UINT32 HSEON                   :1;
    UINT32 HSERDY                  :1;
    UINT32 HSEBYP                  :1;
    UINT32 CSSON                   :1;
    UINT32                         :4;
    UINT32 PLLON                   :1;
    UINT32 PLLRDY                  :1;
    UINT32 PLLI2SON                :1;
    UINT32 PLLI2SRDY               :1;
    UINT32                         :4;
} RCCCRBITFIELD;

typedef struct RCCPLLCFGRBITFIELD {
    UINT32 PLLM                    :6;
    UINT32 PLLN                    :9;
    UINT32                         :1;
    UINT32 PLLP                    :2;
    UINT32                         :4;
    UINT32 PLLSRC                  :1;
    UINT32                         :1;
    UINT32 PLLQ                    :4;
    UINT32                         :4;
} RCCPLLCFGRBITFIELD;

typedef struct RCCCFGRBITFIELD {
    UINT32 SW                      :2;
    UINT32 SWS                     :2;
    UINT32 HPRE                    :4;
    UINT32                         :2;
    UINT32 PPRE1                   :3;
    UINT32 PPRE2                   :3;
    UINT32 RTCPRE                  :5;
    UINT32 MCO1                    :2;
    UINT32 I2SSRC                  :1;
    UINT32 MCO1PRE                 :3;
    UINT32 MCO2PRE                 :3;
    UINT32 MCO2                    :2;
} RCCCFGRBITFIELD;

typedef struct RCCCIRBITFIELD {
    UINT32 LSIRDYF                 :1;
    UINT32 LSERDYF                 :1;
    UINT32 HSIRDYF                 :1;
    UINT32 HSERDYF                 :1;
    UINT32 PLLRDYF                 :1;
    UINT32 PLLI2SRDYF              :1;
    UINT32                         :1;
    UINT32 CSSF                    :1;
    UINT32 LSIRDYIE                :1;
    UINT32 LSERDYIE                :1;
    UINT32 HSIRDYIE                :1;
    UINT32 HSERDYIE                :1;
    UINT32 PLLRDYIE                :1;
    UINT32 PLLI2SRDYIE             :1;
    UINT32                         :2;
    UINT32 LSIRDYC                 :1;
    UINT32 LSERDYC                 :1;
    UINT32 HSIRDYC                 :1;
    UINT32 HSERDYC                 :1;
    UINT32 PLLRDYC                 :1;
    UINT32 PLLI2SRDYC              :1;
    UINT32                         :1;
    UINT32 CSSC                    :1;
    UINT32                         :8;
} RCCCIRBITFIELD;

typedef struct RCCAHB1RSTRBITFIELD {
    UINT32 GPIOARST                :1;
    UINT32 GPIOBRST                :1;
    UINT32 GPIOCRST                :1;
    UINT32 GPIODRST                :1;
    UINT32 GPIOERST                :1;
    UINT32                         :2;
    UINT32 GPIOHRST                :1;
    UINT32                         :4;
    UINT32 CRCRST                  :1;
    UINT32                         :8;
    UINT32 DMA1RST                 :1;
    UINT32 DMA2RST                 :1;
    UINT32                         :9;
} RCCAHB1RSTRBITFIELD;

typedef struct RCCAHB2RSTRBITFIELD {
    UINT32                         :7;
    UINT32 OTGFSRST                :1;
    UINT32                         :24;
} RCCAHB2RSTRBITFIELD;

typedef struct RCCAPB1RSTRBITFIELD {
    UINT32 TIM2RST                 :1;
    UINT32 TIM3RST                 :1;
    UINT32 TIM4RST                 :1;
    UINT32 TIM5RST                 :1;
    UINT32                         :7;
    UINT32 WWDGRST                 :1;
    UINT32                         :2;
    UINT32 SPI2RST                 :1;
    UINT32 SPI3RST                 :1;
    UINT32                         :1;
    UINT32 UART2RST                :1;
    UINT32                         :3;
    UINT32 I2C1RST                 :1;
    UINT32 I2C2RST                 :1;
    UINT32 I2C3RST                 :1;
    UINT32                         :4;
    UINT32 PWRRST                  :1;
    UINT32                         :3;
} RCCAPB1RSTRBITFIELD;

typedef struct RCCAPB2RSTRBITFIELD {
    UINT32 TIM1RST                 :1;
    UINT32                         :3;
    UINT32 USART1RST               :1;
    UINT32 USART6RST               :1;
    UINT32                         :2;
    UINT32 ADCRST                  :1;
    UINT32                         :2;
    UINT32 SDIORST                 :1;
    UINT32 SPI1RST                 :1;
    UINT32                         :1;
    UINT32 SYSCFGRST               :1;
    UINT32                         :1;
    UINT32 TIM9RST                 :1;
    UINT32 TIM10RST                :1;
    UINT32 TIM11RST                :1;
    UINT32                         :13;
} RCCAPB2RSTRBITFIELD;

typedef struct RCCAHB1ENRBITFIELD {
    UINT32 GPIOAEN                 :1;
    UINT32 GPIOBEN                 :1;
    UINT32 GPIOCEN                 :1;
    UINT32 GPIODEN                 :1;
    UINT32 GPIOEEN                 :1;
    UINT32                         :2;
    UINT32 GPIOHEN                 :1;
    UINT32                         :4;
    UINT32 CRCEN                   :1;
    UINT32                         :8;
    UINT32 DMA1EN                  :1;
    UINT32 DMA2EN                  :1;
    UINT32                         :9;
} RCCAHB1ENRBITFIELD;

typedef struct RCCAHB2ENRBITFIELD {
    UINT32                         :7;
    UINT32 OTGFSEN                 :1;
    UINT32                         :24;
} RCCAHB2ENRBITFIELD;

typedef struct RCCAPB1ENRBITFIELD {
    UINT32 TIM2EN                  :1;
    UINT32 TIM3EN                  :1;
    UINT32 TIM4EN                  :1;
    UINT32 TIM5EN                  :1;
    UINT32                         :7;
    UINT32 WWDGEN                  :1;
    UINT32                         :2;
    UINT32 SPI2EN                  :1;
    UINT32 SPI3EN                  :1;
    UINT32                         :1;
    UINT32 USART2EN                :1;
    UINT32                         :3;
    UINT32 I2C1EN                  :1;
    UINT32 I2C2EN                  :1;
    UINT32 I2C3EN                  :1;
    UINT32                         :4;
    UINT32 PWREN                   :1;
    UINT32                         :3;
} RCCAPB1ENRBITFIELD;

typedef struct RCCAPB2ENRBITFIELD {
    UINT32 TIM1EN                  :1;
    UINT32                         :3;
    UINT32 USART1EN                :1;
    UINT32 USART6EN                :1;
    UINT32                         :2;
    UINT32 ADC1EN                  :1;
    UINT32                         :2;
    UINT32 SDIOEN                  :1;
    UINT32 SPI1EN                  :1;
    UINT32 SPI4EN                  :1;
    UINT32 SYSCFGEN                :1;
    UINT32                         :1;
    UINT32 TIM9EN                  :1;
    UINT32 TIM10EN                 :1;
    UINT32 TIM11EN                 :1;
    UINT32                         :1;
    UINT32 SPI5EN                  :1;
    UINT32                         :11;
} RCCAPB2ENRBITFIELD;

typedef struct RCCAHB1LPENRBITFIELD {
    UINT32 GPIOALPEN               :1;
    UINT32 GPIOBLPEN               :1;
    UINT32 GPIOCLPEN               :1;
    UINT32 GPIODLPEN               :1;
    UINT32 GPIOELPEN               :1;
    UINT32                         :2;
    UINT32 GPIOHLPEN               :1;
    UINT32                         :4;
    UINT32 CRCLPEN                 :1;
    UINT32                         :2;
    UINT32 FLITFLPEN               :1;
    UINT32 SRAM1LPEN               :1;
    UINT32                         :4;
    UINT32 DMA1LPEN                :1;
    UINT32 DMA2LPEN                :1;
    UINT32                         :9;
} RCCAHB1LPENRBITFIELD;

typedef struct RCCAHB2LPENRBITFIELD {
    UINT32                         :7;
    UINT32 OTGFSLPEN               :1;
    UINT32                         :24;
} RCCAHB2LPENRBITFIELD;

typedef struct RCCAPB1LPENRBITFIELD {
    UINT32 TIM2LPEN                :1;
    UINT32 TIM3LPEN                :1;
    UINT32 TIM4LPEN                :1;
    UINT32 TIM5LPEN                :1;
    UINT32                         :7;
    UINT32 WWDGLPEN                :1;
    UINT32                         :2;
    UINT32 SPI2LPEN                :1;
    UINT32 SPI3LPEN                :1;
    UINT32                         :1;
    UINT32 USART2LPEN              :1;
    UINT32                         :3;
    UINT32 I2C1LPEN                :1;
    UINT32 I2C2LPEN                :1;
    UINT32 I2C3LPEN                :1;
    UINT32                         :4;
    UINT32 PWRLPEN                 :1;
    UINT32                         :3;
} RCCAPB1LPENRBITFIELD;

typedef struct RCCAPB2LPENRBITFIELD {
    UINT32 TIM1LPEN                :1;
    UINT32                         :3;
    UINT32 USART1LPEN              :1;
    UINT32 USART6LPEN              :1;
    UINT32                         :2;
    UINT32 ADC1LPEN                :1;
    UINT32                         :2;
    UINT32 SDIOLPEN                :1;
    UINT32 SPI1LPEN                :1;
    UINT32 SPI4LPEN                :1;
    UINT32 SYSCFGLPEN              :1;
    UINT32                         :1;
    UINT32 TIM9LPEN                :1;
    UINT32 TIM10LPEN               :1;
    UINT32 TIM11LPEN               :1;
    UINT32                         :13;
} RCCAPB2LPENRBITFIELD;

typedef struct RCCBDCRBITFIELD {
    UINT32 LSEON                   :1;
    UINT32 LSERDY                  :1;
    UINT32 LSEBYP                  :1;
    UINT32                         :5;
    UINT32 RTCSEL0                 :1;
    UINT32 RTCSEL1                 :1;
    UINT32                         :5;
    UINT32 RTCEN                   :1;
    UINT32 BDRST                   :1;
    UINT32                         :15;
} RCCBDCRBITFIELD;

typedef struct RCCCSRBITFIELD {
    UINT32 LSION                   :1;
    UINT32 LSIRDY                  :1;
    UINT32                         :22;
    UINT32 RMVF                    :1;
    UINT32 BORRSTF                 :1;
    UINT32 PADRSTF                 :1;
    UINT32 PORRSTF                 :1;
    UINT32 SFTRSTF                 :1;
    UINT32 WDGRSTF                 :1;
    UINT32 WWDGRSTF                :1;
    UINT32 LPWRRSTF                :1;
} RCCCSRBITFIELD;

typedef struct RCCSSCGRBITFIELD {
    UINT32 MODPER                  :13;
    UINT32 INCSTEP                 :15;
    UINT32                         :2;
    UINT32 SPREADSEL               :1;
    UINT32 SSCGEN                  :1;
} RCCSSCGRBITFIELD;

typedef struct RCCPLLI2SCFGRBITFIELD {
    UINT32                         :6;
    UINT32 PLLI2SNX                :9;
    UINT32                         :13;
    UINT32 PLLI2SRX                :3;
    UINT32                         :1;
} RCCPLLI2SCFGRBITFIELD;

#define REG_RCCAHB1ENR                            REG_32(0x40023830)
#define REGBITS_RCCAHB1ENR                        REGBITS_32(0x40023830, RCCAHB1ENRBITFIELD)
#define REG_RCCAHB1LPENR                          REG_32(0x40023850)
#define REGBITS_RCCAHB1LPENR                      REGBITS_32(0x40023850, RCCAHB1LPENRBITFIELD)
#define REG_RCCAHB1RSTR                           REG_32(0x40023810)
#define REGBITS_RCCAHB1RSTR                       REGBITS_32(0x40023810, RCCAHB1RSTRBITFIELD)
#define REG_RCCAHB2ENR                            REG_32(0x40023834)
#define REGBITS_RCCAHB2ENR                        REGBITS_32(0x40023834, RCCAHB2ENRBITFIELD)
#define REG_RCCAHB2LPENR                          REG_32(0x40023854)
#define REGBITS_RCCAHB2LPENR                      REGBITS_32(0x40023854, RCCAHB2LPENRBITFIELD)
#define REG_RCCAHB2RSTR                           REG_32(0x40023814)
#define REGBITS_RCCAHB2RSTR                       REGBITS_32(0x40023814, RCCAHB2RSTRBITFIELD)
#define REG_RCCAPB1ENR                            REG_32(0x40023840)
#define REGBITS_RCCAPB1ENR                        REGBITS_32(0x40023840, RCCAPB1ENRBITFIELD)
#define REG_RCCAPB1LPENR                          REG_32(0x40023860)
#define REGBITS_RCCAPB1LPENR                      REGBITS_32(0x40023860, RCCAPB1LPENRBITFIELD)
#define REG_RCCAPB1RSTR                           REG_32(0x40023820)
#define REGBITS_RCCAPB1RSTR                       REGBITS_32(0x40023820, RCCAPB1RSTRBITFIELD)
#define REG_RCCAPB2ENR                            REG_32(0x40023844)
#define REGBITS_RCCAPB2ENR                        REGBITS_32(0x40023844, RCCAPB2ENRBITFIELD)
#define REG_RCCAPB2LPENR                          REG_32(0x40023864)
#define REGBITS_RCCAPB2LPENR                      REGBITS_32(0x40023864, RCCAPB2LPENRBITFIELD)
#define REG_RCCAPB2RSTR                           REG_32(0x40023824)
#define REGBITS_RCCAPB2RSTR                       REGBITS_32(0x40023824, RCCAPB2RSTRBITFIELD)
#define REG_RCCBDCR                               REG_32(0x40023870)
#define REGBITS_RCCBDCR                           REGBITS_32(0x40023870, RCCBDCRBITFIELD)
#define REG_RCCCFGR                               REG_32(0x40023808)
#define REGBITS_RCCCFGR                           REGBITS_32(0x40023808, RCCCFGRBITFIELD)
#define REG_RCCCIR                                REG_32(0x4002380C)
#define REGBITS_RCCCIR                            REGBITS_32(0x4002380C, RCCCIRBITFIELD)
#define REG_RCCCR                                 REG_32(0x40023800)
#define REGBITS_RCCCR                             REGBITS_32(0x40023800, RCCCRBITFIELD)
#define REG_RCCCSR                                REG_32(0x40023874)
#define REGBITS_RCCCSR                            REGBITS_32(0x40023874, RCCCSRBITFIELD)
#define REG_RCCPLLCFGR                            REG_32(0x40023804)
#define REGBITS_RCCPLLCFGR                        REGBITS_32(0x40023804, RCCPLLCFGRBITFIELD)
#define REG_RCCPLLI2SCFGR                         REG_32(0x40023884)
#define REGBITS_RCCPLLI2SCFGR                     REGBITS_32(0x40023884, RCCPLLI2SCFGRBITFIELD)
#define REG_RCCSSCGR                              REG_32(0x40023880)
#define REGBITS_RCCSSCGR                          REGBITS_32(0x40023880, RCCSSCGRBITFIELD)

/*******************************************************************************************************************************************
    PUBLIC FUNCTIONS
*******************************************************************************************************************************************/
extern UINT32 MCU_AHBClockHz(void);
extern UINT32 MCU_APB1ClockHz(void); 
extern UINT32 MCU_APB2ClockHz(void);

#endif /* MCU_RCC_H__ */
