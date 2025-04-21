/*******************************************************************************************************************************************

    DZX | DATALINK | CONFIGURATION                                                                                        VERSION 18.2.1
    ------------------------------------------------------------------------------------------------------------------------------------

    This provides configuration settings for communication data links.

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
#ifndef DATALINK_CFG_H__
#define DATALINK_CFG_H__


/*******************************************************************************************************************************************
    GENERAL CONFIGURATION
*******************************************************************************************************************************************/
/*******************************************************************************************************************************************

    SUPPORT CRC                     Indicates whether to include code for calculating CRC's to verify messages. This is required if any
                                    data link is using a CRC to verify messages. If TRUE, must add source file 'Crypto/crc32.c' to 
                                    compilation.

*******************************************************************************************************************************************/
#define CFG_DATALINKCRC             TRUE

/*******************************************************************************************************************************************

    SUPPORT ENCAPSULATION           Indicates whether to include code for encapsulating messages. This is used when transferring messages
                                    over an interface that does not have natural encapsulation.
                                        
                                        FALSE - when transferring over native USB with short packet termination.
                                        TRUE  - when transferring over UART.

*******************************************************************************************************************************************/
#define CFG_DATALINKENCAPSULATION   TRUE




/*******************************************************************************************************************************************
    UART DATA LINK CONFIGURATION
*******************************************************************************************************************************************/
/*******************************************************************************************************************************************

    UARTLINK THREAD STACK SIZE      The size, in bytes, of the stack memory for the underlying thread of a UART data link. The thread 
                                    processes all data received over the UART.

*******************************************************************************************************************************************/
#define CFG_UARTLINKSTACKSIZE       1024

/*******************************************************************************************************************************************

    UARTLINK DECODER BUFFER SIZE    The size, in bytes, of the buffer that holds decoded (decapsulated) data that has been received over
                                    the link. This must be large enough to hold the largest message that can be received by the device.

*******************************************************************************************************************************************/
#define CFG_UARTLINKDECODEBUFSIZE   1024

/*******************************************************************************************************************************************

    UARTLINK ENCODER BUFFER SIZE    The size, in bytes, of the buffer that holds encoded (encapsulated) data to be transmitted over the
                                    link. This does not have to be large enough to contain an entire message. A larger buffer reduces
                                    the number of calls that is made to data link write handler function.

*******************************************************************************************************************************************/
#define CFG_UARTLINKENCODEBUFSIZE   64




/*******************************************************************************************************************************************
    USB DATA LINK CONFIGURATION
*******************************************************************************************************************************************/
/*******************************************************************************************************************************************

    USBLINK THREAD STACK SIZE       The size, in bytes, of the stack memory for the underlying thread of a USB data link. The thread reads 
                                    the receive endpoint and processes all received data.

*******************************************************************************************************************************************/
#define CFG_USBLINKSTACKSIZE        1024

/*******************************************************************************************************************************************

    USBLINK BUFFER SIZE             The size, in bytes, of the buffer used to receive data over the receive endpoint. Must be large enough
                                    to receive and hold the largest message that can be received by the link.

*******************************************************************************************************************************************/
#define CFG_USBLINKBUFFERSIZE       1024

#endif /* DATALINK_CFG_H__ */
