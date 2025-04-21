/*******************************************************************************************************************************************

    DZX | LPC175x6x | ADC                                                                                                 VERSION 18.2.1
    ------------------------------------------------------------------------------------------------------------------------------------

    This is part of the MCU peripheral drivers and provides support for the analog-to-digital converter (ADC).

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
#include "mcu_adc.h"
#include "mcu_cfg.h"
#include "mcu_scu.h"

/*******************************************************************************************************************************************
    PRIVATE VARIABLES
*******************************************************************************************************************************************/
static ADC* mcu_adc[1];         /* Pointers to each of the open ADC peripherals */

/***************************************************************************************************************************************//**

    Initializes the analog-to-digital converter (ADC) peripheral. The peripheral is powered on and it's clock source is configured.

    @param[in]  adc         A pointer to the ADC to be initialized.
    @param[in]  number      The number of peripheral to be opened.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The ADC peripheral was successfully initialized.
     ERR_INVALIDCONTEXT     | Not allowed to be called from the context of an interrupt service routine (ISR).
     ERR_NULLREFERENCE      | The argument 'adc' was found to be NULL.
     ERR_NOTSUPPORTED       | An unsupported ADC peripheral number was specified.

    @remark     Not thread safe.
    @module     adc-lpc175x6x

*******************************************************************************************************************************************/
STATUS ADC_Open(ADC* adc, UINT32 number)
{
    INTERRUPTLOCK lock;
    BYTE div;


#if (CFG_CONTEXTCHECKING)
    if (KERNEL_IsISR()) {
        return ERR_INVALIDCONTEXT;
    }
#endif
#if (CFG_NULLCHECKING)
    if (adc == NULL) {
        return ERR_NULLREFERENCE;
    }
#endif

    ACQUIREINTERRUPTLOCK();
    
    switch (number) {
        case 0:
            adc->REG = REG_ADC0;
            REGBITS_PCONP.PCAD = 1;                 /* Power ON the ADC peripheral */
            break;
        default:
            RELEASEINTERRUPTLOCK();
            return ERR_NOTSUPPORTED;
    }
    
    RELEASEINTERRUPTLOCK();

    adc->number = number;
    
    div = CFG_CPUCLOCKHZ / CFG_ADCCLOCKHZ;          /* Calculate a clock divider */
    if (CFG_CPUCLOCKHZ % CFG_ADCCLOCKHZ) {
        div++;                                      /* Round divisor up to guarantee clock is at or below configured setting */
    }
    
    ACQUIREINTERRUPTLOCK();

    adc->REG->CR.BITS.CLKDIV = div;                 /* Assign the calculated clock divider */
    adc->REG->CR.BITS.BURST = 0;                    /* Burst OFF */
    adc->REG->CR.BITS.PDN = 1;                      /* Set ADC as operational */

    mcu_adc[number] = adc;
    
    RELEASEINTERRUPTLOCK();
    return SUCCESS;
}

/***************************************************************************************************************************************//**

    Closes an ADC peripheral.

    @param[in]  adc         The ADC peripheral to be closed.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The ADC was successfully closed.
     ERR_NULLREFERENCE      | The argument 'adc' was found to be NULL. 
     ERR_INVALIDCONTEXT     | This operation is not supported from the context of an interrupt service routine (ISR).
     ERR_NOTINITIALIZED     | The specified ADC has not been initialized (opened).
     ERR_INVALIDOPERATION   | The ADC could not be closed due to an invalid state.

    @remark     Not thread safe.
    @module     adc-lpc175x6x

*******************************************************************************************************************************************/
STATUS ADC_Close(ADC* adc)
{
    INTERRUPTLOCK lock;
    
    
#if (CFG_CONTEXTCHECKING)
    if (KERNEL_IsISR()) {
        return ERR_INVALIDCONTEXT;
    }
#endif
#if (CFG_NULLCHECKING)
    if (adc == NULL) {
        return ERR_NULLREFERENCE;
    }
#endif

    ACQUIREINTERRUPTLOCK();
    
    if (mcu_adc[adc->number] != adc) {                          /* Has the specified ADC been opened (initialized)? */
        RELEASEINTERRUPTLOCK();
        return ERR_NOTINITIALIZED;
    }
    
    adc->REG->CR.BITS.PDN = 0;                                  /* Set ADC into power-down mode */
    
    switch (adc->number) {
        case 0:
            REGBITS_PCONP.PCAD = 1;                             /* Power OFF the ADC peripheral */
            break;
        default:
            RELEASEINTERRUPTLOCK();
            return ERR_INVALIDOPERATION;
    }

    mcu_adc[adc->number] = NULL;                                /* Release the reference to the open ADC */
    
    RELEASEINTERRUPTLOCK();
    return SUCCESS;
}

/***************************************************************************************************************************************//**

    Initiates a conversion and returns the resulting value for an ADC channel.

    @param[in]  adc         The ADC peripheral that contains the channel to be read.
    @param[in]  channel     The ADC channel to be read.
    @param[out] value       A pointer to a caller allocated variable to retrieve the result of the ADC conversion.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The channel was successfully converted and returned.
     ERR_NULLREFERENCE      | The argument 'adc' or 'value' was found to be NULL.
     ERR_NOTSUPPORTED       | An unsupported channel was specified.
     ERR_NOTINITIALIZED     | The specified ADC has not been initialized.
     ERR_INVALIDOPERATION   | The ADC has burst mode enabled and cannot manually initiate a conversion.

    @remark     Not thread safe.
    @remark     Uses a spin-wait until the conversion is complete.
    @remark     Must not be used while burst mode is enabled on the specified ADC.
    @module     adc-lpc175x6x

*******************************************************************************************************************************************/
STATUS ADC_Convert(ADC* adc, UINT32 channel, UINT16* value)
{
#if (CFG_NULLCHECKING)
    if (adc == NULL) {
        return ERR_NULLREFERENCE;
    }

    if (value == NULL) {
        return ERR_NULLREFERENCE;
    }
#endif

    if (channel >= 8) {
        return ERR_NOTSUPPORTED;
    }
    
    if (mcu_adc[adc->number] != adc) {
        return ERR_NOTINITIALIZED;
    }
    
    if (adc->REG->CR.BITS.BURST == 1) {
        return ERR_INVALIDOPERATION;
    }

    adc->REG->CR.BITS.SEL = (1 << channel);                     /* Set the channel to be sampled and converted */
    adc->REG->CR.BITS.START = 1;                                /* Initiate the ADC conversion */
    
    while (adc->REG->ADDR[channel].BITS.DONE == 0);             /* Wait for the conversion to complete */
    *value = adc->REG->ADDR[channel].BITS.RESULT;               /* Assign the ADC result value */
    
    return SUCCESS;
}

/***************************************************************************************************************************************//**

    Enables the burst mode for an ADC.

    @param[in]  adc         A pointer to the ADC to enable burst mode.
    @param[in]  channels    A bit-field of the channels to be enabled (i.e. bit-0 => channel 0 ... bit-7 => channel 7).

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The ADC has been configured for burst mode.
     ERR_NULLREFERENCE      | The argument 'adc' was found to be NULL.
     ERR_NOTINITIALIZED     | The specified ADC has not been initialized.

    @remark     Not thread safe.
    @module     adc-lpc175x6x

*******************************************************************************************************************************************/
STATUS ADC_EnableBurst(ADC* adc, BYTE channels)
{
#if (CFG_NULLCHECKING)
    if (adc == NULL) {
        return ERR_NULLREFERENCE;
    }
#endif
    
    if (mcu_adc[adc->number] != adc) {
        return ERR_NOTINITIALIZED;
    }
    
    adc->REG->CR.BITS.START = 0;
    adc->REG->CR.BITS.SEL = channels;
    adc->REG->CR.BITS.BURST = 1;
    
    return SUCCESS;
}

/***************************************************************************************************************************************//**

    Disables the burst mode for an ADC.

    @param[in]  adc         A pointer to the ADC to disable burst mode.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The burst mode has been disabled.
     ERR_NULLREFERENCE      | The argument 'adc' was found to be NULL.
     ERR_NOTINITIALIZED     | The specified ADC has not been initialized.

    @remark     Not thread safe.
    @module     adc-lpc175x6x

*******************************************************************************************************************************************/
STATUS ADC_DisableBurst(ADC* adc)
{
#if (CFG_NULLCHECKING)
    if (adc == NULL) {
        return ERR_NULLREFERENCE;
    }
#endif
    
    if (mcu_adc[adc->number] != adc) {
        return ERR_NOTINITIALIZED;
    }
    
    adc->REG->CR.BITS.BURST = 0;
    return SUCCESS;
}

/***************************************************************************************************************************************//**

    Reads and returns the resulting value for an ADC channel that has been converted using the burst mode. Requires that the specified
    channel has been previously enabled for burst mode using ADC_EnableBurst().

    @param[in]  adc         The ADC peripheral that contains the channel to be read.
    @param[in]  channel     The ADC channel to be read.
    @param[out] value       A pointer to a caller allocated variable to retrieve the result.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The channel was successfully returned.
     ERR_NULLREFERENCE      | The argument 'adc' or 'value' was found to be NULL.
     ERR_NOTSUPPORTED       | An unsupported channel was specified.
     ERR_NOTINITIALIZED     | The specified ADC has not been initialized.

    @module     adc-lpc175x6x

*******************************************************************************************************************************************/
STATUS ADC_ReadBurst(ADC* adc, UINT32 channel, UINT16* value)
{
    INTERRUPTLOCK lock;
    
    
#if (CFG_NULLCHECKING)
    if (adc == NULL) {
        return ERR_NULLREFERENCE;
    }
    
    if (value == NULL) {
        return ERR_NULLREFERENCE;
    }
#endif
    
    if (channel >= 8) {
        return ERR_NOTSUPPORTED;
    }
    
    ACQUIREINTERRUPTLOCK();
    
    if (mcu_adc[adc->number] != adc) {
        RELEASEINTERRUPTLOCK();
        return ERR_NOTINITIALIZED;
    }
    
    *value = adc->REG->ADDR[channel].BITS.RESULT;               /* Assign the ADC result value */
    
    RELEASEINTERRUPTLOCK();
    return SUCCESS;
}
