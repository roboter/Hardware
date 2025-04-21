/*******************************************************************************************************************************************

    DZX | LPC175x6x | PWM                                                                                                 VERSION 18.2.1
    ------------------------------------------------------------------------------------------------------------------------------------

    This is part of the MCU peripheral drivers and provides support for pulse width modulator (PWM) peripheral.

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
#ifndef MCU_PWM_H__
#define MCU_PWM_H__

#include "Kernel/kernel.h"

/*******************************************************************************************************************************************
    REGISTER DEFINITIONS
*******************************************************************************************************************************************/
#define REG_PWM1         ((REG_PWM*)0x40018000)

typedef struct PWM1IRBITFIELD {
    UINT32 PWMMR0I                 :1;
    UINT32 PWMMR1I                 :1;
    UINT32 PWMMR2I                 :1;
    UINT32 PWMMR3I                 :1;
    UINT32 PWMCAP0                 :1;
    UINT32 PWMCAP1                 :1;
    UINT32                         :2;
    UINT32 PWMMR4I                 :1;
    UINT32 PWMMR5I                 :1;
    UINT32 PWMMR6I                 :1;
    UINT32                         :21;
} PWM1IRBITFIELD;

typedef struct PWM1TCRBITFIELD {
    UINT32 CE                      :1;
    UINT32 CR                      :1;
    UINT32                         :1;
    UINT32 PWMEN                   :1;
    UINT32                         :28;
} PWM1TCRBITFIELD;

typedef struct PWM1MCRBITFIELD {
    UINT32 PWMMR0I                 :1;
    UINT32 PWMMR0R                 :1;
    UINT32 PWMMR0S                 :1;
    UINT32 PWMMR1I                 :1;
    UINT32 PWMMR1R                 :1;
    UINT32 PWMMR1S                 :1;
    UINT32 PWMMR2I                 :1;
    UINT32 PWMMR2R                 :1;
    UINT32 PWMMR2S                 :1;
    UINT32 PWMMR3I                 :1;
    UINT32 PWMMR3R                 :1;
    UINT32 PWMMR3S                 :1;
    UINT32 PWMMR4I                 :1;
    UINT32 PWMMR4R                 :1;
    UINT32 PWMMR4S                 :1;
    UINT32 PWMMR5I                 :1;
    UINT32 PWMMR5R                 :1;
    UINT32 PWMMR5S                 :1;
    UINT32 PWMMR6I                 :1;
    UINT32 PWMMR6R                 :1;
    UINT32 PWMMR6S                 :1;
    UINT32                         :11;
} PWM1MCRBITFIELD;

typedef struct PWM1CCRBITFIELD {
    UINT32 CAP0RE                  :1;
    UINT32 CAP0FE                  :1;
    UINT32 CAP0INT                 :1;
    UINT32 CAP1RE                  :1;
    UINT32 CAP1FE                  :1;
    UINT32 CAP1INT                 :1;
    UINT32                         :26;
} PWM1CCRBITFIELD;

typedef struct PWM1PCRBITFIELD {
    UINT32                         :2;
    UINT32 PWMSEL2                 :1;
    UINT32 PWMSEL3                 :1;
    UINT32 PWMSEL4                 :1;
    UINT32 PWMSEL5                 :1;
    UINT32 PWMSEL6                 :1;
    UINT32                         :2;
    UINT32 PWMENA1                 :1;
    UINT32 PWMENA2                 :1;
    UINT32 PWMENA3                 :1;
    UINT32 PWMENA4                 :1;
    UINT32 PWMENA5                 :1;
    UINT32 PWMENA6                 :1;
    UINT32                         :17;
} PWM1PCRBITFIELD;

typedef struct PWM1LERBITFIELD {
    UINT32 EM0L                    :1;
    UINT32 EM1L                    :1;
    UINT32 EM2L                    :1;
    UINT32 EM3L                    :1;
    UINT32 EM4L                    :1;
    UINT32 EM5L                    :1;
    UINT32 EM6L                    :1;
    UINT32                         :25;
} PWM1LERBITFIELD;

typedef struct PWM1CTCRBITFIELD {
    UINT32 CM                      :2;
    UINT32 CIS                     :2;
    UINT32                         :28;
} PWM1CTCRBITFIELD;

#define REG_PWM1CCR                               REG_32(0x40018028)
#define REGBITS_PWM1CCR                           REGBITS_32(0x40018028, PWM1CCRBITFIELD)
#define REG_PWM1CR0                               REG_32(0x4001802C)
#define REG_PWM1CR1                               REG_32(0x40018030)
#define REG_PWM1CR2                               REG_32(0x40018034)
#define REG_PWM1CR3                               REG_32(0x40018038)
#define REG_PWM1CTCR                              REG_32(0x40018070)
#define REGBITS_PWM1CTCR                          REGBITS_32(0x40018070, PWM1CTCRBITFIELD)
#define REG_PWM1IR                                REG_32(0x40018000)
#define REGBITS_PWM1IR                            REGBITS_32(0x40018000, PWM1IRBITFIELD)
#define REG_PWM1LER                               REG_32(0x40018050)
#define REGBITS_PWM1LER                           REGBITS_32(0x40018050, PWM1LERBITFIELD)
#define REG_PWM1MCR                               REG_32(0x40018014)
#define REGBITS_PWM1MCR                           REGBITS_32(0x40018014, PWM1MCRBITFIELD)
#define REG_PWM1MR0                               REG_32(0x40018018)
#define REG_PWM1MR1                               REG_32(0x4001801C)
#define REG_PWM1MR2                               REG_32(0x40018020)
#define REG_PWM1MR3                               REG_32(0x40018024)
#define REG_PWM1MR4                               REG_32(0x40018040)
#define REG_PWM1MR5                               REG_32(0x40018044)
#define REG_PWM1MR6                               REG_32(0x40018048)
#define REG_PWM1PC                                REG_32(0x40018010)
#define REG_PWM1PCR                               REG_32(0x4001804C)
#define REGBITS_PWM1PCR                           REGBITS_32(0x4001804C, PWM1PCRBITFIELD)
#define REG_PWM1PR                                REG_32(0x4001800C)
#define REG_PWM1TC                                REG_32(0x40018008)
#define REG_PWM1TCR                               REG_32(0x40018004)
#define REGBITS_PWM1TCR                           REGBITS_32(0x40018004, PWM1TCRBITFIELD)

typedef struct REG_PWM {
	PREG_BITS32(IR, PWM1IRBITFIELD);
	PREG_BITS32(TCR, PWM1TCRBITFIELD);
	PREG_32(TC);
	PREG_32(PR);
	PREG_32(PC);
	PREG_BITS32(MCR, PWM1MCRBITFIELD);
	PREG_32(MR0);
	PREG_32(MR1);
	PREG_32(MR2);
	PREG_32(MR3);
	PREG_BITS32(CCR, PWM1CCRBITFIELD);
	PREG_32(CR0);
	PREG_32(CR1);
	PREG_32(CR2);
	PREG_32(CR3);
	PREG_RSRVD32(reserved);
	PREG_32(MR4);
	PREG_32(MR5);
	PREG_32(MR6);
	PREG_BITS32(PCR, PWM1PCRBITFIELD);
	PREG_BITS32(LER, PWM1LERBITFIELD);
	volatile UINT32 reserved2[7];
	PREG_BITS32(CTCR, PWM1CTCRBITFIELD);
} REG_PWM;

/*******************************************************************************************************************************************
    TYPE DEFINITIONS
*******************************************************************************************************************************************/
typedef struct LPC175X6X_PWM PWM;

/***************************************************************************************************************************************//**

    A PWM peripheral.
    @module     pwm-lpc175x6x

*******************************************************************************************************************************************/
struct LPC175X6X_PWM {
    UINT32      number;
    REG_PWM*    REG;
};

/*******************************************************************************************************************************************
    PUBLIC FUNCTIONS
*******************************************************************************************************************************************/
/***************************************************************************************************************************************//**

    Opens and initializes a PWM peripheral for the specified base frequency.

    @param[in]  pwm         A pointer to a caller allocated PWM to be initialized.
    @param[in]  number      The number of the PWM perhiperal to be initialized.
    @param[in]  hz          The base frequency for each of the channels of the PWM.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The PWM was successfully intialized and configured.
     ERR_NULLREFERENCE      | The argument 'pwm' was found to be a NULL reference.
     ERR_NOTSUPPORTED       | The PWM number is not supported.

    @module     pwm-lpc175x6x

*******************************************************************************************************************************************/
extern STATUS PWM_Open(PWM* pwm, UINT32 number, UINT32 hz);

/***************************************************************************************************************************************//**

    Closes a PWM peripheral.

    @param[in]  pwm         A pointer to the PWM peripheral to be closed.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The PWM was closed.
     ERR_NULLREFERENCE      | The argument 'pwm' was found to be a NULL reference.
     ERR_INVALIDOPERATION   | The PWM number is not supported.

    @module     pwm-lpc175x6x

*******************************************************************************************************************************************/
extern STATUS PWM_Close(PWM* pwm);

/***************************************************************************************************************************************//**

    Enables a channel for a PWM peripheral.

    @param[in]  pwm         A pointer to the PWM peripheral that contains the channel to be enabled.
    @param[in]  channel     The channel number to be enabled. Valid channels are 1 to 6.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The channel was enabled.
     ERR_NULLREFERENCE      | The argument 'pwm' was found to be a NULL reference.
     ERR_NOTINITIALIZED     | The specified perhipheral has not been initialized (opened).
     ERR_NOTSUPPORTED       | The specified channel is not supported.

    @module     pwm-lpc175x6x

*******************************************************************************************************************************************/
extern STATUS PWM_EnableChannel(PWM* pwm, UINT32 channel);

/***************************************************************************************************************************************//**

    Disables a channel for a PWM peripheral.

    @param[in]  pwm         A pointer to the PWM peripheral that contains the channel to be disabled.
    @param[in]  channel     The channel number to be disabled. Valid channels are 1 to 6.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The channel was disabled.
     ERR_NULLREFERENCE      | The argument 'pwm' was found to be a NULL reference.
     ERR_NOTINITIALIZED     | The specified perhipheral has not been initialized (opened).
     ERR_NOTSUPPORTED       | The specified channel is not supported.

    @module     pwm-lpc175x6x

*******************************************************************************************************************************************/
extern STATUS PWM_DisableChannel(PWM* pwm, UINT32 channel);

/***************************************************************************************************************************************//**

    Sets the duty cycle for a channel for a PWM peripheral.

    @param[in]  pwm         A pointer to the PWM peripheral that contains the channel to be configured.
    @param[in]  channel     The channel number to be configured.
    @param[in]  dutycycle   The new duty cycle value for the channel. Valid range is 0 to 100.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The new duty cycle value has been applied.
     ERR_NULLREFERENCE      | The argument 'pwm' was found to be a NULL reference.
     ERR_NOTINITIALIZED     | The specified perhipheral has not been initialized (opened).
     ERR_NOTSUPPORTED       | The specified channel is not supported.

    @module     pwm-lpc175x6x

*******************************************************************************************************************************************/
extern STATUS PWM_SetDuty(PWM* pwm, UINT32 channel, UINT32 dutycycle);

/***************************************************************************************************************************************//**

    Gets the duty cycle for a channel for a PWM peripheral.

    @param[in]  pwm         A pointer to the PWM peripheral that contains the channel to be configured.
    @param[in]  channel     The channel number to be configured.
    @param[in]  dutycycle   The new duty cycle value for the channel. Valid range is 0 to 100.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The duty cycle value has been returned.
     ERR_NULLREFERENCE      | The argument 'pwm' was found to be a NULL reference.
     ERR_NOTINITIALIZED     | The specified perhipheral has not been initialized (opened).
     ERR_NOTSUPPORTED       | The specified channel is not supported.

    @module     pwm-lpc175x6x

*******************************************************************************************************************************************/
extern STATUS PWM_GetDuty(PWM* pwm, UINT32 channel, UINT32* dutycycle);

#endif /* MCU_PWM_H__ */
