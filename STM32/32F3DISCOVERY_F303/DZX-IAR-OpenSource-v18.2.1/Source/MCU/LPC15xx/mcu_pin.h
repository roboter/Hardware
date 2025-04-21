/*******************************************************************************************************************************************

    DZX | LPC15xx | PIN                                                                                                   VERSION 18.2.1
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
#define REG_GPIOBASE        0x1C000000
#define REG_GPIODIRBASE     (REG_GPIOBASE + 0x2000)
#define REG_GPIOMASKBASE    (REG_GPIOBASE + 0x2080)
#define REG_GPIOPINBASE     (REG_GPIOBASE + 0x2100)
#define REG_GPIOSETBASE     (REG_GPIOBASE + 0x2200)
#define REG_GPIOCLRBASE     (REG_GPIOBASE + 0x2280)
#define REG_PINASSIGNBASE   0x40038000

/*******************************************************************************************************************************************
    TYPE DEFINITIONS
*******************************************************************************************************************************************/
typedef enum LPC15XX_PORT PORT;
typedef enum LPC15XX_PIN PIN;
typedef enum LPC15XX_EDGE EDGE;
typedef enum LPC15XX_DIRECTION DIRECTION;
typedef enum LPC15XX_FUNCTION FUNCTION;

enum LPC15XX_DIRECTION {
    DIRECTION_INPUT = 0,
    DIRECTION_OUTPUT
};

enum LPC15XX_FUNCTION {
    UART0_TXD_O = 0,
    UART0_RXD_I,
    UART0_RTS_O,
    UART0_CTS_I,
    
    UART0_SCLK_IO,
    UART1_TXD_O,
    UART1_RXD_I,
    UART1_RTS_O,
    
    UART1_CTS_I,
    UART1_SCLK_IO,
    UART2_TXD_O,
    UART2_RXD_I,
    
    UART2_SCLK_IO,
    SPI0_SCK_IO,
    SPI0_MOSI_IO,
    SPI0_MISO_IO,
    
    SPI0_SSELSN_0_IO,
    SPI0_SSELSN_1_IO,
    SPI0_SSELSN_2_IO,
    SPI0_SSELSN_3_IO,
    
    SPI1_SCK_IO,
    SPI1_MOSI_IO,
    SPI1_MISO_IO,
    SPI1_SSELSN_0_IO,
    
    SPI1_SSELSN_1_IO,
    CAN_TD1_O,
    CAN_RD1_I,
    
    USB_VBUS_I = 28,
    SCT0_OUT0_O,
    SCT0_OUT1_O,
    SCT0_OUT2_O,
    
    SCT1_OUT0_O,
    SCT1_OUT1_O,
    SCT1_OUT2_O,
    SCT2_OUT0_O,
    
    SCT2_OUT1_O,
    SCT2_OUT2_O,
    SCT3_OUT0_O,
    SCT3_OUT1_O,
    
    SCT3_OUT2_O,                /* PINASSIGN10 */
    SCT_ABORT0_I,
    SCT_ABORT1_I,
    ADC0_PIN_TRIG0_I,
    
    ADC0_PIN_TRIG1_I,
    ADC1_PIN_TRIG0_I,
    ADC1_PIN_TRIG1_I,
    DAC_PIN_TRIG_I,
    
    DAC_SHUTOFF_I,
    ACMP0_OUT_O,
    ACMP1_OUT_O,
    ACMP2_OUT_O,
    
    ACMP3_OUT_O,
    CLK_OUT_O,
    ROSC0_O,
    ROSC_RST0_I,
    
    USB_FRAME_TOG_O,
    QEI0_PHA_I,
    QEI0_PHB_I,
    QEI0_IDX_I,
    
    GPIO_INT_BMATCH_O,
    SWO_O
};

/***************************************************************************************************************************************//**

    Represents a port of pins within the MCU.
    @module     pin-lpc15xx

*******************************************************************************************************************************************/
enum LPC15XX_PORT {
	PORT_0 = 0,     /**< Pin Port 0 */
	PORT_1,         /**< Pin Port 1 */
	PORT_2,         /**< Pin Port 2 */
	PORT_MAX
};

/***************************************************************************************************************************************//**

    Represents an individual pin on the MCU.
    @module     pin-lpc15xx

*******************************************************************************************************************************************/
enum LPC15XX_PIN {
	P0_00 = 0x0000,  /**< P0.0 */
	P0_01 = 0x0001,  /**< P0.1 */
	P0_02 = 0x0002,  /**< P0.2 */
	P0_03 = 0x0003,  /**< P0.3 */
	P0_04 = 0x0004,  /**< P0.4 */
	P0_05 = 0x0005,  /**< P0.5 */
	P0_06 = 0x0006,  /**< P0.6 */
	P0_07 = 0x0007,  /**< P0.7 */
	P0_08 = 0x0008,  /**< P0.8 */
	P0_09 = 0x0009,  /**< P0.9 */
	P0_10 = 0x000A,  /**< P0.10 */
	P0_11 = 0x000B,  /**< P0.11 */
	P0_12 = 0x000C,  /**< P0.12 */
	P0_13 = 0x000D,  /**< P0.13 */
	P0_14 = 0x000E,  /**< P0.14 */
	P0_15 = 0x000F,  /**< P0.15 */
	P0_16 = 0x0010,  /**< P0.16 */
	P0_17 = 0x0011,  /**< P0.17 */
	P0_18 = 0x0012,  /**< P0.18 */
	P0_19 = 0x0013,  /**< P0.19 */
	P0_20 = 0x0014,  /**< P0.20 */
	P0_21 = 0x0015,  /**< P0.21 */
	P0_22 = 0x0016,  /**< P0.22 */
	P0_23 = 0x0017,  /**< P0.23 */
	P0_24 = 0x0018,  /**< P0.24 */
	P0_25 = 0x0019,  /**< P0.25 */
	P0_26 = 0x001A,  /**< P0.26 */
	P0_27 = 0x001B,  /**< P0.27 */
	P0_28 = 0x001C,  /**< P0.28 */
	P0_29 = 0x001D,  /**< P0.29 */
	P0_30 = 0x001E,  /**< P0.30 */
	P0_31 = 0x001F,  /**< P0.31 */


	P1_00 = 0x0100,  /**< P1.0 */
	P1_01 = 0x0101,  /**< P1.1 */
	P1_02 = 0x0102,  /**< P1.2 */
	P1_03 = 0x0103,  /**< P1.3 */
	P1_04 = 0x0104,  /**< P1.4 */
	P1_05 = 0x0105,  /**< P1.5 */
	P1_06 = 0x0106,  /**< P1.6 */
	P1_07 = 0x0107,  /**< P1.7 */
	P1_08 = 0x0108,  /**< P1.8 */
	P1_09 = 0x0109,  /**< P1.9 */
	P1_10 = 0x010A,  /**< P1.10 */
	P1_11 = 0x010B,  /**< P1.11 */
	P1_12 = 0x010C,  /**< P1.12 */
	P1_13 = 0x010D,  /**< P1.13 */
	P1_14 = 0x010E,  /**< P1.14 */
	P1_15 = 0x010F,  /**< P1.15 */
	P1_16 = 0x0110,  /**< P1.16 */
	P1_17 = 0x0111,  /**< P1.17 */
	P1_18 = 0x0112,  /**< P1.18 */
	P1_19 = 0x0113,  /**< P1.19 */
	P1_20 = 0x0114,  /**< P1.20 */
	P1_21 = 0x0115,  /**< P1.21 */
	P1_22 = 0x0116,  /**< P1.22 */
	P1_23 = 0x0117,  /**< P1.23 */
	P1_24 = 0x0118,  /**< P1.24 */
	P1_25 = 0x0119,  /**< P1.25 */
	P1_26 = 0x011A,  /**< P1.26 */
	P1_27 = 0x011B,  /**< P1.27 */
	P1_28 = 0x011C,  /**< P1.28 */
	P1_29 = 0x011D,  /**< P1.29 */
	P1_30 = 0x011E,  /**< P1.30 */
	P1_31 = 0x011F,  /**< P1.31 */

	P2_00 = 0x0200,  /**< P2.0 */
	P2_01 = 0x0201,  /**< P2.1 */
	P2_02 = 0x0202,  /**< P2.2 */
	P2_03 = 0x0203,  /**< P2.3 */
	P2_04 = 0x0204,  /**< P2.4 */
	P2_05 = 0x0205,  /**< P2.5 */
	P2_06 = 0x0206,  /**< P2.6 */
	P2_07 = 0x0207,  /**< P2.7 */
	P2_08 = 0x0208,  /**< P2.8 */
	P2_09 = 0x0209,  /**< P2.9 */
	P2_10 = 0x020A,  /**< P2.10 */
	P2_11 = 0x020B,  /**< P2.11 */
	P2_12 = 0x020C,  /**< P2.12 */
	P2_13 = 0x020D,  /**< P2.13 */
	P2_14 = 0x020E,  /**< P2.14 */
	P2_15 = 0x020F,  /**< P2.15 */
	P2_16 = 0x0210,  /**< P2.16 */
	P2_17 = 0x0211,  /**< P2.17 */
	P2_18 = 0x0212,  /**< P2.18 */
	P2_19 = 0x0213,  /**< P2.19 */
	P2_20 = 0x0214,  /**< P2.20 */
	P2_21 = 0x0215,  /**< P2.21 */
	P2_22 = 0x0216,  /**< P2.22 */
	P2_23 = 0x0217,  /**< P2.23 */
	P2_24 = 0x0218,  /**< P2.24 */
	P2_25 = 0x0219,  /**< P2.25 */
	P2_26 = 0x021A,  /**< P2.26 */
	P2_27 = 0x021B,  /**< P2.27 */
	P2_28 = 0x021C,  /**< P2.28 */
	P2_29 = 0x021D,  /**< P2.29 */
	P2_30 = 0x021E,  /**< P2.30 */
	P2_31 = 0x021F,  /**< P2.31 */

	P3_00 = 0x0300,  /**< P3.0 */
	P3_01 = 0x0301,  /**< P3.1 */
	P3_02 = 0x0302,  /**< P3.2 */
	P3_03 = 0x0303,  /**< P3.3 */
	P3_04 = 0x0304,  /**< P3.4 */
	P3_05 = 0x0305,  /**< P3.5 */
	P3_06 = 0x0306,  /**< P3.6 */
	P3_07 = 0x0307,  /**< P3.7 */
	P3_08 = 0x0308,  /**< P3.8 */
	P3_09 = 0x0309,  /**< P3.9 */
	P3_10 = 0x030A,  /**< P3.10 */
	P3_11 = 0x030B,  /**< P3.11 */
	P3_12 = 0x030C,  /**< P3.12 */
	P3_13 = 0x030D,  /**< P3.13 */
	P3_14 = 0x030E,  /**< P3.14 */
	P3_15 = 0x030F,  /**< P3.15 */
	P3_16 = 0x0310,  /**< P3.16 */
	P3_17 = 0x0311,  /**< P3.17 */
	P3_18 = 0x0312,  /**< P3.18 */
	P3_19 = 0x0313,  /**< P3.19 */
	P3_20 = 0x0314,  /**< P3.20 */
	P3_21 = 0x0315,  /**< P3.21 */
	P3_22 = 0x0316,  /**< P3.22 */
	P3_23 = 0x0317,  /**< P3.23 */
	P3_24 = 0x0318,  /**< P3.24 */
	P3_25 = 0x0319,  /**< P3.25 */
	P3_26 = 0x031A,  /**< P3.26 */
	P3_27 = 0x031B,  /**< P3.27 */
	P3_28 = 0x031C,  /**< P3.28 */
	P3_29 = 0x031D,  /**< P3.29 */
	P3_30 = 0x031E,  /**< P3.30 */
	P3_31 = 0x031F,  /**< P3.31 */

	P4_00 = 0x0400,  /**< P4.0 */
	P4_01 = 0x0401,  /**< P4.1 */
	P4_02 = 0x0402,  /**< P4.2 */
	P4_03 = 0x0403,  /**< P4.3 */
	P4_04 = 0x0404,  /**< P4.4 */
	P4_05 = 0x0405,  /**< P4.5 */
	P4_06 = 0x0406,  /**< P4.6 */
	P4_07 = 0x0407,  /**< P4.7 */
	P4_08 = 0x0408,  /**< P4.8 */
	P4_09 = 0x0409,  /**< P4.9 */
	P4_10 = 0x040A,  /**< P4.10 */
	P4_11 = 0x040B,  /**< P4.11 */
	P4_12 = 0x040C,  /**< P4.12 */
	P4_13 = 0x040D,  /**< P4.13 */
	P4_14 = 0x040E,  /**< P4.14 */
	P4_15 = 0x040F,  /**< P4.15 */
	P4_16 = 0x0410,  /**< P4.16 */
	P4_17 = 0x0411,  /**< P4.17 */
	P4_18 = 0x0412,  /**< P4.18 */
	P4_19 = 0x0413,  /**< P4.19 */
	P4_20 = 0x0414,  /**< P4.20 */
	P4_21 = 0x0415,  /**< P4.21 */
	P4_22 = 0x0416,  /**< P4.22 */
	P4_23 = 0x0417,  /**< P4.23 */
	P4_24 = 0x0418,  /**< P4.24 */
	P4_25 = 0x0419,  /**< P4.25 */
	P4_26 = 0x041A,  /**< P4.26 */
	P4_27 = 0x041B,  /**< P4.27 */
	P4_28 = 0x041C,  /**< P4.28 */
	P4_29 = 0x041D,  /**< P4.29 */
	P4_30 = 0x041E,  /**< P4.30 */
	P4_31 = 0x041F,  /**< P4.31 */
    
    P5_00 = 0x0500,  /**< P5.0 */
    P5_01 = 0x0501,  /**< P5.1 */
    P5_02 = 0x0502,  /**< P5.2 */
    P5_03 = 0x0503,  /**< P5.3 */
    P5_04 = 0x0504,  /**< P5.4 */
    
	PIN_INVALID = 0xFFFF,       /* An invalid pin */
};

/***************************************************************************************************************************************//**

    Describes a possible signal edge.
    @module     pin-lpc15xx

*******************************************************************************************************************************************/
enum LPC15XX_EDGE {
	EDGE_NONE       = 0,        /**< Indicates no edges */
	EDGE_RISING     = 1,        /**< Indicates rising-edge signals only */
	EDGE_FALLING    = 2,        /**< Indicates falling-edge signals only */
	EDGE_BOTH       = 3,        /**< Indicates both rising and falling edge signals */
    
    EDGE_INVALID    = 0xFFFF
};

/*******************************************************************************************************************************************
    PUBLIC FUNCTIONS
*******************************************************************************************************************************************/
/***************************************************************************************************************************************//**

    Assigns a pin to a function.

    @param[in]  function    The target function to be assigned the pin.
    @param[in]  pin         The pin to be assigned to the function.

    @return     None.
    @module     pin-lpc15xx

*******************************************************************************************************************************************/
extern void PIN_Assign(FUNCTION function, PIN pin);

/***************************************************************************************************************************************//**

    Assigns a new direction setting for a pin.

    @param[in]  pin         The target pin to receive the new direction setting.
    @param[in]  dir         The new direction setting for the pin.

     Direction              | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     DIRECTION_OUTPUT       | Use to configure the pin as an output.
     DIRECTION_INPUT        | Use to configure the pin as an input.

    @return     None.
    @module     pin-lpc15xx

*******************************************************************************************************************************************/
extern void PIN_SetDirection(PIN pin, DIRECTION dir);

/***************************************************************************************************************************************//**

    Returns the current direction setting for a pin.

    @param[in]  pin         The target pin.

    @return

     Direction              | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     DIRECTION_OUTPUT       | The pin is configured as an output.
     DIRECTION_INPUT        | The pin is configured as an input.

    @module     pin-lpc15xx

*******************************************************************************************************************************************/
extern DIRECTION PIN_Direction(PIN pin);

/***************************************************************************************************************************************//**

    Reads and returns the current state of a pin.

    @param[in]  pin         The target pin.

    @return     A value '1' if the pin is currently high; otherwise '0' if low.
    @module     pin-lpc15xx

*******************************************************************************************************************************************/
extern UINT32 PIN_Read(PIN pin);

/***************************************************************************************************************************************//**

    Writes a value to a pin.

    @param[in]  pin         The target pin.
    @param[in]  value       The new value for the specified pin. Use '1' to set the pin as logic level high, or use '0' to set the pin 
                            as logic level low.

    @return     None.
    @module     pin-lpc15xx

*******************************************************************************************************************************************/
extern void PIN_Write(PIN pin, UINT32 value);

/***************************************************************************************************************************************//**

    Reads and returns the current mask for a pin port. A zero in this register�s bit enables an access to the corresponding physical pin 
    via a read or write access using either PINPORT_Write() or PINPORT_Read(). If a bit in this register is one, the corresponding pin 
    will not be changed with write using PINPORT_Write().

    @param[in]  port        The target pin port.

    @return     The current mask that is applied to the specified port.
    @module     pin-lpc15xx

*******************************************************************************************************************************************/
extern UINT32 PORT_Mask(PORT port);

/***************************************************************************************************************************************//**

    Sets the mask register for a pin port. A zero in this register�s bit enables an access to the corresponding physical pin via a read
    or write access using either PINPORT_Write() or PINPORT_Read(). If a bit in this register is one, the corresponding pin will not be 
    changed with write using PINPORT_Write().

    @param[in]  port        The target pin port.
    @param[in]  mask        The new mask value to be applied to the specified port.

    @return     None.
    @module     pin-lpc15xx

*******************************************************************************************************************************************/
extern void PORT_SetMask(PORT port, UINT32 mask);

/***************************************************************************************************************************************//**

    Reads and returns the direction bits for each of the pins on a port.

    @param[in]  port        The target pin port.

    @return     A bit-field indicating the configured direction for each of the pins on the specified port. A bit value of '1' indicates 
                the pin is configured as an output while a '0' indicates configured as an input.
    @module     pin-lpc15xx

*******************************************************************************************************************************************/
extern UINT32 PORT_Direction(PORT port);

/***************************************************************************************************************************************//**

    Sets the direction for each of the pins on a port.

    @param[in]  port        The target pin port.
    @param[in]  value       A bit-field that specifies a direction for each of the pins. A bit value of '1' indicates the pin to be 
                            configured as an output while a '0' indicates to be configured as an input.

    @return     None.
    @module     pin-lpc15xx

*******************************************************************************************************************************************/
extern void PORT_SetDirection(PORT port, UINT32 value);

/***************************************************************************************************************************************//**

    Reads and returns a bit-field of states of each of the pins for a port. Only valid for the pins that are not currently masked by the
    PINPORT_SetMask() function.

    @param[in]  port        The target pin port.

    @return     A bit value '1' indicates the pin is currently high; otherwise a '0' if the pin is low.
    @module     pin-lpc15xx

*******************************************************************************************************************************************/
extern UINT32 PORT_Read(PORT port);

/***************************************************************************************************************************************//**

    Writes and sets the states of each of the pins for a port. Only applies to the pins that are not currently masked by the 
    PINPORT_SetMask() function.

    @param[in]  port        The target pin port to be written.
    @param[in]  value       A bit-field of states for each of the pins. A bit value of '1' sets the pin to a logic level high while a '0'
                            sets the pin to a logic level low.

    @return     None.
    @module     pin-lpc15xx

*******************************************************************************************************************************************/
extern void PORT_Write(PORT port, UINT32 value);
                                        
#endif /* MCU_PIN_H__ */
