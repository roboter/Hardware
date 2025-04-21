/*******************************************************************************************************************************************

    DZX | LPC18xx | PIN                                                                                                   VERSION 18.2.1
    ------------------------------------------------------------------------------------------------------------------------------------

    This is part of the MCU peripheral drivers and provides support for reading and writing the MCU pins.

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
#ifndef MCU_PIN_H__
#define MCU_PIN_H__

#include "Kernel/kernel.h"

/*******************************************************************************************************************************************
    REGISTER DEFINITIONS
*******************************************************************************************************************************************/
#define REG_GPIODIR         ((volatile UINT32*)(0x400F6000))
#define REG_GPIOMASK        ((volatile UINT32*)(0x400F6080))
#define REG_GPIOPIN         ((volatile UINT32*)(0x400F6100))
#define REG_GPIOSET         ((volatile UINT32*)(0x400F6200))
#define REG_GPIOCLR         ((volatile UINT32*)(0x400F6280))
#define REG_SFSPBASE        0x40086000

/*******************************************************************************************************************************************
    TYPE DEFINITIONS
*******************************************************************************************************************************************/
typedef enum LPC18XX_PORT PORT;
typedef enum LPC18XX_PIN PIN;
typedef enum LPC18XX_DIRECTION DIRECTION;
typedef enum LPC18XX_EDGE EDGE;

/***************************************************************************************************************************************//**

    Represents a port of pins within the MCU.
    @module     pin-lpc18xx

*******************************************************************************************************************************************/
enum LPC18XX_PORT {
	PORT_0 = 0,     /**< Pin Port 0 */
	PORT_1,         /**< Pin Port 1 */
	PORT_2,         /**< Pin Port 2 */
	PORT_3,         /**< Pin Port 3 */
	PORT_4,         /**< Pin Port 4 */
    PORT_5,         /**< Pin Port 5 */
    PORT_6,         /**< Pin Port 6 */
    PORT_7,         /**< Pin Port 7 */
	PORT_MAX
};

/***************************************************************************************************************************************//**

    Represents an individual pin on the MCU.

    @remark     The upper 16-bits of the value represents the offset for the SFSP register. The lower 16-bits represents the GPIO port
                and pin numbers.
    @module     pin-lpc18xx

*******************************************************************************************************************************************/
enum LPC18XX_PIN {
	P0_00 = 0x00000000,  /**< P0.0 */
	P0_01 = 0x00040001,  /**< P0.1 */
    
	P1_00 = 0x00800004,  /**< P1.0 */
	P1_01 = 0x00840008,  /**< P1.1 */
	P1_02 = 0x00880009,  /**< P1.2 */
	P1_03 = 0x008C000A,  /**< P1.3 */
	P1_04 = 0x0090000B,  /**< P1.4 */
	P1_05 = 0x00940108,  /**< P1.5 */
	P1_06 = 0x00980109,  /**< P1.6 */
	P1_07 = 0x009C0100,  /**< P1.7 */
	P1_08 = 0x00A00101,  /**< P1.8 */
	P1_09 = 0x00A40102,  /**< P1.9 */
	P1_10 = 0x00A80103,  /**< P1.10 */
	P1_11 = 0x00AC0104,  /**< P1.11 */
	P1_12 = 0x00B00105,  /**< P1.12 */
	P1_13 = 0x00B40106,  /**< P1.13 */
	P1_14 = 0x00B80107,  /**< P1.14 */
	P1_15 = 0x00BC0002,  /**< P1.15 */
	P1_16 = 0x00C00003,  /**< P1.16 */
	P1_17 = 0x00C4000C,  /**< P1.17 */
	P1_18 = 0x00C8000D,  /**< P1.18 */
	P1_19 = 0x00CC000E,  /**< P1.19 */
	P1_20 = 0x00D0000F,  /**< P1.20 */

	P2_00 = 0x01000500,  /**< P2.0 */
	P2_01 = 0x01040501,  /**< P2.1 */
	P2_02 = 0x01080502,  /**< P2.2 */
	P2_03 = 0x010C0503,  /**< P2.3 */
	P2_04 = 0x01100504,  /**< P2.4 */
	P2_05 = 0x01140505,  /**< P2.5 */
	P2_06 = 0x01180506,  /**< P2.6 */
	P2_07 = 0x011C0007,  /**< P2.7 */
	P2_08 = 0x01200507,  /**< P2.8 */
	P2_09 = 0x0124010A,  /**< P2.9 */
	P2_10 = 0x0128000E,  /**< P2.10 */
	P2_11 = 0x012C010B,  /**< P2.11 */
	P2_12 = 0x0130010C,  /**< P2.12 */
	P2_13 = 0x0134010D,  /**< P2.13 */

	P3_00 = 0x0180FF00,  /**< P3.0 */
	P3_01 = 0x01840508,  /**< P3.1 */
	P3_02 = 0x01880509,  /**< P3.2 */
	P3_03 = 0x018CFF03,  /**< P3.3 */
	P3_04 = 0x0190010E,  /**< P3.4 */
	P3_05 = 0x0194010F,  /**< P3.5 */
	P3_06 = 0x01980006,  /**< P3.6 */
	P3_07 = 0x019C050A,  /**< P3.7 */
	P3_08 = 0x01A0050B,  /**< P3.8 */

	P4_00 = 0x02000200,  /**< P4.0 */
	P4_01 = 0x02040201,  /**< P4.1 */
	P4_02 = 0x02080202,  /**< P4.2 */
	P4_03 = 0x020C0203,  /**< P4.3 */
	P4_04 = 0x02100204,  /**< P4.4 */
	P4_05 = 0x02140205,  /**< P4.5 */
	P4_06 = 0x02180206,  /**< P4.6 */
	P4_07 = 0x021CFF07,  /**< P4.7 */
	P4_08 = 0x0220050C,  /**< P4.8 */
	P4_09 = 0x0224050D,  /**< P4.9 */
	P4_10 = 0x0228050E,  /**< P4.10 */
    
    P5_00 = 0x02800209,  /**< P5.0 */
    P5_01 = 0x0284020A,  /**< P5.1 */
    P5_02 = 0x0288020B,  /**< P5.2 */
    P5_03 = 0x028C020C,  /**< P5.3 */
    P5_04 = 0x0290020D,  /**< P5.4 */
    P5_05 = 0x0294020E,  /**< P5.5 */
    P5_06 = 0x0298020F,  /**< P5.6 */
    P5_07 = 0x029C0207,  /**< P5.7 */
    
    P6_00 = 0x0300FF00,  /**< P6.0 */
    P6_01 = 0x03040300,  /**< P6.1 */
    P6_02 = 0x03080301,  /**< P6.2 */
    P6_03 = 0x030C0302,  /**< P6.3 */
    P6_04 = 0x03100303,  /**< P6.4 */
    P6_05 = 0x03140304,  /**< P6.5 */
    P6_06 = 0x03180005,  /**< P6.6 */
    P6_07 = 0x031C050F,  /**< P6.7 */
    P6_08 = 0x03200510,  /**< P6.8 */
    P6_09 = 0x03240305,  /**< P6.9 */
    P6_10 = 0x03280306,  /**< P6.10 */
    P6_11 = 0x032C0307,  /**< P6.11 */
    P6_12 = 0x03300208,  /**< P6.12 */
    
    P7_00 = 0x03800308,  /**< P7.0 */
    P7_01 = 0x03840309,  /**< P7.1 */
    P7_02 = 0x0388030A,  /**< P7.2 */
    P7_03 = 0x038C030B,  /**< P7.3 */
    P7_04 = 0x0390030C,  /**< P7.4 */
    P7_05 = 0x0394030D,  /**< P7.5 */
    P7_06 = 0x0398030E,  /**< P7.6 */
    P7_07 = 0x039C030F,  /**< P7.7 */
    
    P8_00 = 0x04000400,  /**< P8.0 */
    P8_01 = 0x04040401,  /**< P8.1 */
    P8_02 = 0x04080402,  /**< P8.2 */
    P8_03 = 0x040C0403,  /**< P8.3 */
    P8_04 = 0x04100404,  /**< P8.4 */
    P8_05 = 0x04140405,  /**< P8.5 */
    P8_06 = 0x04180406,  /**< P8.6 */
    P8_07 = 0x041C0407,  /**< P8.7 */
    P8_08 = 0x0420FF07,  /**< P8.8 */
    
    P9_00 = 0x0480040C,  /**< P9.0 */
    P9_01 = 0x0484040D,  /**< P9.1 */
    P9_02 = 0x0488040E,  /**< P9.2 */
    P9_03 = 0x048C040F,  /**< P9.3 */
    P9_04 = 0x04900511,  /**< P9.4 */
    P9_05 = 0x04940512,  /**< P9.5 */
    P9_06 = 0x0498FF05,  /**< P9.6 */
    
    PA_00 = 0x0500FF0B,  /**< PA.0 */
    PA_01 = 0x05040408,  /**< PA.1 */
    PA_02 = 0x05080409,  /**< PA.2 */
    PA_03 = 0x050C040A,  /**< PA.3 */
    PA_04 = 0x05100513,  /**< PA.4 */
    
    PB_00 = 0x05800514,  /**< PB.0 */
    PB_01 = 0x05840515,  /**< PB.1 */
    PB_02 = 0x05880516,  /**< PB.2 */
    PB_03 = 0x058C0517,  /**< PB.3 */
    PB_04 = 0x05900518,  /**< PB.4 */
    PB_05 = 0x05940519,  /**< PB.5 */
    PB_06 = 0x0598051A,  /**< PB.6 */
    
    PC_00 = 0x0600FF1A,  /**< PC.0 */
    PC_01 = 0x06040600,  /**< PC.1 */
    PC_02 = 0x06080601,  /**< PC.2 */
    PC_03 = 0x060C0602,  /**< PC.3 */
    PC_04 = 0x06100603,  /**< PC.4 */
    PC_05 = 0x06140604,  /**< PC.5 */
    PC_06 = 0x06180605,  /**< PC.6 */
    PC_07 = 0x061C0606,  /**< PC.7 */
    PC_08 = 0x06200607,  /**< PC.8 */
    PC_09 = 0x06240608,  /**< PC.9 */
    PC_10 = 0x06280609,  /**< PC.10 */
    PC_11 = 0x062C060A,  /**< PC.11 */
    PC_12 = 0x0630060B,  /**< PC.12 */
    PC_13 = 0x0634060C,  /**< PC.13 */
    PC_14 = 0x0638060D,  /**< PC.14 */
    
    PD_00 = 0x0680060E,  /**< PD.0 */
    PD_01 = 0x0684060F,  /**< PD.1 */
    PD_02 = 0x06880610,  /**< PD.2 */
    PD_03 = 0x068C0611,  /**< PD.3 */
    PD_04 = 0x06900612,  /**< PD.4 */
    PD_05 = 0x06940613,  /**< PD.5 */
    PD_06 = 0x06980614,  /**< PD.6 */
    PD_07 = 0x069C0615,  /**< PD.7 */
    PD_08 = 0x06A00616,  /**< PD.8 */
    PD_09 = 0x06A40617,  /**< PD.9 */
    PD_10 = 0x06A80618,  /**< PD.10 */
    PD_11 = 0x06AC0619,  /**< PD.11 */
    PD_12 = 0x06B0061A,  /**< PD.12 */
    PD_13 = 0x06B4061B,  /**< PD.13 */
    PD_14 = 0x06B8061C,  /**< PD.14 */
    PD_15 = 0x06BC061D,  /**< PD.15 */
    PD_16 = 0x06C0061E,  /**< PD.16 */
    
    PE_00 = 0x07000700,  /**< PE.0 */
    PE_01 = 0x07040701,  /**< PE.1 */
    PE_02 = 0x07080702,  /**< PE.2 */
    PE_03 = 0x070C0703,  /**< PE.3 */
    PE_04 = 0x07100704,  /**< PE.4 */
    PE_05 = 0x07140705,  /**< PE.5 */
    PE_06 = 0x07180706,  /**< PE.6 */
    PE_07 = 0x071C0707,  /**< PE.7 */
    PE_08 = 0x07200708,  /**< PE.8 */
    PE_09 = 0x07240709,  /**< PE.9 */
    PE_10 = 0x0728070A,  /**< PE.10 */
    PE_11 = 0x072C070B,  /**< PE.11 */
    PE_12 = 0x0730070C,  /**< PE.12 */
    PE_13 = 0x0734070D,  /**< PE.13 */
    PE_14 = 0x0738070E,  /**< PE.14 */
    PE_15 = 0x073C070F,  /**< PE.15 */
    
    PF_00 = 0x0780FF0F,  /**< PF.0 */
    PF_01 = 0x07840710,  /**< PF.1 */
    PF_02 = 0x07880711,  /**< PF.2 */
    PF_03 = 0x078C0712,  /**< PF.3 */
    PF_04 = 0x0790FF10,  /**< PF.4 */
    PF_05 = 0x07940713,  /**< PF.5 */
    PF_06 = 0x07980714,  /**< PF.6 */
    PF_07 = 0x079C0715,  /**< PF.7 */
    PF_08 = 0x07A00716,  /**< PF.8 */
    PF_09 = 0x07A40717,  /**< PF.9 */
    PF_10 = 0x07A80718,  /**< PF.10 */
    PF_11 = 0x07AC0719,  /**< PF.11 */
    
    PCLK0 = 0x0C00FF00,
    PCLK1 = 0x0C04FF00,
    PCLK2 = 0x0C08FF00,
    PCLK3 = 0x0C0CFF00,

	PIN_INVALID = 0xFFFF,       /* An invalid pin */
};

/***************************************************************************************************************************************//**

    Describes a possible pin direction setting.
    @module     pin-lpc18xx

*******************************************************************************************************************************************/
enum LPC18XX_DIRECTION {
    DIRECTION_INPUT = 0,        /**< Indicates the pin is configured as an input */
    DIRECTION_OUTPUT            /**< Indicates the pin is configured as an output */
};


/***************************************************************************************************************************************//**

    Describes a possible signal edge.
    @module     pin-lpc18xx

*******************************************************************************************************************************************/
enum LPC18XX_EDGE {
	EDGE_NONE       = 0,        /**< Indicates no edges */
	EDGE_RISING     = 1,        /**< Indicates rising-edge signals only */
	EDGE_FALLING    = 2,        /**< Indicates falling-edge signals only */
	EDGE_BOTH       = 3,        /**< Indicates both rising and falling edge signals */
    
    EDGE_INVALID    = 0xFFFF
};

#define NONE        0
#define INPUT       0x00000000      /**< Indicates a pin configured as an input */
#define OUTPUT      0x00000001      /**< Indicates a pin configured as an output */
#define PULLDOWN    0x00000008      /**< Indicates a pin with an on-chip pull-down enabled */
#define NOPULLUP    0x00000010      /**< Indicates a pin with the default on-chip pull-up disabled */
#define SLEWFAST    0x00000020      /**< Indicates a pin with the fast-mode slew option enabled */
#define BUFFERED    0x00000040      /**< Indicates a pin with the input buffer enabled */
#define NOFILTER    0x00000080      /**< Indicates a pin with the default glitch filter disabled */

#define INVERTED    0x00000040      /**< Indicates a pin with the inverted input option enabled */
#define ADANALOG    0x00000000      /**< Indicates a pin with the analog mode enabled */
#define ADDIGITAL   0x00000080      /**< Indicates a pin with the digital mode enabled */


#define OPENDRAIN   0x00000400      /**< Indicates a pin with the open-drain mode enabled */
#define DACEN       0x00010000      /**< Indicates a pin with the DAC option enabled */

/*******************************************************************************************************************************************
    PUBLIC FUNCTIONS
*******************************************************************************************************************************************/
/***************************************************************************************************************************************//**

    Reads and returns the current state of a pin.

    @param[in]  pin         The target pin.

    @return     A value '1' if the pin is currently high; otherwise '0' if low.
    @module     pin-lpc18xx

*******************************************************************************************************************************************/
extern UINT32 PIN_Read(PIN pin);

/***************************************************************************************************************************************//**

    Writes a value to a pin.

    @param[in]  pin         The target pin.
    @param[in]  value       The new value for the specified pin. Use '1' to set the pin as logic level high, or use '0' to set the pin as 
                            logic level low.

    @return     None.
    @module     pin-lpc18xx

*******************************************************************************************************************************************/
extern void PIN_Write(PIN pin, UINT32 value);

/***************************************************************************************************************************************//**

    Returns the current direction setting for a pin.

    @param[in]  pin         The target pin.

    @return

     Direction              | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     DIRECTION_OUTPUT       | The pin is configured as an output.
     DIRECTION_INPUT        | The pin is configured as an input.

    @module     pin-lpc18xx

*******************************************************************************************************************************************/
extern DIRECTION PIN_Direction(PIN pin);

/***************************************************************************************************************************************//**

    Assigns a new direction setting for a pin.

    @param[in]  pin         The target pin to receive the new direction setting.
    @param[in]  dir         The new direction setting for the pin.

     Direction              | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     DIRECTION_OUTPUT       | Use to configure the pin as an output.
     DIRECTION_INPUT        | Use to configure the pin as an input.

    @return     None.
    @module     pin-lpc18xx

*******************************************************************************************************************************************/
extern void PIN_SetDirection(PIN pin, DIRECTION dir);

/***************************************************************************************************************************************//**

    Returns the current function of a pin.

    @param[in]  pin         The target pin.

    @return     The function number assigned to the specified to the pin.
    @module     pin-lpc18xx

*******************************************************************************************************************************************/
extern BYTE PIN_Function(PIN pin);

/***************************************************************************************************************************************//**

    Sets the function for a pin.

    @param[in]  pin         The pin to be configured.
    @param[in]  function    The new function for the pin.

     function               | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     0                      | Assign the pin to function number 0 (default).
     1                      | Assign the pin to function number 1.
     2                      | Assign the pin to function number 2.
     3                      | Assign the pin to function number 3.
     4                      | Assign the pin to function number 4.
     5                      | Assign the pin to function number 5.
     6                      | Assign the pin to function number 6.
     7                      | Assign the pin to function number 7.

    @return     None.
    @module     pin-lpc18xx

*******************************************************************************************************************************************/
extern void PIN_SetFunction(PIN pin, BYTE function);

/***************************************************************************************************************************************//**

    Reads and returns the state of a bit within the SFSP register for a pin.

    @param[in]  pin         The target pin.
    @param[in]  bit         The number of the target bit.

    @return     TRUE if the specified bit is set; otherwise FALSE.
    @module     pin-lpc18xx

*******************************************************************************************************************************************/
extern BOOLEAN PIN_ConfigBit(PIN pin, UINT32 bit);

/***************************************************************************************************************************************//**

    Assigns a new state of a bit within the SFSP register for a pin.

    @param[in]  pin         The target pin.
    @param[in]  bit         The number of the bit to be updated.
    @param[in]  state       The new state for the bit. Use TRUE to set the bit and FALSE to clear the bit.

    @return     None.
    @module     pin-lpc18xx

*******************************************************************************************************************************************/
extern void PIN_SetConfigBit(PIN pin, UINT32 bit, BOOLEAN state);

/***************************************************************************************************************************************//**

    Returns an indication of whether the input buffer is enabled for the specified pin.

    @param[in]  pin         The target pin.

    @return     TRUE if the input buffer is enabled for the pin; otherwise FALSE.
    @module     pin-lpc18xx

*******************************************************************************************************************************************/
extern BOOLEAN PIN_InputBuffer(PIN pin);

/***************************************************************************************************************************************//**

    Enables or disables the input buffer for a pin.

    @param[in]  pin         The target pin.
    @param[in]  enabled     Use TRUE to enable the input buffer for the pin, otherwise FALSE to disable the input buffer.

    @return     None.
    @module     pin-lpc18xx

*******************************************************************************************************************************************/
extern void PIN_SetInputBuffer(PIN pin, BOOLEAN enabled);

/***************************************************************************************************************************************//**

    Returns an indication of whether the pull down resistor is enabled for the specified pin.

    @param[in]  pin         The target pin.

    @return     TRUE if the pull down resistor is enabled for the pin; otherwise FALSE.
    @module     pin-lpc18xx

*******************************************************************************************************************************************/
extern BOOLEAN PIN_PullDown(PIN pin);

/***************************************************************************************************************************************//**

    Enables or disables the pull down resistor for a pin.

    @param[in]  pin         The target pin.
    @param[in]  enabled     Use TRUE to enable the pull down resistor for the pin, otherwise FALSE to disable the pull down resistor.

    @return     None.
    @module     pin-lpc18xx

*******************************************************************************************************************************************/
extern void PIN_SetPullDown(PIN pin, BOOLEAN enabled);

/***************************************************************************************************************************************//**

    Returns an indication of whether the pull up resistor is enabled for the specified pin.

    @param[in]  pin         The target pin.

    @return     TRUE if the pull up resistor is enabled for the pin; otherwise FALSE.
    @module     pin-lpc18xx

*******************************************************************************************************************************************/
extern BOOLEAN PIN_PullUp(PIN pin);

/***************************************************************************************************************************************//**

    Enables or disables the pull up resistor for a pin.

    @param[in]  pin         The target pin.
    @param[in]  enabled     Use TRUE to enable the pull up resistor for the pin, otherwise FALSE to disable the pull up resistor.

    @return     None.
    @module     pin-lpc18xx

*******************************************************************************************************************************************/
extern void PIN_SetPullUp(PIN pin, BOOLEAN enabled);

/***************************************************************************************************************************************//**

    Returns an indication of whether the glitch filter is enabled for the specified pin.

    @param[in]  pin         The target pin.

    @return     TRUE if the glitch filter is enabled for the pin; otherwise FALSE.
    @module     pin-lpc18xx

*******************************************************************************************************************************************/
extern BOOLEAN PIN_GlitchFilter(PIN pin);

/***************************************************************************************************************************************//**

    Enables or disables the glitch filter for a pin.

    @param[in]  pin         The target pin.
    @param[in]  enabled     Use TRUE to enable the glitch filter for the pin, otherwise FALSE to disable the glitch filter.

    @return     None.
    @module     pin-lpc18xx

*******************************************************************************************************************************************/
extern void PIN_SetGlitchFilter(PIN pin, BOOLEAN enabled);

/***************************************************************************************************************************************//**

    Returns an indication of whether the fast slew rate is enabled for the specified pin.

    @param[in]  pin         The target pin.

    @return     TRUE if the fast slew rate is enabled for the pin; otherwise FALSE.
    @module     pin-lpc18xx

*******************************************************************************************************************************************/
extern BOOLEAN PIN_FastSlewRate(PIN pin);

/***************************************************************************************************************************************//**

    Enables or disables the fast slew rate for a pin.

    @param[in]  pin         The target pin.
    @param[in]  enabled     Use TRUE to enable the fast slew rate for the pin, otherwise FALSE.

    @return     None.
    @module     pin-lpc18xx

*******************************************************************************************************************************************/
extern void PIN_SetFastSlewRate(PIN pin, BOOLEAN enabled);

/***************************************************************************************************************************************//**

    Reads and returns the current mask for a pin port. A zero in this register�s bit enables an access to the corresponding physical pin 
    via a read or write access using either PINPORT_Write() or PINPORT_Read(). If a bit in this register is one, the corresponding pin 
    will not be changed with write using PINPORT_Write().

    @param[in]  port        The target pin port.

    @return     The current mask that is applied to the specified port.
    @module     pin-lpc18xx

*******************************************************************************************************************************************/
extern UINT32 PORT_Mask(PORT port);

/***************************************************************************************************************************************//**

    Sets the mask register for a pin port. A zero in this register�s bit enables an access to the corresponding physical pin via a read
    or write access using either PINPORT_Write() or PINPORT_Read(). If a bit in this register is one, the corresponding pin will not be 
    changed with write using PINPORT_Write().

    @param[in]  port        The target pin port.
    @param[in]  mask        The new mask value to be applied to the specified port.

    @return     None.
    @module     pin-lpc18xx

*******************************************************************************************************************************************/
extern void PORT_SetMask(PORT port, UINT32 mask);

/***************************************************************************************************************************************//**

    Reads and returns the direction bits for each of the pins on a port.

    @param[in]  port        The target pin port.

    @return     A bit-field indicating the configured direction for each of the pins on the specified port. A bit value of '1' indicates 
                the pin is configured as an output while a '0' indicates configured as an input.
    @module     pin-lpc18xx

*******************************************************************************************************************************************/
extern UINT32 PORT_Direction(PORT port);

/***************************************************************************************************************************************//**

    Sets the direction for each of the pins on a port.

    @param[in]  port        The target pin port.
    @param[in]  value       A bit-field that specifies a direction for each of the pins. A bit value of '1' indicates the pin to be 
                            configured as an output while a '0' indicates to be configured as an input.

    @return     None.
    @module     pin-lpc18xx

*******************************************************************************************************************************************/
extern void PORT_SetDirection(PORT port, UINT32 value);

/***************************************************************************************************************************************//**

    Reads and returns a bit-field of states of each of the pins for a port. Only valid for the pins that are not currently masked by the
    PINPORT_SetMask() function.

    @param[in]  port        The target pin port.

    @return     A bit value '1' indicates the pin is currently high; otherwise a '0' if the pin is low.
    @module     pin-lpc18xx

*******************************************************************************************************************************************/
extern UINT32 PORT_Read(PORT port);

/***************************************************************************************************************************************//**

    Writes and sets the states of each of the pins for a port. Only applies to the pins that are not currently masked by the 
    PINPORT_SetMask() function.

    @param[in]  port        The target pin port to be written.
    @param[in]  value       A bit-field of states for each of the pins. A bit value of '1' sets the pin to a logic level high while a '0'
                            sets the pin to a logic level low.

    @return     None.
    @module     pin-lpc18xx

*******************************************************************************************************************************************/
extern void PORT_Write(PORT port, UINT32 value);

#endif /* MCU_PIN_H__ */
