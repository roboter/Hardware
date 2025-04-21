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
#ifndef MCU_ADC_H__
#define MCU_ADC_H__

#include "Kernel/kernel.h"

/*******************************************************************************************************************************************
    REGISTER DEFINITIONS
*******************************************************************************************************************************************/
#define REG_ADC0    ((REG_ADC*)0x40034000)      /* The peripheral registers for ADC 0 */

typedef struct AD0CRBITFIELD {
    UINT32 SEL                     :8;
    UINT32 CLKDIV                  :8;
    UINT32 BURST                   :1;
    UINT32 CLKS                    :3;
    UINT32                         :1;
    UINT32 PDN                     :1;
    UINT32                         :2;
    UINT32 START                   :3;
    UINT32 EDGE                    :1;
    UINT32                         :4;
} AD0CRBITFIELD;

typedef struct AD0GDRBITFIELD {
    UINT32                         :6;
    UINT32 RESULT                  :10;
    UINT32                         :8;
    UINT32 CHN                     :3;
    UINT32                         :3;
    UINT32 OVERUN                  :1;
    UINT32 DONE                    :1;
} AD0GDRBITFIELD;

typedef struct AD0INTENBITFIELD {
    UINT32 ADINTEN0                :1;
    UINT32 ADINTEN1                :1;
    UINT32 ADINTEN2                :1;
    UINT32 ADINTEN3                :1;
    UINT32 ADINTEN4                :1;
    UINT32 ADINTEN5                :1;
    UINT32 ADINTEN6                :1;
    UINT32 ADINTEN7                :1;
    UINT32 ADGINTEN                :1;
    UINT32                         :23;
} AD0INTENBITFIELD;

typedef struct AD0DRBITFIELD {
    UINT32                         :6;
    UINT32 RESULT                  :10;
    UINT32                         :14;
    UINT32 OVERUN                  :1;
    UINT32 DONE                    :1;
} AD0DRBITFIELD;

typedef struct AD0STATBITFIELD {
    UINT32 DONE0                   :1;
    UINT32 DONE1                   :1;
    UINT32 DONE2                   :1;
    UINT32 DONE3                   :1;
    UINT32 DONE4                   :1;
    UINT32 DONE5                   :1;
    UINT32 DONE6                   :1;
    UINT32 DONE7                   :1;
    UINT32 OVERRUN0                :1;
    UINT32 OVERRUN1                :1;
    UINT32 OVERRUN2                :1;
    UINT32 OVERRUN3                :1;
    UINT32 OVERRUN4                :1;
    UINT32 OVERRUN5                :1;
    UINT32 OVERRUN6                :1;
    UINT32 OVERRUN7                :1;
    UINT32 ADINT                   :1;
    UINT32                         :15;
} AD0STATBITFIELD;
                                           
typedef struct REG_ADC {
	PREG_BITS32(CR, AD0CRBITFIELD);             /* Control Register */
	PREG_BITS32(GDR, AD0GDRBITFIELD);           /* Global Data Register */
	PREG_RSRVD32(RESERVED0);                    /* Reserved */
	PREG_BITS32(INTEN, AD0INTENBITFIELD);       /* Interrupt Enable Register */
	PREG_BITS32(ADDR, AD0DRBITFIELD)[8];        /* A/D Channel Data Register */
	PREG_BITS32(STAT, AD0STATBITFIELD);         /* Status Register */
} REG_ADC;

/*******************************************************************************************************************************************
    TYPE DEFINITIONS
*******************************************************************************************************************************************/
typedef struct LPC175X6X_ADC ADC;

/***************************************************************************************************************************************//**

    An Analog-to-Digital Converter (ADC) peripheral.
    @module     adc-lpc175x6x

*******************************************************************************************************************************************/
struct LPC175X6X_ADC {
    REG_ADC*    REG;                /**< A pointer to the registers for the ADC peripheral */
    UINT32      number;             /**< The number of the ADC peripheral */
};

/*******************************************************************************************************************************************
    PUBLIC FUNCTIONS
*******************************************************************************************************************************************/
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
extern STATUS ADC_Open(ADC* adc, UINT32 number);

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
extern STATUS ADC_Close(ADC* adc);

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
extern STATUS ADC_Convert(ADC* adc, UINT32 channel, UINT16* value);

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
extern STATUS ADC_EnableBurst(ADC* adc, BYTE channels);

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
extern STATUS ADC_DisableBurst(ADC* adc);

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
extern STATUS ADC_ReadBurst(ADC* adc, UINT32 channel, UINT16* value);

#endif /* MCU_ADC_H__ */
