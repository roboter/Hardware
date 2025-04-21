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
#include "mcu_pwm.h"
#include "mcu_cfg.h"
#include "mcu_scu.h"

/*******************************************************************************************************************************************
    PRIVATE VARIABLES
*******************************************************************************************************************************************/
static PWM* mcu_pwm[1];

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
STATUS PWM_Open(PWM* pwm, UINT32 number, UINT32 hz)
{
#if (CFG_NULLCHECKING)
    if (pwm == NULL) {
        return ERR_NULLREFERENCE;
    }
#endif

    switch (number) {
        case 0:
            pwm->REG = REG_PWM1;

            REGBITS_PCONP.PCPWM1 = 1;                           /* Power ON PWM peripheral */
            REGBITS_PCLKSEL0.PCLKPWM1 = 1;                      /* Set PWM peripheral to receive same clock as CPU core */

            pwm->REG->MR0 = CFG_CPUCLOCKHZ / hz;                /* Calc the scalar based on system clock frequency */
            pwm->REG->TCR.VALUE = 0x9;                          /* Enable the PWM and counters */
            break;
        default:
            return ERR_NOTSUPPORTED;
    }

    pwm->number = number;
    mcu_pwm[number] = pwm;
    return SUCCESS;
}

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
STATUS PWM_Close(PWM* pwm)
{
#if (CFG_NULLCHECKING)
    if (pwm == NULL) {
        return ERR_NULLREFERENCE;
    }
#endif

    if (pwm == mcu_pwm[pwm->number]) {
        switch (pwm->number) {
            case 0:
                REGBITS_PCONP.PCPWM1 = 0;                       /* Power OFF PWM peripheral */
                break;
            default:
                return ERR_INVALIDOPERATION;
        }
    }

    return SUCCESS;
}

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
STATUS PWM_EnableChannel(PWM* pwm, UINT32 channel)
{
#if (CFG_NULLCHECKING)
    if (pwm == NULL) {
        return ERR_NULLREFERENCE;
    }
#endif

    if (pwm != mcu_pwm[pwm->number]) {                      /* Has the peripheral been initialized? */
        return ERR_NOTINITIALIZED;
    }

    switch (channel) {
        case 1:
            pwm->REG->PCR.BITS.PWMENA1 = 1;
            break;
        case 2:
            pwm->REG->PCR.BITS.PWMENA2 = 1;
            break;
        case 3:
            pwm->REG->PCR.BITS.PWMENA3 = 1;
            break;
        case 4:
            pwm->REG->PCR.BITS.PWMENA4 = 1;
            break;
        case 5:
            pwm->REG->PCR.BITS.PWMENA5 = 1;
            break;
        case 6:
            pwm->REG->PCR.BITS.PWMENA6 = 1;
            break;
        default:
            return ERR_NOTSUPPORTED;
    }

    return SUCCESS;
}

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
STATUS PWM_DisableChannel(PWM* pwm, UINT channel)
{
#if (CFG_NULLCHECKING)
    if (pwm == NULL) {
        return ERR_NULLREFERENCE;
    }
#endif

    if (pwm != mcu_pwm[pwm->number]) {              /* Is the PWM open? */
        return ERR_INVALIDOPERATION;
    }

    switch (channel) {
        case 1:
            pwm->REG->PCR.BITS.PWMENA1 = 0;
            break;
        case 2:
            pwm->REG->PCR.BITS.PWMENA2 = 0;
            break;
        case 3:
            pwm->REG->PCR.BITS.PWMENA3 = 0;
            break;
        case 4:
            pwm->REG->PCR.BITS.PWMENA4 = 0;
            break;
        case 5:
            pwm->REG->PCR.BITS.PWMENA5 = 0;
            break;
        case 6:
            pwm->REG->PCR.BITS.PWMENA6 = 0;
            break;
        default:
            return ERR_NOTSUPPORTED;
    }
    return SUCCESS;
}

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
STATUS PWM_SetDuty(PWM* pwm, UINT32 channel, UINT32 dutycycle)
{
    UINT32 tics;

    
#if (CFG_NULLCHECKING)
    if (pwm == NULL) {
        return ERR_NULLREFERENCE;
    }
#endif

    if (pwm != mcu_pwm[pwm->number]) {              /* Is the PWM open? */
        return ERR_INVALIDOPERATION;
    }

    if (dutycycle > 100) {                         /* Bound to maximum duty cycle */
        dutycycle = 100;
    }

    tics = (pwm->REG->MR0 * dutycycle) / 100;      /* Calc the amount of time tics to achieve the desired duty cycle */

    switch (channel) {
        case 1:
            pwm->REG->MR1 = tics;
            pwm->REG->LER.BITS.EM1L = 1;
            break;
        case 2:
            pwm->REG->MR2 = tics;
            pwm->REG->LER.BITS.EM2L = 1;
            break;
        case 3:
            pwm->REG->MR3 = tics;
            pwm->REG->LER.BITS.EM3L = 1;
            break;
        case 4:
            pwm->REG->MR4 = tics;
            pwm->REG->LER.BITS.EM4L = 1;
            break;
        case 5:
            pwm->REG->MR5 = tics;
            pwm->REG->LER.BITS.EM5L = 1;
            break;
        case 6:
            pwm->REG->MR6 = tics;
            pwm->REG->LER.BITS.EM6L = 1;
            break;
        default:
            return ERR_NOTSUPPORTED;
    }
    return SUCCESS;
}

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
STATUS PWM_GetDuty(PWM* pwm, UINT32 channel, UINT32* dutycycle)
{
    UINT32 value;
    UINT32 cycle;

    
#if (CFG_NULLCHECKING)
    if (pwm == NULL) {
        return ERR_NULLREFERENCE;
    }
    
    if (dutycycle == NULL) {
        return ERR_NULLREFERENCE;
    }
#endif


    cycle = REG_PWM1MR0;                                        /* Capture the full cycle time */
    
    if (cycle == 0) {
        *dutycycle = 0;
        return SUCCESS;
    }
    
    switch (channel)                                            /* Capture the amount of ON time */
    {
        case 1:
            value = REG_PWM1MR1;
            break;
        case 2:
            value = REG_PWM1MR2;
            break;
        case 3:
            value = REG_PWM1MR3;
            break;
        case 4:
            value = REG_PWM1MR4;
            break;
        case 5:
            value = REG_PWM1MR5;
            break;
        case 6:
            value = REG_PWM1MR6;
            break;
        default:
            return ERR_NOTSUPPORTED;
    }

    *dutycycle = ((value * 100) / cycle);
    return SUCCESS;
}
