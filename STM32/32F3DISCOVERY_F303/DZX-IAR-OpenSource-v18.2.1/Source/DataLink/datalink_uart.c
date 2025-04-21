/*******************************************************************************************************************************************

    DZX | DATALINK | UARTLINK                                                                                             VERSION 18.2.1
    ------------------------------------------------------------------------------------------------------------------------------------

    This provides a basic implementation of a data link that transfers messages over an UART.

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
#include "datalink_uart.h"

/*******************************************************************************************************************************************
    PRIVATE FUNCTIONS
*******************************************************************************************************************************************/
static void UARTLINK_ThreadProc(void* arg);
static STATUS UARTLINK_Write(DATALINK* link, void* arg, const void* data, UINT32 nbytes);

/***************************************************************************************************************************************//**

    Creates and initializes a data link that transfer messages over a UART.

    @param[in]  link        A pointer to a caller allocated UART data link instance to be initialized.
    @param[in]  create      The create handler function to initialize the application-defined data link.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The data link has been created and initialized.
     ERR_NULLREFERENCE      | The argument 'link' was found to be NULL.

    @module     datalink-uart

*******************************************************************************************************************************************/
STATUS UARTLINK_Create(UARTLINK* link, DATALINKCREATEHANDLER create)
{
    STATUS status;
    
    
#if (CFG_NULLCHECKING)
    if (link == NULL) {
        return ERR_NULLREFERENCE;
    }
    
    if (create == NULL) {
        return ERR_NULLREFERENCE;
    }
#endif
    
    status = create(&link->base,                                /* Initialize the application-defined data link */
                    UARTLINK_Write,                             /* The write handler function */
                    link);                                      /* Argument for the write handler function */
    
    if (status != SUCCESS) {
        return status;
    }
    
    status = DATALINK_EnableEncapsulation(&link->base,          /* Enable encapsulation for a UART data link (required for UART) */
                                          link->decbuf,
                                          CFG_UARTLINKDECODEBUFSIZE,
                                          link->encbuf,
                                          CFG_UARTLINKENCODEBUFSIZE);
    
    if (status != SUCCESS) {
        return status;
    }

    status = THREAD_Create(&link->thread,                       /* Create a thread to process data received over the UART */
                           "UART Data Link",                    /* A name for the thread */
                           link->stk,                           /* A pointer to the stack memory for the thread */
                           sizeof(link->stk),                   /* The size, in bytes, of the stack memory */
                           PRIO_NORMAL);                        /* The initial priority for the thread */
    
    if (status != SUCCESS) {
        return status;
    }

    return SUCCESS;
}

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
STATUS UARTLINK_Destroy(UARTLINK* link)
{
    STATUS status;
    
    
#if (CFG_NULLCHECKING)
    if (link == NULL) {
        return ERR_NULLREFERENCE;
    }
#endif
    
    status = UARTLINK_Close(link);                              /* Close the link (which will close the port and stop the thread) */
    if (status != SUCCESS) {
        return status;
    }
    
    status = THREAD_Destroy(&link->thread);                     /* Destroy the underlying thread */
    if (status != SUCCESS) {
        return status;
    }
    
    return SUCCESS;
}

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
STATUS UARTLINK_Open(UARTLINK* link, UINT32 port, UINT32 baud)
{
    STATUS status;
    
    
#if (CFG_NULLCHECKING)
    if (link == NULL) {
        return ERR_NULLREFERENCE;
    }
#endif

    status = UART_Open(&link->uart,                             /* Open the specified UART */
                       port,                                    /* The port number to be opened */
                       baud,                                    /* The baud rate */
                       8,                                       /* Number of data bits */
                       STOPBITS_ONE,                            /* Stop bits */
                       PARITY_NONE,                             /* Parity options */
                       HANDSHAKE_NONE);                         /* Handshake options */
    
    if (status != SUCCESS) {
        return status;
    }
    
    status = THREAD_Start(&link->thread,                        /* Start the thread for receiving data from the UART */
                          UARTLINK_ThreadProc,                  /* The process function for the thread */
                          link);                                /* An argument for the thread process function */
    
    if (status != SUCCESS) {
        return status;
    }
    
    return SUCCESS;
}

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
STATUS UARTLINK_Close(UARTLINK* link)
{
    STATUS status;
    
    
#if (CFG_NULLCHECKING)
    if (link == NULL) {
        return ERR_NULLREFERENCE;
    }
#endif
    
    status = THREAD_Abort(&link->thread);                       /* Abort the underlying thread */
    if (status != SUCCESS) {
        return status;
    }
    
    status = THREAD_Join(&link->thread, INFINITE);              /* Wait for the thread to terminate */
    if (status != SUCCESS) {
        return status;
    }
    
    status = UART_Close(&link->uart);                           /* Close the underlying UART */
    if (status != SUCCESS) {
        return status;
    }

    return SUCCESS;
}

/***************************************************************************************************************************************//**

    The thread process function for a UART data link. This continually reads the underlying UART and provides any received data to the
    data link.

    @param[in]  arg         A pointer to an application-defined argument.

    @return     None.
    @module     datalink-uart

*******************************************************************************************************************************************/
static void UARTLINK_ThreadProc(void* arg)
{
    UARTLINK* link = (UARTLINK*)arg;
    STATUS status;
    UINT32 num;
    ALIGNED(4) BYTE buffer[32];
    


    for (;;) {
        
        status = UART_Read(&link->uart,                         /* Read any available data from the UART */
                           buffer,                              /* A buffer to receive the data */
                           sizeof(buffer),                      /* The maximum amount to receive */
                           &num,                                /* A pointer to variable to get actual amount received */
                           2);                                  /* Maximum amount of time to wait, in kernel ticks */
        
        if (status == SUCCESS) {
            
            if (num > 0) {                                      /* Received any data? */
                
                DATALINK_ReceivedBytes(&link->base,             /* Provide the data link with the received data */
                                       buffer, 
                                       num);
            }
        }
        
        if (THREAD_Aborted()) {
            return;                                             /* Exit if aborted */
        }
    }
}
          
/***************************************************************************************************************************************//**

    A handler function called by a data link to transmit data over the link. This transmits the data over the underlying UART.

    @param[in]  arg         A pointer to an application-defined argument.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The data has been written successfully.

    @module     datalink-uart

*******************************************************************************************************************************************/
static STATUS UARTLINK_Write(DATALINK* link, void* arg, const void* data, UINT32 nbytes)
{
    UARTLINK* uartlink = (UARTLINK*)arg;
    STATUS status;
    
    
    status = UART_Write(&uartlink->uart,                        /* Write the data to the underlying UART */
                        data,                                   /* A pointer to the data to be transmitted */
                        nbytes,                                 /* The number of bytes to be transmitted */
                        NULL,                                   /* A pointer to a variable to retrieve actual count transmitted */
                        1000);                                  /* Maximum amount of time, in kernel ticks, to wait for completion */
    
    if (status != SUCCESS) {
        return status;
    }
    
    return SUCCESS;
}
