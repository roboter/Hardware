/*******************************************************************************************************************************************

    DZX | DATALINK | UARTLINK                                                                                             VERSION 18.2.1
    ------------------------------------------------------------------------------------------------------------------------------------

    This provides the interface for a basic implementation of a data link that transfers messages over an UART.

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
#ifndef UARTLINK_H__
#define UARTLINK_H__

#include "mcu_uart.h"
#include "DataLink/datalink.h"


/*******************************************************************************************************************************************
    TYPE DEFINITIONS
*******************************************************************************************************************************************/
/***************************************************************************************************************************************//**

    Represents a data link instance that transfers messages over a UART.
    @module     datalink-uart

*******************************************************************************************************************************************/
typedef struct UARTLINK {
    DATALINK    base;                                   /**< Build upon the base data link */
    UART        uart;                                   /**< A UART for transferring data */
    THREAD      thread;                                 /**< A thread for receiving and processing data for the link */
    BYTE        stk[CFG_UARTLINKSTACKSIZE];             /**< Stack memory for the thread */
    BYTE        decbuf[CFG_UARTLINKDECODEBUFSIZE];      /**< A buffer for holding decapsulated message data */
    BYTE        encbuf[CFG_UARTLINKENCODEBUFSIZE];      /**< A buffer for holding encapsulated message data */
} UARTLINK;


/*******************************************************************************************************************************************
    PUBLIC FUNCTIONS
*******************************************************************************************************************************************/
/***************************************************************************************************************************************//**

    Creates and initializes a data link that transfer messages over a UART.

    @param[in]  link        A pointer to a caller allocated UART data link instance to be initialized.
    @param[in]  create      The create handler function to initialize the application-defined data link.
    @param[in]  port        The port number of the UART to be opened.
    @param[in]  baud        The baud rate for the UART.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The data link has been created and initialized.
     ERR_NULLREFERENCE      | The argument 'link' was found to be NULL.

    @module     datalink-uart

*******************************************************************************************************************************************/
extern STATUS UARTLINK_Create(UARTLINK* link, DATALINKCREATEHANDLER create);

/***************************************************************************************************************************************//**

    Opens the underlying port for a UART data link.

    @param[in]  link        A pointer to the UART data link to be opened.
    @param[in]  port        The port number of the UART to be opened.
    @param[in]  baud        The baud rate for the UART.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The link has been opened for communications.
     ERR_NULLREFERENCE      | The argument 'link' was found to be NULL.

    @module     datalink-uart

*******************************************************************************************************************************************/
extern STATUS UARTLINK_Open(UARTLINK* link, UINT32 port, UINT32 baud);

/***************************************************************************************************************************************//**

    Closes the underlying port and stops communications for a UART data link.

    @param[in]  link        A pointer to the UART data link to be closed.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The link has been closed.
     ERR_NULLREFERENCE      | The argument 'link' was found to be NULL.

    @module     datalink-uart

*******************************************************************************************************************************************/
extern STATUS UARTLINK_Close(UARTLINK* link);

/***************************************************************************************************************************************//**

    Destroys a UART data link.

    @param[in]  link        A pointer to the UART data link to be destroyed.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The link has been destroyed.
     ERR_NULLREFERENCE      | The argument 'link' was found to be NULL.

    @module     datalink-uart

*******************************************************************************************************************************************/
extern STATUS UARTLINK_Destroy(UARTLINK* link);

#endif /* UARTLINK_H__ */
